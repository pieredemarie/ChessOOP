class Figure {
public:
	int x, y;
	enum class type { ROCK, BISHOP, PAWN, QUEEN, KING, KNIGHT, NONE };
	enum class color { WHITE, BLACK, NONE };
	type FigureType;
	color FigureColor;
public:
	Figure(int x, int y, type TYPE, color COLOR) {
		this->x = x;
		this->y = y;
		FigureType = TYPE;
		FigureColor = COLOR;
	};
	virtual bool CanMoveFigure(int newX, int newY) {
		return true;
	};
	int getX();
	int getY();
	bool getColor(color FigureColor);
};
class Cell {
public:
	int x, y;
	Figure* figure;
	bool isFree;
	bool isAttacked;
public:
	Cell(int x, int y, Figure figure, bool isFree) :
		x(x), y(y), figure(&figure), isFree(isFree), isAttacked(false) {}
	bool isCellFree() {
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
	bool isCellOccupied(int dx, int dy);
	void MakeMove(Cell* board[8][8]);
	void ArrangeFigures(Cell* board[8][8]);
	void GameStart(Cell* board[8][8]);
	void PrintBoard(Cell* board[8][8]);
};
class Knight :public Figure {
public:
	Knight(int x, int y, color COLOR) : Figure(x, y, type::KNIGHT, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Rock :public Figure {
public:
	Rock(int x, int y, color COLOR) :Figure(x, y, type::ROCK, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Pawn :public Figure {
public:
	bool PawnTurn;//Превращение пешки
	bool CanTwoCellsGo;
public:
	Pawn(int x, int y, bool PawnTurn, bool CanTwoCellsGo, color COLOR) :Figure(x, y, type::PAWN, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override 
	{
		if (Pawn::CanTwoCellsGo) {
			Pawn::CanTwoCellsGo = false;
			return (dx - x == 2 && dy == y ); 
		}
		else {
			return (abs(dx - x) == 1 && (dy == y));
		}
	};
	bool CanTakeFigure(int dx, int dy);
};
class Queen : public Figure {
public:
	Queen(int x, int y, color COLOR) :Figure(x, y, type::QUEEN, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class King :public Figure {
protected:
	bool canCastle;//Рокировка
public:
	King(int x, int y, bool canCastle, color COLOR) :Figure(x, y, type::KING, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
class Bishop :public Figure {
public:
	Bishop(int x, int y, color COLOR) :Figure(x, y, type::BISHOP, COLOR) {};
	bool CanMoveFigure(int dx, int dy) override;
};
