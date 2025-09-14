#include "Board.h"

int Board::delete_lines()
{
	int no_of_lines_deleted = 0;
	for(int i = 0; i < grid.size(); ++i) {
		bool full_line = ((1 << (width))-1 == grid[i]);
		if(full_line) {
			no_of_lines_deleted++;
			grid.erase(grid.begin() + i);
			grid.insert(grid.begin(), 0);
		}
		
	}
	return no_of_lines_deleted;
}

Board Board::copy()
{
	Board new_board(this->width, this->height);
	for(int i = 0; i < this->height; ++i) {
		new_board.grid[i] = this->grid[i];
	}
	return new_board;
}

Board::Board(int w, int h)
	: width(w), height(h), grid(h)
{
}

bool Board::drop_piece(Piece* hanging_piece)
{
	std::vector<std::vector<bool>> piece_matrix = hanging_piece->get_piece_matrix();
	int* position = hanging_piece->get_position();
	for (int i = 0; i < piece_matrix.size(); ++i) {
		for (int j = 0; j < piece_matrix[i].size(); ++j) {
			if (piece_matrix[i][j]) {
				int board_x = position[0] + j;
				int board_y = position[1] + i;
				if (board_y < 0) return false;
				if (board_x < 0 || board_x >= width || board_y < 0 || board_y >= height) return false;
				if (this->is_filled(board_x, board_y) == 1) return false;
				if (board_y >= 0 && board_y < height && board_x >= 0 && board_x < width)
					this->set_cell(board_x, board_y, true);
			}
		}
	}
	return true;
}

bool Board::is_colliding(Piece* piece, int x_offset, int y_offset)
{
	std::vector<int> raw_matrix = piece->raw_piece_matrix();
	int* position = piece->get_position();
	int board_x = position[0] + x_offset;
	for (int i = 0; i < raw_matrix.size(); ++i) {
		int board_y = position[1] + i + y_offset;

		if (board_y >= height) return true;
		if (board_x < 0) return true;

		int piece_row = raw_matrix[i] << (board_x);

		if ((piece_row & (0b111111 << width)))
			return true;

		if (board_y < 0) continue;
		if (grid[board_y] & piece_row) return true;
	}
	return false;
}