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
	virtual bool CanMoveFigure(int newX, int newY,int oldX,int oldY) {
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
	bool isPathSafe(int dx, int dy, int x1, int y1, Figure* figure) {
		if (figure->FigureType == Figure::type::BISHOP)
		{
			int nx = x1;
			int ny = y1;

			int deltaX = (dx > x1) ? 1 : -1;
			int deltaY = (dy > y1) ? 1 : -1;

			nx += deltaX;
			ny += deltaY;
			while (nx != dx && ny != dy) {
				if (board[ny][nx]->figure->FigureColor == figure->FigureColor) {
					return false;
				}
				nx += deltaX;
				ny += deltaY;
			}
			return true; 
		}
		else if (figure->FigureType == Figure::type::ROCK)
		{
			int nx, ny;
			nx = x1;
			ny = y1;
			if (x1 - dx != 0) { // y1 == y2;
				int deltaX = (dx > x1) ? 1 : -1;
				while (nx != dx) {
					if (board[ny][nx]->figure->FigureColor == figure->FigureColor)
					{
						return false;
					}
					nx += deltaX;
				}
			}
			else if (y1 - dy != 0)
			{
				int deltaY = (dy > y1) ? 1 : -1;
				while (ny != dy)
				{
					if (board[ny][nx]->figure->FigureColor == figure->FigureColor)
					{
						return false;
					}
					ny += deltaY;
				}
			}
		}
		else if (figure->FigureType == Figure::type::QUEEN)
		{
			return true;
		}
		else
		{
			return true;
		}
	}
	void MakeMove(Cell* board[8][8]);
	void ArrangeFigures(Cell* board[8][8]);
	void GameStart(Cell* board[8][8]);
	void PrintBoard(Cell* board[8][8]);
};
class Knight :public Figure {
public:
	Knight(int x, int y, color COLOR) : Figure(x, y, type::KNIGHT, COLOR) {};
	bool CanMoveFigure(int dx, int dy,int x1,int y1) override;
	
};
class Rock :public Figure {
public:
	Rock(int x, int y, color COLOR) :Figure(x, y, type::ROCK, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1) override;
	
};
class Pawn :public Figure {
public:
	bool PawnTurn;//Превращение пешки
	bool CanTwoCellsGo;
public:
	Pawn(int x, int y, bool PawnTurn, bool CanTwoCellsGo, color COLOR) :Figure(x, y, type::PAWN, COLOR) {};
	bool CanMoveFigure(int x2, int y2,int x1,int y1) override 
	{
		if (Figure::FigureColor == Figure::color::WHITE)
		{
			if (Pawn::CanTwoCellsGo) {
				if (x2 - x1 == 1 && y1 == y2)
				{
					return true;
				}
				else if (x2 - x1 == 2 && y1 == y2)
				{
					CanTwoCellsGo = false;
					return true;
				}
			}
			else {
				return (x2 - x1 == 1 && y1 == y2);
			}
		}
		else if (Figure::FigureColor == Figure::color::BLACK)
		{
			if (Pawn::CanTwoCellsGo) {
				if (x2 - x1 == -1 && y1 == y2)
				{
					return true;
				}
				else if (x2 - x1 == -2 && y1 == y2)
				{
					CanTwoCellsGo = false;
					return true;
				}
			}
			else {
				return (x2 - x1 == -1 && y1 == y2);
			}
		}
	};
	bool CanTakeFigure(int dx, int dy);

};
class Queen : public Figure {
public:
	Queen(int x, int y, color COLOR) :Figure(x, y, type::QUEEN, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1) override;

};
class King :public Figure {
protected:
	bool canCastle;//Рокировка
public:
	King(int x, int y, bool canCastle, color COLOR) :Figure(x, y, type::KING, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1) override;

};
class Bishop :public Figure {
public:
	Bishop(int x, int y, color COLOR) :Figure(x, y, type::BISHOP, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1) override;
};
