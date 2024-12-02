#include "AllClasses.h"
#include <iostream>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "p - пешка\nr - ладья\nn - конь\nb - слон\nk - король\nq - ферзь" << std::endl;
	std::cout << "Заглавные буквы - белые фигуры, строчные - черные" << std::endl << std::endl << std::endl;
	Cell* board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = new Cell(i, j, Figure(i, j, Figure::type::NONE, Figure::color::NONE), true);
		}
	}
	Board chess(board, true);
	chess.ArrangeFigures(board);
	chess.PrintBoard(board);
	chess.GameStart();
}
