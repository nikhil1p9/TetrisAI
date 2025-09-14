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
	std::vector<std::vector<bool>>board_copy(game.board.size(), std::vector<bool>(game.board[0].size(), false));
    for(int i = 0; i < game.board.size(); ++i) {
        for (int j = 0; j < game.board[i].size(); ++j) {
            board_copy[i][j] = game.board[i][j];
        }
	}
    if (game.hanging_piece) {
        std::vector<std::vector<bool>> piece_matrix = game.hanging_piece->get_piece_matrix();
        int* position = game.hanging_piece->get_position();
        for (int i = 0; i < piece_matrix.size(); ++i) {
            for (int j = 0; j < piece_matrix[i].size(); ++j) {
                if (piece_matrix[i][j]) {
                    if (position[1] + i < 0) continue;
                      board_copy[position[1] + i][position[0] + j] = true;
                }
            }
        }
	}
    std::stringstream buffer;

    buffer << "Score: " << game.score << "\n";

    for (int i = 0; i < 2 * game.board[0].size() + 2; i++) {
        buffer << "-";
    }
    buffer << "\n";

    for (int i = 0; i < game.board.size(); ++i) {
        buffer << "|";
        for (int j = 0; j < game.board[i].size(); ++j) {
            if (board_copy[i][j]) {
                buffer << "[]";
            }
            else {
                buffer << "  "; 
            }
        }
        buffer << "|\n";
    }

    for (int i = 0; i < 2 * game.board[0].size() + 2; i++) {
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
