#include <iostream>
#include <math.h>

class Figure {
public:
	int x, y;
	enum class type { ROCK, BISHOP, PAWN, QUEEN, KING, KNIGHT, NONE };
	enum class color { WHITE, BLACK , NONE};
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
	Cell(int x, int y, Figure figure, bool isFree) :
		x(x), y(y), figure(figure), isFree(isFree), isAttacked(false) {}
	bool isCellFree(bool isFree) {
		return isFree;
	};
};
class Board {
public:
	Cell* board[8][8];
	bool WhiteTurn;
public:
	Board(Cell* board[8][8], bool WhiteTurn) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				this->board[i][j] = board[i][j];
			}
		}
	}
	bool isCheckMate(Cell* board[8][8]);
	bool isCheck(Cell* board[8][8]);
	void ArrangeFigures(Cell* board[8][8]);
	void PrintBoard(Cell* board[8][8]);
};
class Knight :public Figure {
public:
	Knight(int x, int y, color COLOR) :Figure(x, y, type::KNIGHT, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};
class Rock :public Figure {
public:
	Rock(int x, int y, color COLOR) :Figure(x, y, type::ROCK, COLOR) {
	
	};
	//bool CanMoveFigure(int dx, int dy) override;
};
class Pawn :public Figure {
protected:
	bool PawnTurn;//Превращение пешки
	bool CanTwoCellsGo;
public:
	Pawn(int x, int y, bool PawnTurn, bool CanTwoCellsGo, color COLOR) :Figure(x, y, type::PAWN, COLOR) {};
	//Bool CanMoveFigure(int dx, int dy) override;
};
class Queen : public Figure {
public:
	Queen(int x, int y, color COLOR) :Figure(x, y, type::QUEEN, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};
class King :public Figure {
protected:
	bool canCastle;//Рокировка
public:
	King(int x, int y, bool canCastle, color COLOR) :Figure(x, y, type::KING, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};
class Bishop :public Figure {
public:
	Bishop(int x, int y, color COLOR) :Figure(x, y, type::BISHOP, COLOR) {};
	//bool CanMoveFigure(int dx, int dy) override;
};

/*bool Knight::CanMoveFigure(int dx, int dy) {
	return (abs(x - dx) * abs(y - dy)) == 2;
}
*/
void Board::PrintBoard(Cell* board[8][8]) {
	std::cout << "   A   B   C   D   E   F   G   H" << std::endl;
	std::cout << " ---------------------------------" << std::endl;

	for (int i = 7; i >= 0; i--) {
		std::cout << i+1 << " |";
		for (int j = 0; j < 8; ++j) {
			// Проверяем, есть ли фигура в ячейке
			if (!board[j][i]->isFree) { // Используем !isFree, чтобы проверить, есть ли фигура
				// Выводим символ фигуры
				switch (board[j][i]->figure.FigureType) {
				case Figure::type::PAWN:
					std::cout << (board[j][i]->figure.FigureColor == Figure::color::WHITE ? "P" : "p") << "  |";
					break;
				case Figure::type::ROCK:
					std::cout << (board[j][i]->figure.FigureColor == Figure::color::WHITE ? "R" : "r") << "  |";
					break;
				case Figure::type::KNIGHT:
					std::cout << (board[j][i]->figure.FigureColor == Figure::color::WHITE ? "N" : "n") << "  |";
					break;
				case Figure::type::BISHOP:
					std::cout << (board[j][i]->figure.FigureColor == Figure::color::WHITE ? "B" : "b") << "  |";
					break;
				case Figure::type::QUEEN:
					std::cout << (board[j][i]->figure.FigureColor == Figure::color::WHITE ? "Q" : "q") << "  |";
					break;
				case Figure::type::KING:
					std::cout << (board[j][i]->figure.FigureColor == Figure::color::WHITE ? "K" : "k") << "  |";
					break;
				}
			}
			else {
				std::cout << "   |"; // Если фигуры нет, выводим пустую ячейку
			}
		}
		std::cout << std::endl;
		std::cout << " ---------------------------------" << std::endl;
	}
}
void Board::ArrangeFigures(Cell* board[8][8]) {
	board[0][0]->figure = *new Rock(0, 0, Figure::color::WHITE);
	board[0][1]->figure = Knight(0, 0, Figure::color::WHITE);
	board[0][2]->figure = Bishop(0, 0, Figure::color::WHITE);
	board[0][3]->figure = Queen(0, 0, Figure::color::WHITE);
	board[0][4]->figure = King(0, 0,true, Figure::color::WHITE);
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

int main() {
	std::cout << "test" << std::endl;
	Cell* board[8][8];
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          board[i][j] = new Cell(i, j, Figure(i,j,Figure::type::NONE, Figure::color::NONE), true); // Создаем Cell с пустой фигурой
        }
      }
      Board chess(board, true); 
      chess.ArrangeFigures(board); 
	  chess.PrintBoard(board);
}
