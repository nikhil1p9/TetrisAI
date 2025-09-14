#pragma once
#include "Piece.h"
class TetrisPiece :
    public Piece
{
    public:
    std::vector<std::vector<bool>> raw_piece_matrix() override
    {
        return {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0}
        };
	}
};

