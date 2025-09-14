#include "Renderer.h"
#include "Piece.h"
#include <windows.h>
#include<iostream>
#include <sstream> // Required for std::stringstream
#include "TPiece.h"

Renderer* Renderer::Intance = nullptr;
Renderer::Renderer()
{
}

void Renderer::render(Game game)
{
	
    Board board_copy = game.board.copy();
    if (game.hanging_piece && !game.game_over) {
		board_copy.drop_piece(game.hanging_piece);
	}
    std::stringstream buffer;

    buffer << "Score: " << game.score << "\n";
    for (int i = 0; i < 2 * game.board.get_width() + 2; i++) {
        buffer << "-";
    }
    buffer << "\n";

    for (int i = 0; i < game.board.get_height(); ++i) {
        buffer << "|";
        for (int j = 0; j < game.board.get_width(); ++j) {
            if (board_copy.is_filled(j,i)) {
                buffer << "[]";
            }
            else {
                buffer << "  "; 
            }
        }
        buffer << "|\n";
    }

    for (int i = 0; i < 2 * game.board.get_width() + 2; i++) {
        buffer << "-";
    }
    buffer << "\n";

    clear_screen();
    std::cout << buffer.str();

    Sleep(1);
}

void Renderer::clear_screen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD homeCoords = { 0, 0 };
	DWORD charsWritten;

	FillConsoleOutputCharacter(hConsole, (TCHAR)' ', consoleSize, homeCoords, &charsWritten);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, homeCoords, &charsWritten);
	SetConsoleCursorPosition(hConsole, homeCoords);
}

void Renderer::game_over_screen(Game game)
{
    std::cout << "Game Over!\n";
	std::cout << "Final Score: " << game.score << "\n";
    std::cout << "Press enter to exit...\n";
	std::cin.get();
}
