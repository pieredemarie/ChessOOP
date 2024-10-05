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
	//virtual bool CanMoveFigure(int newX, int newY);
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
public:
	Cell* board[8][8];
	bool WhiteTurn;
public:
	Board(Cell* board[8][8], bool WhiteTurn);
	bool isCheckMate(Cell* board[8][8]);
	bool isCheck(Cell* board[8][8]);
	void ArrangeFigures(Cell* board[8][8]);
	void PrintBoard(Cell* board[8][8]);
};
class Knight:public Figure {
public:
	Knight(int x, int y, color COLOR) :Figure(x, y, type::KNIGHT, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};
class Rock:public Figure {
protected:
public:
	Rock(int x, int y, color COLOR) :Figure(x, y, type::ROCK, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};
class Pawn:public Figure {
protected:
	bool PawnTurn;//Превращение пешки
	bool CanTwoCellsGo;
public:
	Pawn(int x, int y,bool PawnTurn,bool CanTwoCellsGo, color COLOR) :Figure(x, y, type::PAWN, COLOR) {};
	//Bool CanMoveFigure(int dx, int dy) override;
};
class Queen : public Figure {
public:
	Queen(int x, int y, color COLOR) :Figure(x, y, type::QUEEN, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};
class King:public Figure {
protected:
	bool canCastle;//Рокировка
public:
	King(int x, int y, bool canCastle, color COLOR) :Figure(x, y, type::KING, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};
class Bishop:public Figure {
public:
	Bishop(int x, int y, color COLOR) :Figure(x, y, type::BISHOP, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};

/*bool Knight::CanMoveFigure(int dx, int dy) {
	return (abs(x - dx) * abs(y - dy)) == 2;
}
*/
void Board::PrintBoard(Cell* board[8][8]) {
	std::cout << "  A B C D E F G H" << std::endl;
	std::cout << "+-----------------+" << std::endl;

	for (int i = 0; i < 8; i++) {
		std::cout << i + 1 << "|";
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->figure.FigureType == Figure::type::ROCK) {
				if (board[i][j]->figure.FigureColor == Figure::color::WHITE) {
					std::cout << "R";
				}
				else {
					std::cout << "r";
				}
			}
			else if (board[i][j]->figure.FigureType == Figure::type::KNIGHT) {
				if (board[i][j]->figure.FigureColor == Figure::color::WHITE) {
					std::cout << "N";
				}
				else {
					std::cout << "n";
				}
			}
			else if (board[i][j]->figure.FigureType == Figure::type::BISHOP) {
				if (board[i][j]->figure.FigureColor == Figure::color::WHITE) {
					std::cout << "B";
				}
				else {
					std::cout << "b";
				}
			}
			else if (board[i][j]->figure.FigureType == Figure::type::QUEEN) {
				if (board[i][j]->figure.FigureColor == Figure::color::WHITE) {
					std::cout << "Q";
				}
				else {
					std::cout << "q";
				}
			}
			else if (board[i][j]->figure.FigureType == Figure::type::KING) {
				if (board[i][j]->figure.FigureColor == Figure::color::WHITE) {
					std::cout << "K";
				}
				else {
					std::cout << "k";
				}
			}
			else if (board[i][j]->figure.FigureType == Figure::type::PAWN) {
				if (board[i][j]->figure.FigureColor == Figure::color::WHITE) {
					std::cout << "P";
				}
				else {
					std::cout << "p";
				}
			}
			else {
				std::cout << "x";
			}
			std::cout << "|";
		}
		std::cout << std::endl;
		std::cout << "+-----------------+" << std::endl;
	}
}
void Board::ArrangeFigures(Cell* board[8][8]) {
	board[0][0]->figure = Rock(0, 0, Figure::color::WHITE);
	/*
	board[0][1].figure = Knight(0, 1, Figure::color::WHITE);
	board[0][2].figure = Bishop(0, 2, Figure::color::WHITE);
	board[0][3].figure = Queen(0, 3, Figure::color::WHITE);
	board[0][3].figure = King(0, 4,true, Figure::color::WHITE);
	board[0][4].figure = Rock(0, 0, Figure::color::WHITE);
	board[0][5].figure = Knight(0, 1, Figure::color::WHITE);
	board[0][6].figure = Bishop(0, 2, Figure::color::WHITE);
	board[0][7].figure = Queen(0, 3, Figure::color::WHITE);
	for (int i = 0; i < 8; i++) {
		board[1][i].figure = Pawn(1, i, false, true, Figure::color::WHITE);
		board[2][i].isAttacked = true;
	}
	board[7][0].figure = Rock(0, 0, Figure::color::WHITE);
	board[7][1].figure = Knight(0, 1, Figure::color::WHITE);
	board[7][2].figure = Bishop(0, 2, Figure::color::WHITE);
	board[7][3].figure = Queen(0, 3, Figure::color::WHITE);
	board[7][3].figure = King(0, 4, true, Figure::color::WHITE);
	board[7][4].figure = Rock(0, 0, Figure::color::WHITE);
	board[7][5].figure = Knight(0, 1, Figure::color::WHITE);
	board[7][6].figure = Bishop(0, 2, Figure::color::WHITE);
	board[7][7].figure = Queen(0, 3, Figure::color::WHITE);
	for (int i = 0; i < 8; i++) {
		board[6][i].figure = Pawn(1, i, false, true, Figure::color::WHITE);
		board[5][i].isAttacked = true;
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
	Cell* board[8][8];
	Board chesss(board,true);
	//chesss.ArrangeFigures(board);
	//chesss.PrintBoard(board);
}
