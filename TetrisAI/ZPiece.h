#pragma once
#include "Piece.h"
class ZPiece :
    public Piece
{
    public:
    std::vector<int> raw_piece_matrix() override
    {
        switch (this->rotation % 4)
        {
        case 0:
            return { 0b0110, 0b0011 };
		case 1:
			return { 0b0001, 0b0011, 0b0010 };
		case 2:
			return { 0b0110, 0b0011 };
		case 3:
			return { 0b0001, 0b0011, 0b0010 };
        default:
            break;
        }

    }
};

