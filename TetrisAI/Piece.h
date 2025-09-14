#pragma once
#include <vector>

class Piece
{
private:
	int position[2] = {0,-3};
	int rotation;

public:
	virtual std::vector<std::vector<bool>> raw_piece_matrix() = 0;
	inline void apply_gravity() { position[1]++; }

	inline int* get_position() { return position; }
	inline void set_position(int x, int y) { position[0] = x; position[1] = y; }

	bool rotate(std::vector<std::vector<bool>>& board);
	bool move(std::vector<std::vector<bool>>& board, int x_offset, int y_offset);
	bool is_colliding(std::vector<std::vector<bool>>& board, int x_offset = 0, int y_offset = 0);
	std::vector<std::vector<bool>> get_piece_matrix();
	
};
