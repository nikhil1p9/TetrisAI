#pragma once
#include "Piece.h"
class OPiece :
    public Piece
{
    public:
    std::vector<std::vector<bool>> raw_piece_matrix() override
    {
        return {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        };
	}
};

