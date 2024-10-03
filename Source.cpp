#include <iostream>
#include <math.h>

class Figure {
public:
	int x, y;
	enum class type { ROCK, BISHOP, PAWN, QUEEN, KING, KNIGHT };
	enum class color { WHITE, BLACK };
	type FigureType;
	color FigureColor;
public:
	Figure(int x, int y, type TYPE, color COLOR) {
		this->x = x;
		this->y = y;
		FigureType = TYPE;
		FigureColor = COLOR;
	};
	virtual bool CanMoveFigure(int newX, int newY);
	void MoveFigure(int newX, int newY);
	int getX(int x);
	int getY(int y);
	bool getColor(color FigureColor);
};
class Cell {
public:
	int x, y;
	Figure figure;
	bool isFree;
	bool isAttacked;
public:
	Cell(int x, int y,Figure figure,bool isFree);
	bool isCellFree(bool isFree);
};
class Board {
protected:
	Cell board[8][8];
	bool WhiteTurn;
public:
	Board(Cell board[8][8]);
	bool isCheckMate(Cell board[8][8]);
	bool isCheck(Cell board[8][8]);
	void ArrangeFigures(Cell board[8][8]);
	void PrintBoard(Cell board[8][8]);
};
class Knight:public Figure {
public:
	Knight(int x, int y, color COLOR) :Figure(x, y, type::KNIGHT, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Rock:public Figure {
protected:
public:
	Rock(int x, int y, color COLOR) :Figure(x, y, type::ROCK, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Pawn:public Figure {
protected:
	bool PawnTurn;//Превращение пешки
	bool CanTwoCellsGo;
public:
	Pawn(int x, int y,bool PawnTurn,bool CanTwoCellsGo, color COLOR) :Figure(x, y, type::PAWN, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Queen : public Figure {
	Queen(int x, int y, color COLOR) :Figure(x, y, type::QUEEN, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class King:public Figure {
protected:
	bool canCastle;//Рокировка
public:
	King(int x, int y, bool canCastle, color COLOR) :Figure(x, y, type::KING, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Bishop:public Figure {
	Bishop(int x, int y, color COLOR) :Figure(x, y, type::BISHOP, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};

bool Knight::CanMoveFigure(int dx, int dy) {
	return (abs(x - dx) * abs(y - dy)) == 2;
}
void Board::ArrangeFigures(Cell board[8][8]) {
	board[0][0].figure = Figure(0, 0, Figure::type::ROCK, Figure::color::WHITE);
/*
	board[0][1].figure = Figure(0, 1, Figure::type::KNIGHT, Figure::color::WHITE);
	board[0][2].figure = Figure(0, 2, Figure::type::BISHOP, Figure::color::WHITE);
	board[0][3].figure = Figure(0, 3, Figure::type::QUEEN, Figure::color::WHITE);
	board[0][4].figure = Figure(0, 4, Figure::type::KING, Figure::color::WHITE);
	board[0][5].figure = Figure(0, 5, Figure::type::BISHOP, Figure::color::WHITE);
	board[0][6].figure = Figure(0, 6, Figure::type::KNIGHT, Figure::color::WHITE);
	board[0][7].figure = Figure(0, 7, Figure::type::ROCK, Figure::color::WHITE);
	for (int i = 0; i < 8; i++) {
		board[1][i].figure = Figure(1, i, Figure::type::PAWN, Figure::color::WHITE);
	}

	board[7][0].figure = Figure(7, 0, Figure::type::ROCK, Figure::color::BLACK);
	board[7][1].figure = Figure(7, 1, Figure::type::KNIGHT, Figure::color::BLACK);
	board[7][2].figure = Figure(7, 2, Figure::type::BISHOP, Figure::color::BLACK);
	board[7][3].figure = Figure(7, 3, Figure::type::QUEEN, Figure::color::BLACK);
	board[7][4].figure = Figure(7, 4, Figure::type::KING, Figure::color::BLACK);
	board[7][5].figure = Figure(7, 5, Figure::type::BISHOP, Figure::color::BLACK);
	board[7][6].figure = Figure(7, 6, Figure::type::KNIGHT, Figure::color::BLACK);
	board[7][7].figure = Figure(7, 7, Figure::type::ROCK, Figure::color::BLACK);
	for (int i = 0; i < 8; i++) {
		board[6][i].figure = Figure(6, i, Figure::type::PAWN, Figure::color::BLACK);
	}
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j].isFree = true;
		}
	
	}
	*/
}

int main() {
	std::cout << "test" << std::endl;
}
