#pragma once
#include<vector>
#include "Piece.h"
#include "LPiece.h"
#include "InvertedLPiece.h"
#include "OPiece.h"
#include "SPiece.h"
#include "TPiece.h"
#include "ZPiece.h"
#include "TetrisPiece.h"

enum class Movement {
	LEFT = 'a', RIGHT = 'd', DOWN = 's', ROTATE = 'r', SNAP_DOWN = 'S'
};

class Renderer;
class Game
{
private: 
	int score;
	Piece* hanging_piece;
	std::vector<std::vector<bool>> board;
	bool game_over = false;
	void spawn_piece();
	void delete_lines();

public:
	Game(int width = 10, int height = 24)
		: hanging_piece(nullptr), score(0), board(height, std::vector<bool>(width, false)) {
		spawn_piece();
	}	

	~Game() = default;

	bool is_game_over();
	void tick();
	void apply_movement(Movement movement);
	friend class Renderer;
};