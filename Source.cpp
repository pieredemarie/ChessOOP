#include <iostream>

class Board {
protected:
	Cell* board[8][8];
public:
	Board(Cell* board[8][8]);
	void InitialiseBoard(Cell* board[8][8]);
	bool isCheckMate(Cell* board[8][8]);
	bool isCheck(Cell* board[8][8]);
	void ArrangeFigures(Cell* board[8][8]);
};
class Cell :public Board {
public:
	int x, y;
	bool isFree;
	Cell(int x, int y);
	bool isFree(int x, int y);
};
class Figure {
public: 
	int x, y;
	enum class type { ROCK, PAWN, QUEEN, KING, KNIGHT };
	enum class color { WHITE, BLACK };
public:
	Figure(int x, int y, type TYPE, color COLOR);
	bool CanMoveFigure(int newX, int newY);
	void MoveFigure(int newX, int newY);
};
class Knight : public Figure {
	int dx, dy;
};
class Rock : public Figure {
	int dx, dy;
};
class Pawn : public Figure {
	int dx, dy;
};
class Queen : public Figure {
	int dx, dy;
};
class King : public Figure {
	int dx, dy;
};
class Bishop :public Figure {
	int dx, dy;
};

bool isFree(bool isFree) {
	return isFree;
}
int main() {
	///
}