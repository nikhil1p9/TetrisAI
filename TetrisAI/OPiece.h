#pragma once
#include "Piece.h"
class OPiece :
    public Piece
{
    public:

        std::vector<int> raw_piece_matrix() override
        {
			return { 0b0011, 0b0011 };

        }
};

