#include "Game.h"
#include "Renderer.h"
#include "TPiece.h"
#include <numeric>

void Game::delete_lines()
{
	int line_scores[] = {0, 2, 5, 15, 60};
	int no_of_lines_deleted = this->board.delete_lines();
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
	free(this->hanging_piece);
	this->hanging_piece = this->next_piece;
		
	this->next_piece = pieces[piece_number]; 

	for(int i = 0; i < rand() % 4; ++i) {
		this->next_piece->rotate(board);
	}

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

		game_over |= !board.drop_piece(hanging_piece);

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
