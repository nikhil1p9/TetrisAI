#pragma once

#include "Game.h"
class EvaluationFunction
{
public:
	virtual float evaluate_board(Board board) = 0;
};

class SearchFunction
{
public:
	virtual Movement get_best_move(Game game, EvaluationFunction* evaluation_function) = 0;
};