#pragma once
#include<vector>
#include "Piece.h"
class Board
{
private:
	int width;
	int height;
	std::vector<int>grid;

public:
	int delete_lines();
	Board copy();

	Board(int w, int h);

	bool drop_piece(Piece* hanging_piece);

	int get_width() { return width; }
	int get_height() { return height; }
	std::vector<int>& get_grid() {return grid;}

	bool is_colliding(Piece* piece, int x_offset = 0, int y_offset = 0);

	bool is_filled(int x, int y) { 
		return grid[y] & (1 << x);
	}

	bool set_cell(int x, int y,bool f) {

		if (x < 0 || x >= width || y < 0 || y >= height) return false;
		if(f)grid[y] |= (1 << x);
		else grid[y] &= ~(1 << x);
		return true;
	}

};

