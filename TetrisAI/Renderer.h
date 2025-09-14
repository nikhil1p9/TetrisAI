#pragma once
#include "Game.h"

class Renderer
{
private:
	static Renderer* Intance;
	Renderer();

public:
	void render( Game game);
	void clear_screen();

	static Renderer* get() {
		if (Intance == nullptr) {
			Intance = new Renderer();
		}
		return Intance;
	}
};
