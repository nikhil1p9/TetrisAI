#pragma once
#include <vector>

class Board;

class Piece
{
protected:
	int position[2] = {2,-3};
	int rotation;


public:
	virtual std::vector<int> raw_piece_matrix() = 0;

	inline void apply_gravity() { position[1]++; }

	inline int* get_position() { return position; }
	inline void set_position(int x, int y) { position[0] = x; position[1] = y; }
	void set_rotation(int rotation) { this->rotation = rotation % 4; }
	int get_rotation() { return this->rotation; }
	bool rotate(Board& board);
	bool move(Board& board, int x_offset, int y_offset);
	bool is_colliding(Board& board, int x_offset = 0, int y_offset = 0);
	std::vector<std::vector<bool>> get_piece_matrix();
	
};
