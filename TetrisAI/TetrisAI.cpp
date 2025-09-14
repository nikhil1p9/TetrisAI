// TetrisAI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <future>   
#include <numeric>  
#include <chrono>   
#include <thread>
#include <algorithm>

#include "Renderer.h"
#include "Game.h"
#include "TPiece.h"
#include "Input.h"
#include "AI.h"
#include "DepthOneSearch.h"
#include "SimpleEvaluationFunction.h"
#include<ctime>

#define SEED time(nullptr)
//#define SEED 42
#define TICKRATE 100 // in milliseconds
//#define HEADLESS 
//#define TAKEINPUT

struct Score {
	int game_id;
	int score;

	Score(int game_id, int score) {
		this->game_id = game_id;
		this->score = score;
	}
};


struct Score run_game(EvaluationFunction& evaluation_function, int game_id)
{
	Renderer* renderer = Renderer::get();
	Game game(10, 24);

	SearchFunction& ai = *(new DepthOneSearch());


	auto last_tick = std::chrono::high_resolution_clock::now();
	while (!game.is_game_over()) {

#ifdef TAKEINPUT
		// for every movement in movements if Input::check(movement)  then game.apply_movement(movement);
		Input::poll_input();
		if (Input::is_key_pressed('a')) {
			game.apply_movement(Movement::LEFT);
		}
		if (Input::is_key_pressed('d')) {
			game.apply_movement(Movement::RIGHT);
		}
		if (Input::is_key_pressed('s')) {
			game.apply_movement(Movement::DOWN);
		}
		if (Input::is_key_pressed('S')) {
			game.apply_movement(Movement::SNAP_DOWN);
		}
		if (Input::is_key_pressed('w') || Input::is_key_pressed('r')) {
			game.apply_movement(Movement::ROTATE);
		}

		auto now = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tick).count() > TICKRATE) {
			last_tick = now;
			game.tick();
		}
		renderer->render(game);
#else // !TAKEINPUT


#ifndef HEADLESS
		auto now = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tick).count() > TICKRATE) {
			auto movement = ai.get_best_move(game, &evaluation_function);
			last_tick = now;
			game.apply_movement(movement);
			game.tick();
		}
		renderer->render(game);
		std::cout << evaluation_function.evaluate_board(game.get_board()) << std::endl;

#else
		
		auto movement = ai.get_best_move(game, &evaluation_function);
		game.apply_movement(movement);
		game.tick();
#endif
#endif

	}
	struct Score score(game_id,game.get_score());
	
	//renderer->game_over_screen(game);
	return score;
}

#define EPOCH 10
int main() {
	long long int average_time = 0;
	srand(SEED);
	run_game(*(new SimpleEvaluationFunction()), -1);
	std::vector<std::vector<float>> parameters_list(0, std::vector<float>(9, 0));
	std::vector<std::pair<float, int>> scores_list;
	for(int i = 0; i < EPOCH; ++i) {
		
		parameters_list.push_back({
			(float)(rand() % 100) / 10.0f,
			(float)(rand() % 100) / 10.0f,
			(float)(-(rand() % 100)) / 10.0f,
			(float)(rand() % 100) / 10.0f,

			(float)(rand() % 100) / 50.0f,
			(float)(rand() % 100) / 50.0f,
			(float)(rand() % 100) / 50.0f,
			(float)(rand() % 100) / 50.0f,
	
			(float)(rand() % 2)
		});
	}

	while (true) {
		std::vector<std::future<struct Score>> game_futures;
		for (int i = 0; i < EPOCH; i++) {
			int total_score = 0;
			EvaluationFunction& evaluation_function = *(new SimpleEvaluationFunction());
			((SimpleEvaluationFunction*)&evaluation_function)->parameters = parameters_list[i];

		/*	for (int j = 0; j < 10; j++) {
				game_futures.push_back(std::async(std::launch::async, run_game, std::ref(evaluation_function), i));
				
			}
			for(auto& fut : game_futures) {
				auto score = fut.get();
				total_score += score.score;
			}*/
			for (int j = 0; j < 10; j++) {
				total_score += run_game(evaluation_function, i).score;

			}
			/*for (auto& fut : game_futures) {
				auto score = fut.get();
				total_score += score.score;
			}*/
			scores_list.push_back({ total_score,i });
			game_futures.clear();
		}
		

		std::sort(scores_list.begin(), scores_list.end(), std::greater<std::pair<float, int>>());

		auto new_parameters_list = std::vector<std::vector<float>>(0, std::vector<float>(9, 0));

		for (int i = 0; i < EPOCH / 4; ++i) {
			new_parameters_list.push_back(parameters_list[scores_list[i].second]);
			new_parameters_list.push_back(parameters_list[scores_list[i].second]);
			new_parameters_list.push_back(parameters_list[scores_list[i].second]);
		}

		for (int i = EPOCH / 4; i < EPOCH; ++i) {
			std::vector<float> new_parameters(9, 0);
			for (int j = 0; j < 9; ++j) {
				//if (rand() % 5 == 0) { // mutation chance
					new_parameters[j] += ((float)(rand() % 2000) - 1000.0f) / 10.0f;
				//}
			}
			new_parameters_list.push_back(new_parameters);
		}

		// Edit each parameter slightly randomly
		for(int i = 0; i < new_parameters_list.size(); ++i) {
			for(int j = 0; j < new_parameters_list[i].size(); ++j) {
				//if (rand() % 10 == 0) { // mutation chance
					new_parameters_list[i][j] += ((float)(rand() % 2000) - 1000.0f) / 10000.0f;
				//}
			}

		}
		parameters_list = new_parameters_list;

		std::cout << "Best score: " << scores_list[0].first << " with parameters: ";
		for (float p : parameters_list[scores_list[0].second]) {
			std::cout << p << " ";
		}
		scores_list.clear();
		//std::cout << "Average score: " << (float)total_score / EPOCH << std::endl;

	}

}

