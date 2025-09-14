#pragma once
#include "AI.h"
#include <iostream>
class DepthOneSearch : public SearchFunction
{
	int get_best_score(Game game, EvaluationFunction* evaluation_function) {
		int x = game.next_piece->get_position()[0];
		int y = game.next_piece->get_position()[1];

		int best_x, best_r, best_evaluation_score = INT_MAX;
		for (int i = 0; i < 10; i++) {
			for (int rotate = 0; rotate < 4; rotate++) {
				game.next_piece->set_rotation(rotate);
				game.next_piece->set_position(i, y);
				if (game.next_piece->is_colliding(game.board, 0, 0)) {
					continue; // Skip if the piece collides with the board
				}
				while (!game.next_piece->is_colliding(game.board, 0, 1)) {
					game.next_piece->apply_gravity();
				}

				Board board_copy = game.board.copy();

				board_copy.drop_piece(game.hanging_piece);

				int score = evaluation_function->evaluate_board(board_copy);
				if (score < best_evaluation_score) {
					best_evaluation_score = score;
					best_x = i;
					best_r = rotate;
				}
			}
		}

		return best_evaluation_score;
	}

	Movement get_best_move(Game game, EvaluationFunction* evaluation_function) override {
		int x = game.hanging_piece->get_position()[0];
		int y = game.hanging_piece->get_position()[1];
		Movement best_move = Movement::SNAP_DOWN;

		int best_x,best_r, best_evaluation_score = INT_MAX;
		for (int i = 0; i < 10; i++) {
			for (int rotate = 0; rotate < 4; rotate++) {
				game.hanging_piece->set_rotation(rotate);
				game.hanging_piece->set_position(i, y);
				if (game.hanging_piece->is_colliding(game.board, 0, 0)) {
					continue; // Skip if the piece collides with the board
				}
				while (!game.hanging_piece->is_colliding(game.board, 0, 1)) {
					game.hanging_piece->apply_gravity();
				}
				Board board_copy = game.board.copy();

				board_copy.drop_piece(game.hanging_piece);
				int score = evaluation_function->evaluate_board(board_copy);
				if (score < best_evaluation_score) {
					best_evaluation_score = this->get_best_score(game, evaluation_function);
					
					best_x = i;
					best_r = rotate;
				}
			}
		}
		game.hanging_piece->set_position(best_x, y);
		game.hanging_piece->set_rotation(best_r);
		return best_move;
	}
};

