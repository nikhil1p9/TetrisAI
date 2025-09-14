#pragma once
#include <conio.h>
class Input
{
private:
	static bool* input_buffer;

public:
	static void poll_input() {
		for (int i = 0; i < 256; ++i) {
			input_buffer[i] = false;
		}
		if  (_kbhit()) {
			input_buffer[_getch()] = true;
		}
	}

	static bool is_key_pressed(int key) {
		return input_buffer[key];
	}
};