#include "Piece.h"
#include<iostream>
#include<algorithm>

bool Piece::rotate(std::vector<std::vector<bool>>& board)
{
	int old_rotation = this->rotation;
	this->rotation = (this->rotation + 1) % 4;
	if (this->is_colliding(board)) {
		this->rotation = old_rotation;
		return false;
	}
	return true;
}

bool Piece::move(std::vector<std::vector<bool>>& board, int x_offset, int y_offset)
{
	if (is_colliding(board, x_offset, y_offset)) {
		return false;
	}
	position[0] += x_offset;
	position[1] += y_offset;
	return true;
}


bool Piece::is_colliding(std::vector<std::vector<bool>>& board, int x_offset, int y_offset)
{
	std::vector<std::vector<bool>> piece_matrix = this->get_piece_matrix();
	int* position = this->get_position();
	for (int i = 0; i < piece_matrix.size(); ++i) {
		for (int j = 0; j < piece_matrix[i].size(); ++j) {
			if (piece_matrix[i][j]) {
				int board_x = position[0] + j + x_offset;
				int board_y = position[1] + i + y_offset;
				if (board_y < 0) return (!(board_x >= 0 and board_x<board[0].size()));
				if (board_x < 0 || board_x >= board[0].size() || board_y < 0 || board_y >= board.size() || board[board_y][board_x]) {
					return true;
				}
			}
		}
	}
	return false;
}

std::vector<std::vector<bool>> Piece::get_piece_matrix()
{
    std::vector<std::vector<bool>> output = this->raw_piece_matrix();
	int var = this->rotation;
	while (var--) {
		for (int i = 0; i < output.size(); ++i) {
			for (int j = i; j < output[i].size(); ++j) {
				int temp = output[i][j];
				output[i][j] = output[j][i];
				output[j][i] = temp;
			}
		}
		for (int i = 0; i < output.size(); ++i) {
			std::reverse(output[i].begin(), output[i].end());
		}
	}
    return output;
}
