#include "Piece.h"
#include<iostream>
#include<algorithm>
#include "Board.h"
bool Piece::rotate(Board& board)
{
	int old_rotation = this->rotation;
	this->rotation = (this->rotation + 1) % 4;
	if (this->is_colliding(board)) {
		this->rotation = old_rotation;
		return false;
	}
	return true;
}

bool Piece::move(Board& board, int x_offset, int y_offset)
{
	std::vector<int>grid = board.get_grid();
	std::vector<int>raw_piece_matrix = this->raw_piece_matrix();
	if (position[1] + y_offset >=0 and position[1] + y_offset <grid.size()) 
	if ((raw_piece_matrix.back() << position[0]) & grid[position[1] + y_offset]) return false;
	//if (x_offset < 0 && (raw_piece_matrix[0] << (position[0] + x_offset)) & (1 << (board.get_width()))) return false;

	if (is_colliding(board, x_offset, y_offset)) {
		return false;
	}

	position[0] += x_offset;
	position[1] += y_offset;
	return true;
}


bool Piece::is_colliding(Board& board, int x_offset, int y_offset)
{
	return board.is_colliding(this, x_offset, y_offset);
}

std::vector<std::vector<bool>> Piece::get_piece_matrix()
{
	std::vector<std::vector<bool>> output(raw_piece_matrix().size(), std::vector<bool>(4, 0));

	for (int i = 0; i < output.size(); ++i) {
		for (int j = 0; j < output[i].size(); ++j) {
			output[i][j] = (raw_piece_matrix()[i] >> j) & 1;
		}
	}
    return output;
}
