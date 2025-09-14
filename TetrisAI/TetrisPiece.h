#pragma once
#include "Piece.h"
class TetrisPiece :
    public Piece
{
    std::vector<int> raw_piece_matrix() override
    {
        switch (this->rotation % 4)
        {
        case 0:
            return { 0b0001, 0b0001, 0b0001, 0b0001 };
		case 1:
			return { 0b1111 };
		case 2:
			return { 0b0001, 0b0001, 0b0001, 0b0001 };
		case 3:
			return { 0b1111 };
        default:
            break;
        }

    }
};

