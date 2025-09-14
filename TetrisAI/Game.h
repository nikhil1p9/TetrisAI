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
#include "Board.h"

enum class Movement {
	LEFT = 'a', RIGHT = 'd', DOWN = 's', ROTATE = 'r', SNAP_DOWN = 'S'
};

class DepthOneSearch;
class Renderer;
class Game
{
private: 
	int score;
	Piece* hanging_piece;
	Piece* next_piece = nullptr;
	Board board;
	bool game_over = false;
	void spawn_piece();
	void delete_lines();

public:
	Game(int width = 10, int height = 24)
		: hanging_piece(nullptr), score(0), board(width, height) {
		spawn_piece();
		spawn_piece();
	}	

	~Game() = default;

	bool is_game_over();
	void tick();
	void apply_movement(Movement movement);
	Board& get_board() { return board; }
	inline int get_score() { return score; }
	friend class Renderer;
	friend class DepthOneSearch;
};