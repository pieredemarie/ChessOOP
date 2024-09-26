#include <iostream>

class Board {
protected:
	Cell board[8][8];
public:
	Board(Cell* board[8][8]);
	void InitialiseBoard(Cell* board[8][8]);
	bool isCheckMate(Cell* board[8][8]);
	bool isCheck(Cell* board[8][8]);
	void StartGame(Cell* board[8][8]);
	void ArrangeFigures(Cell* board[8][8]);
};
class Cell :public Board {
protected:
	int x, y;
	bool isFree;
public:
	Cell(int x, int y);
	bool isFree(int x, int y);
};
class Figure {
protected:
	int x, y;
	enum class type { ROCK,BISHOP, PAWN, QUEEN, KING, KNIGHT };
	enum class color { WHITE, BLACK };
	type FigureType;
	color FigureColor;
public:
	Figure(int x, int y, type TYPE, color COLOR);
	virtual bool CanMoveFigure(int newX, int newY);
	void MoveFigure(int newX, int newY);
};
class Knight : public Figure {
public:
	Knight(int x, int y, color COLOR) :Figure(x, y, type::KNIGHT, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Rock : public Figure {
public:
	Rock(int x, int y, color COLOR) :Figure(x, y, type::ROCK, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Pawn : public Figure {
protected:
	bool PawnTurn;//Превращение пешки
public:
	Pawn(int x, int y,bool PawnTurn, color COLOR) :Figure(x, y, type::PAWN, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Queen : public Figure {
	Queen(int x, int y, color COLOR) :Figure(x, y, type::QUEEN, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class King : public Figure {
protected:
	bool canCastle;//Рокировка
public:
	King(int x, int y, bool canCastle, color COLOR) :Figure(x, y, type::KING, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Bishop :public Figure {
	Bishop(int x, int y, color COLOR) :Figure(x, y, type::BISHOP, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};

bool isFree(bool isFree) {
	return isFree;
}
int main() {
	///
}
