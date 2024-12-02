#include <math.h>
#include <iostream>
class Board;
class Figure;
class Cell;
enum class type { ROCK, BISHOP, PAWN, QUEEN, KING, KNIGHT, NONE };
enum class color { WHITE, BLACK, NONE };
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
	virtual bool CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board) {
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
class King :public Figure {
public:
	bool CanCastle;//Рокировка
public:
	bool isCheck;
	King(int x, int y, bool isCastle, color COLOR) :Figure(x, y, type::KING, COLOR) {};
	bool CanMoveFigure(int end_row, int end_col, int start_row, int start_col, Board* board) override;
	bool CouldCastle(Board board, int king_row, int king_col, int rook_row, int rook_col);
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
		this->WhiteTurn = WhiteTurn;
	}
	bool isCheckMate(Figure::color PlayColor);
	bool isCheck(Figure::color PlayColor);
	bool isStelamate(Figure::color PlayColor);
	std::string GetFigureString(int row, int column);
	bool isCellAttacked(int row, int col, Figure::color PlayColor)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) {
				
				if (board[i][j]->figure->FigureType != Figure::type::NONE && board[i][j]->figure->FigureColor != PlayColor)
				{
					if (board[i][j]->figure->CanMoveFigure(i, j, row, col, this))
					{
						/*
						bool test = board[i][j]->figure->CanMoveFigure(i, j, row, col, this); // проверить что за фигура бьет короля когда он ее берет 
						std::cout << i << ',' << j << std::endl;
						std::cout << "клетка атакована: " << row << col << std::endl;
						std::cout << GetFigureString(i, j) << std::endl;
						std::cout << GetFigureString(6, 5) << std::endl;
						//std::cout << board[i][j]->figure->CanMoveFigure(i, j, row, col, this) << std::endl;
						*/
						return true;
						
					}
				}
			}
		}
		return false;
	}
	void SwitchPieces(int start_row, int start_col, int finish_row, int finish_col, Figure* figure);
	void MakeMove();
	void ArrangeFigures(Cell* board[8][8]);
	void GameStart();
	void PrintBoard(Cell* board[8][8]);
	void ShortCastling(int start_row, int start_col, int finish_row, int finish_col);
	void LongCastling(int start_row, int start_col, int finish_row, int finish_col);
};
class Knight :public Figure {
public:
	Knight(int x, int y, color COLOR) : Figure(x, y, type::KNIGHT, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1, Board* board) override;
};
class Pawn :public Figure {
public:
	bool PawnTurn;//Превращение пешки
	bool CanTwoCellsGo;
	bool enPassAvailable;
public:
	Pawn(int x, int y, bool PawnTurn, bool CanTwoCellsGo, bool enPassAvailable, color COLOR) :Figure(x, y, type::PAWN, COLOR) {};
	bool CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board) override;
};
class Rock :public Figure {
public:
	bool canCastle;
public:
	Rock(int x, int y, bool canCastle,color COLOR) :Figure(x, y, type::ROCK, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1, Board* board) override;
};
class Bishop :public Figure {
public:
	Bishop(int x, int y, color COLOR) :Figure(x, y, type::BISHOP, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1, Board* board) override;
};

class Queen : public Figure {
public:
	Queen(int x, int y, color COLOR) :Figure(x, y, type::QUEEN, COLOR) {};
	bool CanMoveFigure(int dx, int dy, int x1, int y1, Board* board) override;
};
/// Может сделать заготовки на шахматы капабланки (готические шахматы
class Archiepiskop : public Figure 
{
	Archiepiskop(int x,int y,color COLOR) : Figure(x, y, type::KNIGHT, COLOR) {};
	bool CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board) override;
};
class Chancellor : public Figure
{
	Chancellor(int x, int y, color COLOR) : Figure(x, y, type::BISHOP, COLOR) {};
	bool CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board) override;
};
bool Archiepiskop::CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board)
{
	return true; // если понравится идея то реализую
}
bool Chancellor::CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board)
{
	return true; // если понравится идея то реализую
};
class Ai
{
public:

	Ai(Board board);
	void FindAppropriateMove(Cell* firstBoard[8][8])
	{
		Cell* copyboard[8][8];
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				copyboard[i][j] = firstBoard[i][j];
			}
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				/// 
			}
		}
	}
};
bool Knight::CanMoveFigure(int start_row, int start_col, int end_row, int end_col, Board* bor)
{
	if (bor->board[end_row][end_col]->figure->FigureColor == this->FigureColor)
	{
		return false; 
	}
	else
	{
		if (end_row == start_row - 2 && (end_col == start_col - 1 || end_col == start_col + 1)) return true;
		if (end_row == start_row - 1 && (end_col == start_col - 2 || end_col == start_col + 2)) return true;
		if (end_row == start_row + 1 && (end_col == start_col - 2 || end_col == start_col + 2)) return true;
		if (end_row == start_row + 2 && (end_col == start_col - 1 || end_col == start_col + 1)) return true;
		return false;
	}
}

bool King::CanMoveFigure(int start_row, int start_col, int end_row, int end_col, Board* board)
{
	Figure* temp = board->board[end_row][end_col]->figure;
	if (temp->FigureType == Figure::type::ROCK)
	{
		Rock* rockFigure = dynamic_cast<Rock*>(temp);
		if (this->CanCastle && rockFigure->canCastle)
			return true;
		else
			return false;
	}
	int dRow = abs(end_row - start_row);
	int dCol = abs(end_col - start_col);

	if (dCol <= 1 && dRow <= 1)
	{
		if (board->board[end_row][end_col]->figure->FigureColor != this->FigureColor || board->board[end_row][end_col]->figure->FigureType == Figure::type::NONE)
		{
			Figure* targetFigure = board->board[end_row][end_col]->figure;
			board->board[end_row][end_col]->figure = this;
			board->board[start_row][start_col]->figure = targetFigure;
			//SwitchPieces(start_row, start_col, end_row, end_col, this);
			bool isAttacked = board->isCellAttacked(end_row, end_col, this->FigureColor);
			//board.SwitchPieces(start_row, start_col, end_row, end_col, AimedCell); 
			board->board[start_row][start_col]->figure = this;
			board->board[end_row][end_col]->figure = targetFigure;
			return !isAttacked;
		}
	}
	return false;
}
bool Queen::CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board)
{
	int dRow = abs(finish_row - start_row);
	int dCol = abs(finish_col - start_col);
	if (dCol == 0 && dRow == 0)
	{
		return false;
	}
	if (dRow == dCol || finish_row == start_row || finish_col == start_col)
	{
		int stepR = (dRow > 0) ? (finish_row > start_row ? 1 : -1) : 0;
		int stepL = (dCol > 0) ? (finish_col > start_col ? 1 : -1) : 0;

		int r = start_row + stepR;
		int c = start_col + stepL;

		while (r != finish_row || c != finish_col)
		{
			if (board->board[r][c]->figure->FigureType != Figure::type::NONE)
			{
				return false;
			}
			r += stepR;
			c += stepL;
		}
		if (board->board[finish_row][finish_col]->figure->FigureColor == this->FigureColor && board->board[finish_row][finish_col]->figure->FigureType != Figure::type::NONE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Rock::CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board)
{
	int dRow = abs(finish_row - start_row);
	int dCol = abs(finish_col - start_col);
	if ((dRow > 0 && dCol == 0) || (dCol > 0 && dRow == 0))
	{
		int stepR = (dRow > 0) ? (finish_row > start_row ? 1 : -1) : 0;
		int stepC = (dCol > 0) ? (finish_col > start_col ? 1 : -1) : 0;
		int i = start_row + stepR;
		int j = start_col + stepC;
		while (i != finish_row || j != finish_col)
		{
			if (board->board[i][j]->figure->FigureColor == this->FigureColor)
			{
				return false;
			}
			i += stepR;
			j += stepC;
		}
		if (board->board[finish_row][finish_col]->figure->FigureColor == this->FigureColor)
		{
			return false;
		}
		return true;
	}
	return false;
}
bool King::CouldCastle(Board board,int king_row,int king_col,int rook_row,int rook_col)
{
	if (!CanCastle)
		return false;
	if (board.board[rook_row][rook_col]->figure->FigureType != Figure::type::ROCK)
		return false;
	Rock* rockFigure = dynamic_cast<Rock*>(board.board[rook_row][rook_col]->figure);
	if (!rockFigure->canCastle)
		return false;
	int start_col = (king_col > rook_col) ? rook_col : king_col;
	int end_col = (king_col > rook_col) ? king_col : rook_col;
	for (int i = start_col+1; i < end_col; i++)
	{
		if (board.board[king_row][i]->figure->FigureType != Figure::type::NONE)
			return false;
	}
	return true;
}
bool Pawn::CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board)
{
	int dRow = (finish_row - start_row);
	int dCol = (finish_col - start_col);

	if (dRow == 0) 
	{
		return false;
	}
	if (this->FigureColor == color::WHITE) //случай для белой пешки
	{
		if (dRow == 1 && dCol == 0 && board->board[finish_row][finish_col]->figure->FigureType == type::NONE)
		{
			return true;
		}
		if (start_row == 1 && dRow == 2 && dCol == 0 && board->board[finish_row][finish_col]->figure->FigureType == type::NONE && board->board[finish_row - 1][finish_col]->figure->FigureType == type::NONE)
		{
			this->CanTwoCellsGo = false;
			this->enPassAvailable = true;
			return true;
		}
		if (abs(dCol) == 1 && dRow == 1) // взятие пешки
		{
			if (board->board[finish_row][finish_col]->figure->FigureType != type::NONE)
			{
				if (board->board[finish_row][finish_col]->figure->FigureColor != this->FigureColor)
				{
					return true;
				}
			}
		}
		if (board->board[start_row][finish_col]->figure->FigureType != type::NONE && dRow == 1 && dCol == 1) // взятие на проходе
		{
			Figure* tFigure = board->board[start_row][finish_col]->figure;
			if (tFigure->FigureType == type::PAWN && board->board[start_row][finish_col]->figure->FigureColor != this->FigureColor)
			{
				Pawn* pawnFigure = dynamic_cast<Pawn*>(tFigure);
				if (pawnFigure->enPassAvailable)
				{
					return true;
				}
			}
		}
		return false;
	}
	else if (this->FigureColor == color::BLACK)
	{
		if (dRow == -1 && dCol == 0 && board->board[finish_row][finish_col]->figure->FigureType == type::NONE)
		{
			return true;
		}
		if (start_row == 6 && dRow == -2 && dCol == 0 && board->board[finish_row][finish_col]->figure->FigureType == type::NONE && board->board[finish_row +1][finish_col + 1]->figure->FigureType == type::NONE)
		{
			this->CanTwoCellsGo = false;
			this->enPassAvailable = true;
			return true;
		}
		if (abs(dCol) == 1 && abs(dRow) == 1)
		{
			if (board->board[finish_row][finish_col]->figure->FigureType != type::NONE)
			{
				if (board->board[finish_row][finish_col]->figure->FigureColor != this->FigureColor)
				{
					return true;
				}
			}
		}
		if (board->board[start_row][finish_col]->figure->FigureType != type::NONE && abs(dCol) == 1 && abs(dRow) == 1)
		{
			Figure* tFigure = board->board[start_row][finish_col]->figure;
			if (tFigure->FigureType == type::PAWN && board->board[start_row][finish_col]->figure->FigureColor != this->FigureColor)
			{
				Pawn* pawnFigure = dynamic_cast<Pawn*>(tFigure);
				if (pawnFigure->enPassAvailable)
				{
					return true;
				}
			}
		}
		return false;
	}
}
std::string Board::GetFigureString(int row, int column) {
	

	std::string figureType = "";
	switch (board[row][column]->figure->FigureType) {
	case Figure::type::KING:
		figureType = "King";
		break;
	case Figure::type::QUEEN:
		figureType = "Queen";
		break;
	case Figure::type::ROCK:
		figureType = "Rook";
		break;
	case Figure::type::BISHOP:
		figureType = "Bishop";
		break;
	case Figure::type::KNIGHT:
		figureType = "Knight";
		break;
	case Figure::type::PAWN:
		figureType = "Pawn";
		break;
	default:
		figureType = "NONE";
		break;
	}

	return figureType;
}
bool Bishop::CanMoveFigure(int start_row, int start_col, int finish_row, int finish_col, Board* board)
{
	int dRow = abs(finish_row - start_row);
	int dCol = abs(finish_col - start_col);

	if (dRow == dCol)
	{
		int stepR = (finish_row > start_row) ? 1 : -1;
		int stepC = (finish_col > start_col) ? 1 : -1;
		int r = start_row + stepR;
		int c = start_col + stepC;
		while (r != finish_row && c != finish_col)
		{
			if (r >= 0 && r < 8 && c >= 0 && c < 8)
			{
				if (board->board[r][c]->figure->FigureColor == this->FigureColor && board->board[r][c]->figure->FigureType != Figure::type::NONE)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
			r += stepR;
			c += stepC;
		}
		if (board->board[finish_row][finish_col]->figure->FigureColor != this->FigureColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
bool Board::isCheck(Figure::color PlayColor)
{
	bool king = false;
	int king_row = -1;
	int king_col = -1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->figure->FigureType == Figure::type::KING && board[i][j]->figure->FigureColor == PlayColor)
			{
				king = true;
				king_row = i;
				king_col = j;
				break;
			}
			if (king)
				break;
		}
		if (king)
			break;
	}
	return isCellAttacked(king_row, king_col, PlayColor);
}
void Board::ShortCastling(int start_row, int start_col, int finish_row, int finish_col)
{
	board[start_row][start_col]->figure->FigureType = Figure::type::NONE;
	board[finish_row][finish_col]->figure->FigureType = Figure::type::NONE;
	board[start_row][start_col]->isFree = true;
	board[finish_row][finish_col]->isFree = true;
	if (start_row == 0)
	{
		board[0][6]->figure = new King(0, 6, false, Figure::color::WHITE);
		board[0][5]->figure = new Rock(0, 5, false, Figure::color::WHITE);
		board[0][5]->isFree = false;
		board[0][6]->isFree = false;
	}
	else
	{
		board[7][6]->figure = new King(7, 6, false, Figure::color::BLACK);
		board[7][5]->figure = new Rock(0, 5, false, Figure::color::BLACK);
		board[7][5]->isFree = false;
		board[7][6]->isFree = false;
	}
}
void Board::LongCastling(int start_row, int start_col, int finish_row, int finish_col)
{
	board[start_row][start_col]->figure->FigureType = Figure::type::NONE;
	board[finish_row][finish_col]->figure->FigureType = Figure::type::NONE;
	board[start_row][start_col]->isFree = true;
	board[finish_row][finish_col]->isFree = true;
	if (start_row == 0)
	{
		board[0][2]->figure = new King(0, 6, false, Figure::color::WHITE);
		board[0][3]->figure = new Rock(0, 5, false, Figure::color::WHITE);
		board[0][2]->isFree = false;
		board[0][3]->isFree = false;
	}
	else
	{
		board[7][2]->figure = new King(7, 6, false, Figure::color::BLACK);
		board[7][3]->figure = new Rock(0, 5, false, Figure::color::BLACK);
		board[7][2]->isFree = false;
		board[7][3]->isFree = false;
	}
}
void Board::SwitchPieces(int start_row, int start_col, int finish_row, int finish_col, Figure* figure)
{
	if (figure->FigureType == Figure::type::KING && board[finish_row][finish_col]->figure->FigureType != Figure::type::ROCK)
	{
		King* kingFigure = dynamic_cast<King*>(figure);
		kingFigure->CanCastle = false;
		if (board[finish_row][finish_col]->figure->FigureType != Figure::type::NONE)
		{
			board[finish_row][finish_col]->figure = board[start_row][start_col]->figure;
			board[start_row][start_col]->isFree = true;
		}
		Figure* temp = board[finish_row][finish_col]->figure;
		board[finish_row][finish_col]->figure = figure;
		board[finish_row][finish_col]->isFree = false;
		board[start_row][start_col]->isFree = true;
		board[start_row][start_col]->figure = temp;
		figure->x = finish_row;
		figure->y = finish_col;
	}
	else if (figure->FigureType == Figure::type::KING && board[finish_row][finish_col]->figure->FigureType == Figure::type::ROCK)
	{
		King* kingFigure = dynamic_cast<King*>(figure);
		if (kingFigure->CouldCastle(*this,start_row,start_col,finish_row,finish_col))
		{
			std::cout << "Рокирова возможна" << std::endl;
			if (abs(finish_col - start_col) == 3) // короткая рокировка
			{
				ShortCastling(start_row, start_col, finish_row, finish_col);
			}
			else if (abs(finish_col - start_col) == 4) //длинная рокировка
			{
				LongCastling(start_row, start_col, finish_row, finish_col);
			}
		}
	}
	else if (figure->FigureType == Figure::type::ROCK)
	{
		Rock* rockFigure = dynamic_cast<Rock*>(figure);
		rockFigure->canCastle = false;
	}
	else if ((figure->FigureType == Figure::type::PAWN && figure->FigureColor == Figure::color::WHITE && finish_row == 7) || (figure->FigureType == Figure::type::PAWN && figure->FigureColor == Figure::color::BLACK && finish_row == 0))
	{
		Pawn* pawnFigure = dynamic_cast<Pawn*>(figure);
		pawnFigure->PawnTurn = true;
		std::cout << "Выберите фигуру: конь (n),слон(b),лодья (r),ферзь (q)" << std::endl;
		std::string choice;
		std::cin >> choice;
		if (choice == "k")
		{
				if (board[start_row][start_col]->figure->FigureColor == Figure::color::WHITE)
				{
					board[finish_row][finish_col]->figure = new Knight(finish_row, finish_col, Figure::color::WHITE);
					board[finish_row][finish_col]->isFree = false;
				}
				else
				{
					board[finish_row][finish_col]->figure = new Knight(finish_row, finish_col, Figure::color::BLACK);
					board[finish_row][finish_col]->isFree = false;
				}
				board[start_row][start_col]->figure->FigureType = Figure::type::NONE;
				board[start_row][start_col]->isFree = true;
		}
		else if (choice == "b")
		{
			if (board[start_row][start_col]->figure->FigureColor == Figure::color::WHITE)
			{
				board[finish_row][finish_col]->figure = new Bishop(finish_row, finish_col, Figure::color::WHITE);
				board[finish_row][finish_col]->isFree = false;
			}
			else
			{
				board[finish_row][finish_col]->figure = new Bishop(finish_row, finish_col, Figure::color::BLACK);
				board[finish_row][finish_col]->isFree = false;
			}
			board[start_row][start_col]->figure->FigureType = Figure::type::NONE;
			board[start_row][start_col]->isFree = true;
		}
		else if (choice == "л")
		{
			if (board[start_row][start_col]->figure->FigureColor == Figure::color::WHITE)
			{
				board[finish_row][finish_col]->figure = new Rock(finish_row, finish_col, false,Figure::color::WHITE);
				board[finish_row][finish_col]->isFree = false;
			}
			else
			{
				board[finish_row][finish_col]->figure = new Rock(finish_row, finish_col, false,Figure::color::BLACK);
				board[finish_row][finish_col]->isFree = false;
			}
			board[start_row][start_col]->figure->FigureType = Figure::type::NONE;
			board[start_row][start_col]->isFree = true;
		}
		else if (choice == "q")
		{
			if (board[start_row][start_col]->figure->FigureColor == Figure::color::WHITE)
			{
				board[finish_row][finish_col]->figure = new Queen(finish_row, finish_col, Figure::color::WHITE);
				board[finish_row][finish_col]->isFree = false;
			}
			else
			{
				board[finish_row][finish_col]->figure = new Queen(finish_row, finish_col, Figure::color::BLACK);
				board[finish_row][finish_col]->isFree = false;
			}
			board[start_row][start_col]->figure->FigureType = Figure::type::NONE;
			board[start_row][start_col]->isFree = true;
		}
		else
		{
			std::cout << "Неверный выбор!" << std::endl;
		}
	}
	else if (figure->FigureType == Figure::type::PAWN && abs(start_row - finish_row) == 1 && abs(start_col - finish_col) == 1)
	{
		// Проверка условий для взятия на проходе
		Figure* tFigure = board[start_row][finish_col]->figure;
		if (tFigure != nullptr && tFigure->FigureType == Figure::type::PAWN &&
			tFigure->FigureColor != figure->FigureColor &&
			dynamic_cast<Pawn*>(tFigure)->enPassAvailable)
		{
			Figure* temp = board[finish_row][finish_col]->figure;
			board[start_row][finish_col]->figure->FigureType = Figure::type::NONE;
			board[start_row][finish_col]->isFree = true;
			board[finish_row][finish_col]->figure = figure;
			board[finish_row][finish_col]->isFree = false;
			figure->x = finish_row;
			figure->y = finish_col;
			board[start_row][start_col]->figure = temp;
			board[start_row][start_col]->isFree = true;
			board[start_row][start_col]->figure->x = start_row;
			board[start_row][start_col]->figure->y = start_col;
		}
		else
		{
			Figure* temp = board[finish_row][finish_col]->figure;
			board[finish_row][finish_col]->figure = figure;
			board[finish_row][finish_col]->isFree = false;
			board[start_row][start_col]->isFree = true;
			board[start_row][start_col]->figure = temp;
			figure->x = finish_row;
			figure->y = finish_col;
		}
	}
	else
	{
		Figure* temp = board[finish_row][finish_col]->figure;
		board[finish_row][finish_col]->figure = figure;
		board[finish_row][finish_col]->isFree = false;
		board[start_row][start_col]->isFree = true;
		board[start_row][start_col]->figure = temp;
		figure->x = finish_row;
		figure->y = finish_col;
	}
}
bool Board::isCheckMate(Figure::color PlayColor) //Figure::color PlayColor
{
	if (!isCheck(PlayColor))
	{
		return false;
	}
	Figure* king = nullptr;
	int k_row = 0;
	int k_col = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->figure->FigureType == Figure::type::KING && board[i][j]->figure->FigureColor == PlayColor)
			{
				king = board[i][j]->figure;
				k_row = i;
				k_col = j;
				break;
			}
		}
	}
	for (int i = k_row - 1; i <= k_row + 1; i++)
	{
		for (int j = k_col - 1; j <= k_col + 1; j++)
		{
			if (i >= 0 && i < 8 && j >= 0 && j < 8 && (i != king->x || j != king->y))
			{
				if (king->CanMoveFigure(k_row, k_col, i, j, this))
				{
					if (!isCellAttacked(i, j, PlayColor))
					{
						return false;
					}
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->figure->FigureType != Figure::type::NONE && board[i][j]->figure->FigureColor == PlayColor)
			{
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						if (board[i][j]->figure->CanMoveFigure(i, j, k, l, this))
						{
							Figure* original = board[i][j]->figure;
							board[i][j]->figure = board[k][l]->figure;
							board[k][l]->figure = original;
							bool NowKingSafe = !isCellAttacked(k_row, k_col, PlayColor);
							board[k][l]->figure
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->figure->FigureType != Figure::type::NONE && board[i][j]->figure->FigureColor == PlayColor)
			{
				for (int ni = 0; ni < 8; ++ni)
				{
					for (int nj = 0; nj < 8; ++nj)
					{
						if (board[i][j]->figure->CanMoveFigure(i, j, ni, nj, this))
						{
							Figure* temp = board[ni][nj]->figure;
							board[ni][nj]->figure = board[i][j]->figure;
							board[i][j]->figure = temp;

							bool moveKeepKingSafe = !isCellAttacked(king->x, king->y, PlayColor);
							board[i][j]->figure = board[ni][nj]->figure;
							board[ni][nj]->figure = temp;
							if (moveKeepKingSafe)
								return false;
						}
					}
				}
			}
		}
	}
	return true;
}
bool Board::isStelamate(Figure::color PlayColor)
{
	if (isCheck(PlayColor))
	{
		return false;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->figure->FigureType != Figure::type::NONE && board[i][j]->figure->FigureColor == PlayColor)
			{
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						if (board[i][j]->figure->CanMoveFigure(i, j, k, l, this))
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
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
	board[0][0]->figure = new Rock(0, 0,true, Figure::color::WHITE);
	board[0][1]->figure = new Knight(0, 1, Figure::color::WHITE);
	board[0][2]->figure = new Bishop(0, 2, Figure::color::WHITE);
	board[0][3]->figure = new Queen(0, 3, Figure::color::WHITE);
	board[0][4]->figure = new King(0, 4, true, Figure::color::WHITE);
	board[0][5]->figure = new Bishop(0, 5, Figure::color::WHITE);
	board[0][6]->figure = new Knight(0, 6, Figure::color::WHITE);
	board[0][7]->figure = new Rock(0, 7,true, Figure::color::WHITE);
	for (int i = 0; i < 8; i++) {
		board[1][i]->figure = new Pawn(1, i, false, true, false, Figure::color::WHITE);
		board[2][i]->isAttacked = true;
		board[6][i]->figure = new Pawn(1, i, false, true, false, Figure::color::BLACK);
		board[5][i]->isAttacked = true;
	}
	board[7][0]->figure = new Rock(7, 0,true, Figure::color::BLACK);
	board[7][1]->figure = new Knight(7, 1, Figure::color::BLACK);
	board[7][2]->figure = new Bishop(7, 2, Figure::color::BLACK);
	board[7][3]->figure = new Queen(7, 3, Figure::color::BLACK);
	board[7][4]->figure = new King(7, 4, true, Figure::color::BLACK);
	board[7][5]->figure = new Bishop(7, 5, Figure::color::BLACK);
	board[7][6]->figure = new Knight(7, 6, Figure::color::BLACK);
	board[7][7]->figure = new Rock(7, 7,true, Figure::color::BLACK);
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
void Board::MakeMove() {
	std::string fromCoord, toCoord;
	std::cout << "Введите координату фигуры, которой хотите сходить: ";
	std::cin >> fromCoord;
	std::cout << "Введите координату клетки, в которую хотите сходить: ";
	std::cin >> toCoord;
	if (fromCoord.length() != 2 || toCoord.length() != 2)
	{
		std::cout << "Неправильный формат координат" << std::endl;
		return;
	}
	int s_row, s_col, f_row, f_col;
	s_row = fromCoord[1] - '1';
	f_row = toCoord[1] - '1';
	s_col = fromCoord[0] - 'a';
	f_col = toCoord[0] - 'a';
	if (s_row >= 0 && f_row >= 0 && s_col >= 0 && f_col >= 0 && s_row < 8 && f_row < 8 && s_col < 8 && f_row < 8) {
		Cell* fromCell = board[s_row][s_col];
		if (fromCell->isFree) {
			std::cout << "Выбранная клетка пуста!" << std::endl;
			return;
		}
		Figure::color curr = (WhiteTurn == true) ? Figure::color::WHITE : Figure::color::BLACK;
		if (fromCell->figure->FigureColor != curr)
		{
			std::cout << "Не ваш ход!" << std::endl;
			return;
		}
		if (fromCell->figure->CanMoveFigure(s_row, s_col, f_row, f_col, this)) 
		{
			SwitchPieces(s_row, s_col, f_row, f_col, fromCell->figure);
			Figure::color O = (WhiteTurn == true) ? Figure::color::WHITE : Figure::color::BLACK;
			Figure::color V = Figure::color::WHITE;
			Figure::color Z = Figure::color::BLACK;
			bool whiteCheck = isCheck(V);
			bool blackCheck = isCheck(Z);
			if (whiteCheck)
				std::cout << "Белому королю шах!" << std::endl;
			if (blackCheck)
				std::cout << "Черному королю шах!" << std::endl;
		}
		else
		{
			std::cout << "Неверный ход!" << std::endl;
		}
	}
}
void Board::GameStart() {
	Figure::color W = Figure::color::WHITE;
	Figure::color B = Figure::color::BLACK;
	while (!isCheckMate(W) && !isCheckMate(B) && !isStelamate(W) && !isStelamate(B)) { // если убрать Mate и сделать просто !isCheck(B) то фактически работать будет но ты дурак что ли
		if (WhiteTurn) {
			std::cout << "Ход белых" << std::endl;
			MakeMove();
			PrintBoard(board);
		}
		else {
			std::cout << "Ход черных" << std::endl;
			MakeMove();
			PrintBoard(board);
		}
		WhiteTurn = !WhiteTurn;
	}
	if (isCheckMate(W) || isCheckMate(B)) // здесь тоже самое надо разобраться видимо с самой функцией isCheckmate
	{
		if (isCheckMate(W))
		{
			std::cout << "Мат белым!";
		}
		else
			std::cout << "Мат черным!";
	}
	else if (isStelamate(W) || isStelamate(B))
	{
		std::cout << "Пат.";
	}
}
