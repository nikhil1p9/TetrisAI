#pragma once
#include "Piece.h"
class InvertedLPiece :
    public Piece
{
public:
    std::vector<int> raw_piece_matrix() override
    {
        switch (rotation%4)
        {
        case 0:
            return {//
                0b0100,//
                0b0111
            };
		case 1:
			return { 0b0011, 0b0010, 0b0010 };
        case 2:
			return {0b0111, 0b0001 };
		case 3: 
			return { 0b0001, 0b0001, 0b0011 };
        default:
            break;
        }

	}
};

