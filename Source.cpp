#include <iostream>
#include <math.h>
#include <locale.h>
#include "Classes.h"
// Классы figure
int Figure::getX() {
	return x;
}
int Figure::getY() {
	return y;
}
bool Figure::getColor(color FigureColor) {
	return FigureColor == Figure::color::WHITE;
}
// дочерние классы Figure
bool Knight::CanMoveFigure(int dx, int dy, int x1, int y1) {
	return (abs(x - dx) * abs(y - dy)) == 2;
}

bool Pawn::CanTakeFigure(int dx, int dy) {
	return (abs(this->x - dx) == 1 && abs(this->y - dy) == 1);
}
bool Bishop::CanMoveFigure(int dx, int dy, int x1, int y1) {
	return (abs(dx - x) == abs(dy - y));
}
bool Queen::CanMoveFigure(int dx, int dy, int x1, int y1) {
	return ((abs(dx - x) == abs(dy - y)) || ((x == dx) && (y != dy)) || ((dy == y) && (x != dx)));
}
bool King::CanMoveFigure(int dx, int dy, int x1, int y1) {
	return ((abs(dx - x) == 1) || (abs(dy - y)) || (abs(dy - y) && abs(dx - x)));
}
bool Rock::CanMoveFigure(int dx, int dy, int x1, int y1) {
	return (((x == dx) && (y != dy)) || ((dy == y) && (x != dx)));
}
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
				switch ((*board[i][j]->figure).FigureType) {
				case Figure::type::PAWN:
					std::cout << ((*board[i][j]->figure).FigureColor == Figure::color::WHITE ? "P" : "p") << "  |";
					break;
				case Figure::type::ROCK:
					std::cout << ((*board[i][j]->figure).FigureColor == Figure::color::WHITE ? "R" : "r") << "  |";
					break;
				case Figure::type::KNIGHT:
					std::cout << ((*board[i][j]->figure).FigureColor == Figure::color::WHITE ? "N" : "n") << "  |";
					break;
				case Figure::type::BISHOP:
					std::cout << ((*board[i][j]->figure).FigureColor == Figure::color::WHITE ? "B" : "b") << "  |";
					break;
				case Figure::type::QUEEN:
					std::cout << ((*board[i][j]->figure).FigureColor == Figure::color::WHITE ? "Q" : "q") << "  |";
					break;
				case Figure::type::KING:
					std::cout << ((*board[i][j]->figure).FigureColor == Figure::color::WHITE ? "K" : "k") << "  |";
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
	board[0][0]->figure = new Rock(0, 0, Figure::color::WHITE);
	board[0][1]->figure = new Knight(0, 1, Figure::color::WHITE);
	board[0][2]->figure = new Bishop(0, 2, Figure::color::WHITE);
	board[0][3]->figure = new Queen(0, 3, Figure::color::WHITE);
	board[0][4]->figure = new King(0, 4, true, Figure::color::WHITE);
	board[0][5]->figure = new Bishop(0, 5, Figure::color::WHITE);
	board[0][6]->figure = new Knight(0, 6, Figure::color::WHITE);
	board[0][7]->figure = new Rock(0,7, Figure::color::WHITE);
	for (int i = 0; i < 8; i++) {
		board[1][i]->figure = new Pawn(1, i, false, true, Figure::color::WHITE);
		board[2][i]->isAttacked = true;
		board[6][i]->figure = new Pawn(1, i, false, true, Figure::color::BLACK);
		board[5][i]->isAttacked = true;
	}
	board[7][0]->figure = new Rock(7, 0, Figure::color::BLACK);
	board[7][1]->figure = new Knight(7, 1, Figure::color::BLACK);
	board[7][2]->figure = new Bishop(7, 2, Figure::color::BLACK);
	board[7][3]->figure = new Queen(7, 3, Figure::color::BLACK);
	board[7][4]->figure = new King(7, 4, true, Figure::color::BLACK);
	board[7][5]->figure = new Bishop(7, 5, Figure::color::BLACK);
	board[7][6]->figure = new Knight(7, 6, Figure::color::BLACK);
	board[7][7]->figure = new Rock(7, 7, Figure::color::BLACK);

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
bool Board::isCheck(Cell* board[8][8]) {
	return 0;
}
bool Board::isCheckMate(Cell* board[8][8]) {
	return 0;
}
void Board::MakeMove(Cell* board[8][8]) {
	std::string fromCoord, toCoord;
	std::cout << "Введите координату фигуры, которой хотите сходить: ";
	std::cin >> fromCoord;
	std::cout << "Введите координату клетки, в которую хотите сходить: ";
	std::cin >> toCoord;
	int x1, y1, x2, y2;
	x1 = fromCoord[0] - 'a';
	x2 = toCoord[0] - 'a';
	y1 = fromCoord[1] - '1';
	y2 = toCoord[1] - '1';
	int nx, ny;
	//std::cout << "y = "  << y1 << "," << "x = " << x1 << std::endl;
	//std::cout << y2 << "," << x2 << std::endl;
	if (x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0 && x1 < 8 && x2 < 8 && y1 < 8 && y2 < 8) {
		Cell* fromCell = board[y1][x1];
		Cell* toCell = board[y2][x2];
		if (fromCell->isFree) {
			std::cout << "Выбранная клетка пуста!" << std::endl;
			return;
		}
		bool validMove = false;
		Figure* figure = fromCell->figure;
		switch (fromCell->figure->FigureType) {
		case Figure::type::PAWN:
			if (abs(x2 - x1) == abs(y2 - y1) && abs(x2-x1) == 1) 
			{
				Figure* attackedFigure = toCell->figure;
				if (attackedFigure->FigureColor != figure->FigureColor && attackedFigure->FigureColor != Figure::color::NONE)
				{
					validMove = true;
				}
				else
				{
					std::cout << "Такой ход невозможен";
					validMove = false;
				}
			}
			else
			{
				//std::cout << "x2 = " << x2 << " y2 = " << y2 << std::endl;
				//std::cout << "x1 = " << x1 << " y1 = " << y1 << std::endl;
				validMove = fromCell->figure->CanMoveFigure(y2, x2,y1,x1) && board[y2][x2]->isFree && (fromCell->figure->FigureColor != toCell->figure->FigureColor);
			}
			break;
		case Figure::type::ROCK:
			validMove = fromCell->figure->CanMoveFigure(y2, x2, y1, x1) &&
				this->isPathSafe(x2, y2, x1, y1, fromCell->figure);
			break;
		case Figure::type::KNIGHT:
			validMove = fromCell->figure->CanMoveFigure(y2, x2,y1, x1) && (fromCell->figure->FigureColor != toCell->figure->FigureColor);
			break;
		case Figure::type::BISHOP:
			validMove = fromCell->figure->CanMoveFigure(y2, x2, y1, x1) &&
				this->isPathSafe(x2, y2, x1, y1, fromCell->figure);
			break;
		case Figure::type::QUEEN:
			validMove = fromCell->figure->CanMoveFigure(y2, x2, y1, x1) &&
				this->isPathSafe(x2, y2, x1, y1, fromCell->figure);
			break;
		case Figure::type::KING:
			validMove = fromCell->figure->CanMoveFigure(y2, x2, y1, x1) &&
				this->isPathSafe(x2, y2, x1, y1, fromCell->figure) && (fromCell->figure->FigureColor != toCell->figure->FigureColor);
			break;
		}
		if (validMove)
		{  
			toCell->figure = figure;
			fromCell->isFree = true;
			toCell->isFree = false;
			figure->x = x2;
			figure->y = y2;
		}
		else {
			std::cout << "Ход неверный" << std::endl;
		}
		
	}
}

void Board::GameStart(Cell* board[8][8]) {
	while (!isCheckMate(board)) {
		if (WhiteTurn) {
			std::cout << "Ход белых" << std::endl;
			MakeMove(board);
			PrintBoard(board);
		}
		else {
			std::cout << "Ход черных" << std::endl;
			MakeMove(board);
			PrintBoard(board);
		}
		WhiteTurn = !WhiteTurn;
	}
}
//
// Класс Figure
//bool Figure::CanMoveFigure(int dx, int dy) {
	//return 1;//Board::isCellOccupied(dx, dy);//и че это ты сделал гигант м ысли
//}
// 
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
	chess.GameStart(board);
}
