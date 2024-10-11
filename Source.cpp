#include <iostream>
#include <math.h>
#include <locale.h>
#include "Classes.h"
// класс Board
bool Board::isCellOccupied(int dx, int dy) {
	return !(board[dx][dy]->isCellFree());
}
void Board::PrintBoard(Cell* board[8][8]) {
	std::cout << "    A   B   C   D   E   F   G   H   " << std::endl;
	std::cout << " -----------------------------------" << std::endl;
	for (int i = 7; i >= 0; i--) {
		std::cout << i + 1 << " |";
		for (int j = 0; j < 8; j++) {
			if (!board[i][j]->isFree) {
				switch (board[i][j]->figure.FigureType) {
				case Figure::type::PAWN:
					std::cout << (board[i][j]->figure.FigureColor == Figure::color::WHITE ? "P" : "p") << "  |";
					break;
				case Figure::type::ROCK:
					std::cout << (board[i][j]->figure.FigureColor == Figure::color::WHITE ? "R" : "r") << "  |";
					break;
				case Figure::type::KNIGHT:
					std::cout << (board[i][j]->figure.FigureColor == Figure::color::WHITE ? "N" : "n") << "  |";
					break;
				case Figure::type::BISHOP:
					std::cout << (board[i][j]->figure.FigureColor == Figure::color::WHITE ? "B" : "b") << "  |";
					break;
				case Figure::type::QUEEN:
					std::cout << (board[i][j]->figure.FigureColor == Figure::color::WHITE ? "Q" : "q") << "  |";
					break;
				case Figure::type::KING:
					std::cout << (board[i][j]->figure.FigureColor == Figure::color::WHITE ? "K" : "k") << "  |";
					break;
				}
			}
			else {
				std::cout << "   |";
			}
		}
		std::cout << i + 1;
		std::cout << std::endl;
		std::cout << " -----------------------------------" << std::endl;
	}
	std::cout << "    A   B   C   D   E   F   G   H   " << std::endl;
}
void Board::ArrangeFigures(Cell* board[8][8]) {
	board[0][0]->figure = *new Rock(0, 0, Figure::color::WHITE);
	board[0][1]->figure = Knight(0, 0, Figure::color::WHITE);
	board[0][2]->figure = Bishop(0, 0, Figure::color::WHITE);
	board[0][3]->figure = Queen(0, 0, Figure::color::WHITE);
	board[0][4]->figure = King(0, 0, true, Figure::color::WHITE);
	board[0][5]->figure = Bishop(0, 0, Figure::color::WHITE);
	board[0][6]->figure = Knight(0, 0, Figure::color::WHITE);
	board[0][7]->figure = Rock(0, 0, Figure::color::WHITE);
	for (int i = 0; i < 8; i++) {
		board[1][i]->figure = Pawn(1, i, false, true, Figure::color::WHITE);
		board[2][i]->isAttacked = true;
		board[6][i]->figure = Pawn(1, i, false, true, Figure::color::BLACK);
		board[5][i]->isAttacked = true;
	}
	board[7][0]->figure = Rock(0, 0, Figure::color::BLACK);
	board[7][1]->figure = Knight(0, 0, Figure::color::BLACK);
	board[7][2]->figure = Bishop(0, 0, Figure::color::BLACK);
	board[7][3]->figure = Queen(0, 0, Figure::color::BLACK);
	board[7][4]->figure = King(0, 0, true, Figure::color::BLACK);
	board[7][5]->figure = Bishop(0, 0, Figure::color::BLACK);
	board[7][6]->figure = Knight(0, 0, Figure::color::BLACK);
	board[7][7]->figure = Rock(0, 0, Figure::color::BLACK);

	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j]->isFree = true;
		}
	}
	for (int i = 0; i < 8; i++) {
		board[0][i]->isFree = false;
		board[7][i]->isFree = false;
		board[1][i]->isFree = false;
		board[6][i]->isFree = false;
	}
}
//
// дочерние классы Figure
bool Knight::CanMoveFigure(int dx, int dy) {
	return (abs(x - dx) * abs(y - dy)) == 2;
}
bool Pawn::CanMoveFigure(int dx, int dy, bool CanTwoCellsGo) {
	if (CanTwoCellsGo) {
		return (abs(dx - x) == 2 && (dy == y));
	}
	else {
		return (abs(dx - x) == 1 && (dy == y));
	}
}
bool Bishop::CanMoveFigure(int dx, int dy) {
	return (abs(dx - x) == abs(dy - y));
}
bool Queen::CanMoveFigure(int dx, int dy) {
	return ((abs(dx - x) == abs(dy - y)) || ((x == dx) && (y != dy)) || ((dy == y) && (x != dx)));
}
bool King::CanMoveFigure(int dx, int dy) {
	return ((abs(dx - x) == 1) || (abs(dy - y)) || (abs(dy - y) && abs(dx - x)));
}
bool Rock::CanMoveFigure(int dx, int dy) {
	return (((x == dx) && (y != dy)) || ((dy == y) && (x != dx)));
}
int main() {
	setlocale(LC_ALL, "rus");
	std::cout << "p - пешка\nr - ладья\nn - конь\nb - слон\nk - король\nq - ферзь" << std::endl;
	std::cout << "Заглавные буквы - белые фигуры, строчные - черные" << std::endl << std::endl << std::endl;
	Cell* board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = new Cell(i, j, Figure(i, j, Figure::type::NONE, Figure::color::NONE), true); // Создаем Cell с пустой фигурой
		}
	}
	Board chess(board, true);
	chess.ArrangeFigures(board);
	chess.PrintBoard(board);
}
