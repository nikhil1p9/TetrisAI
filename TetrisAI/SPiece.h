#pragma once
#include "Piece.h"
class SPiece :
    public Piece
{
    public:
    std::vector<int> raw_piece_matrix() override
    {
        switch (this->rotation % 4)
        {
        case 0:
            return { 0b0010, 0b0011, 0b0001 };
		case 1:
			return { 0b0011, 0b0110 };
		case 2:
			return { 0b0010, 0b0011, 0b0001 };
		case 3:
			return { 0b0011, 0b0110 };
        default:
            break;
        }

    }
};

