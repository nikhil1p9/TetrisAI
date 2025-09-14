#pragma once
#include "AI.h"

class SimpleEvaluationFunction :
    public EvaluationFunction
{
public:
	SimpleEvaluationFunction() {
		parameters = { 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	}
	std::vector<float> parameters;

    //void dfs(int i, int j, Board& board, Board& vis);
    float number_of_holes(Board board);
	float variance_of_heights(Board board);
	float aggregate_height(Board board);
	float no_of_lines_deleted(Board board);
	float is_last_column_empty(Board board);

	float evaluate_board(Board board) override {
		return 
			parameters[0] * pow(variance_of_heights(board), parameters[4]) +
			parameters[1] * pow(number_of_holes(board), parameters[5]) +
			parameters[2] * pow(no_of_lines_deleted(board), parameters[6]) +
			parameters[3] * pow(aggregate_height(board), parameters[7]) +
			parameters[8] * is_last_column_empty(board);
	}


};

