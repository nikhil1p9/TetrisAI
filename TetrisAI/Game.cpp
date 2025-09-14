#include "Game.h"
#include "Renderer.h"
#include "TPiece.h"
#include <numeric>

void Game::delete_lines()
{
	int no_of_lines_deleted = 0;
	for(int i = 0; i < board.size(); ++i) {
		bool full_line = true;	
		for (int j = 0; j < board[i].size(); ++j) {
			if (!board[i][j]) {
				full_line = false;
				break;
			}
		}
		if(full_line) {
			no_of_lines_deleted++;
			board.erase(board.begin() + i);
			board.insert(board.begin(), std::vector<bool>(board[0].size(), false));
		}
		
	}
	int line_scores[] = {0, 2, 5, 15, 60};
	score +=  line_scores[no_of_lines_deleted] ;
}

void Game::spawn_piece() {

	Piece* pieces[] = {
		new LPiece(),
		new InvertedLPiece(),
		new OPiece(),
		new SPiece(),
		new TetrisPiece(),
		new TPiece(),
		new ZPiece()
	};

	int piece_number = rand() % 7;
	this->hanging_piece = pieces[piece_number]; 

	for (int i = 0; i < 7; ++i) {
		if (i == piece_number) continue;
		delete pieces[i];
	}
}

bool Game::is_game_over()
{
	return game_over;
}

void Game::tick()
{

	if (hanging_piece->is_colliding(board,0,1)) {
		int* position = hanging_piece->get_position();
		std::vector<std::vector<bool>> piece_matrix = hanging_piece->get_piece_matrix();
		for (int i = 0; i < piece_matrix.size(); ++i) {
			for (int j = 0; j < piece_matrix[i].size(); ++j) {
				if (piece_matrix[i][j]) {
					if (position[1] + i < 0) {
						game_over = true;
						return;
					}
					board[position[1] + i][position[0] + j] = true;
				}
			}
		}
		spawn_piece();
		delete_lines();
	}
	else {
		hanging_piece->apply_gravity();
	}
}

void Game::apply_movement(Movement movement)
{
	if (!hanging_piece) return;
	switch (movement) {
		case Movement::LEFT:
			hanging_piece->move(board, -1, 0);
			break;
		case Movement::RIGHT:
			hanging_piece->move(board, 1, 0);
			break;
		case Movement::DOWN:
			hanging_piece->move(board, 0, 1);
			break;
		case Movement::ROTATE:
			hanging_piece->rotate(board);
			break;
		case Movement::SNAP_DOWN:
			while (hanging_piece->move(board, 0, 1));
			break;
		default:
			break;
	}
}
