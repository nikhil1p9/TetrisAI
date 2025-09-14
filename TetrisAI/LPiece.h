#pragma once
#include "Piece.h"

class LPiece :
    public Piece
{
    public:
    /*std::vector<std::vector<bool>> raw_piece_matrix() override
    {
        return {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
			{0, 0, 0, 0}
        };
	}*/

        std::vector<int> raw_piece_matrix() override
        {
            switch (this->rotation % 4)
            {
            case 0:
                return { 0b0010, 0b0010, 0b0011 };
            case 1:
				return { 0b0001, 0b0111  };
			case 2:
				return { 0b0011, 0b0001, 0b001 };
			case 3:
				return { 0b0111, 0b0100 };
            default:
                break;
            }

        }
};

