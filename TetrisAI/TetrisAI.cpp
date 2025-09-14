// TetrisAI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <chrono>

#include "Renderer.h"
#include "Game.h"
#include "TPiece.h"
#include "Input.h"

#define TICKRATE 500 // in milliseconds

int main()
{
	Renderer* renderer = Renderer::get();
	Game game(10, 24);
	auto last_tick = std::chrono::high_resolution_clock::now();

	while (!game.is_game_over()) {
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
		if(std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tick).count() > TICKRATE) {
			last_tick = now;
			game.tick();
		}
		renderer->render(game);
	}
}

