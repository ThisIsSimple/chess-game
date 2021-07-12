#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Game.h"

namespace chess
{
	namespace answer
	{
		constexpr size_t WHITE = 0;
		constexpr size_t BLACK = 1;
		constexpr size_t COLOR_EMPTY = 2;

		constexpr size_t KING = 0;
		constexpr size_t QUEEN = 1;
		constexpr size_t ROOK = 2;
		constexpr size_t BISHOP = 3;
		constexpr size_t KNIGHT = 4;
		constexpr size_t PAWN = 5;
		constexpr size_t PIECE_EMPTY = 6;

		constexpr size_t MAX_PIECE_COUNT[6] = {
			1, 1, 2, 2, 2, 8
		};

		void PrintMenu(std::ostream& os, bool bIsFirstTime);
		void PrintError(std::ostream& os);
		void PrintEnd(std::ostream& os);
		constexpr bool IsValidInput(int input);
		constexpr bool IsValidPiece(char piece);
		constexpr bool IsValidCoordinateXY(int x, int y);
		constexpr bool IsValidCoordinate(char x, int y);
		constexpr size_t GetCoordinateFromChar(char ch);
		constexpr size_t GetPieceFromChar(char ch);
		constexpr size_t GetColorFromChar(char ch);

		std::vector<std::vector<char>> chessVector(8, std::vector<char>(8, ' '));

		void PrintInitialBoard(std::ostream& os) {
			os << "*-------------------------*\n";
			os << "*   abcdefgh              *\n";
			os << "*  +--------+             *\n";
			os << "* 0|RNBKQBNR|             *\n";
			os << "* 1|PPPPPPPP|             *\n";
			os << "* 2|        |             *\n";
			os << "* 3|        |             *\n";
			os << "* 4|        |             *\n";
			os << "* 5|        |             *\n";
			os << "* 6|pppppppp|             *\n";
			os << "* 7|rnbkqbnr|             *\n";
			os << "*  +--------+             *\n";
		}

		void LoadBoard(std::istream& is, std::ostream& os) {
			char board[8][8];
			for (int y = 0; y < 8; ++y)
			{
				for (int x = 0; x < 8; ++x)
				{
					board[y][x] = ' ';
				}
			}
			int pieceCounter[2][6] = {{0, }, {0, }};

			char chessPiece;
			char xCh;
			int y;
			while (!is.eof()) {
				is >> chessPiece >> xCh >> y;

				if (is.fail())
				{
					if (is.eof())
					{
						break;
					}
					is.clear();
					std::string trash;
					is >> trash;
					continue;
				}
				else
				{
					if (IsValidPiece(chessPiece) && IsValidCoordinate(xCh, y))
					{
						size_t x = GetCoordinateFromChar(xCh);

						size_t color = GetColorFromChar(board[y][x]);
						size_t piece = GetPieceFromChar(board[y][x]);
						
						if (color == COLOR_EMPTY && piece == PIECE_EMPTY)
						{
							size_t inputColor = GetColorFromChar(chessPiece);
							size_t inputPiece = GetPieceFromChar(chessPiece);
							if (pieceCounter[inputColor][inputPiece] >= MAX_PIECE_COUNT[inputPiece])
							{
								continue;
							}

							++pieceCounter[inputColor][inputPiece];
							board[y][x] = chessPiece;
						}
					}
				}
			}

			os << "*-------------------------*\n";
			os << "*   abcdefgh              *\n";
			os << "*  +--------+             *\n";
			for (int i = 0; i < 8; i++) {
				os << "* " << i << "|";
				for (int j = 0; j < 8; j++) {
					os << board[i][j];
				}
				os << "|             *\n";
			}
			os << "*  +--------+             *\n";
		}

		void PrintGameInformation(std::istream& is, std::ostream& os) {
			char board[8][8];
			for (int y = 0; y < 8; ++y)
			{
				for (int x = 0; x < 8; ++x)
				{
					board[y][x] = ' ';
				}
			}
			int pieceCounter[2][6] = {{0, }, {0, }};

			char chessPiece;
			char xCh;
			int y;
			while (!is.eof()) {
				is >> chessPiece >> xCh >> y;

				if (is.fail())
				{
					if (is.eof())
					{
						break;
					}
					is.clear();
					std::string trash;
					is >> trash;
					continue;
				}
				else
				{
					if (IsValidPiece(chessPiece) && IsValidCoordinate(xCh, y))
					{
						size_t x = GetCoordinateFromChar(xCh);

						size_t color = GetColorFromChar(board[y][x]);
						size_t piece = GetPieceFromChar(board[y][x]);
						
						if (color == COLOR_EMPTY && piece == PIECE_EMPTY)
						{
							size_t inputColor = GetColorFromChar(chessPiece);
							size_t inputPiece = GetPieceFromChar(chessPiece);
							if (pieceCounter[inputColor][inputPiece] >= MAX_PIECE_COUNT[inputPiece])
							{
								continue;
							}

							++pieceCounter[inputColor][inputPiece];
							board[y][x] = chessPiece;
						}
					}
				}
			}

			int blackScore = 100 * pieceCounter[BLACK][PAWN] 
						+ 320 * pieceCounter[BLACK][KNIGHT] 
						+ 330 * pieceCounter[BLACK][BISHOP] 
						+ 500 * pieceCounter[BLACK][ROOK] 
						+ 900 * pieceCounter[BLACK][QUEEN] 
						+ 20000 * pieceCounter[BLACK][KING];
			int whiteScore = 100 * pieceCounter[WHITE][PAWN] 
						+ 320 * pieceCounter[WHITE][KNIGHT] 
						+ 330 * pieceCounter[WHITE][BISHOP] 
						+ 500 * pieceCounter[WHITE][ROOK] 
						+ 900 * pieceCounter[WHITE][QUEEN] 
						+ 20000 * pieceCounter[WHITE][KING];

			os << "*-------------------------*\n";
			os << "* Black pawns:   " << pieceCounter[BLACK][PAWN]		<< "        *\n";
			os << "* Black rooks:   " << pieceCounter[BLACK][ROOK]		<< "        *\n";
			os << "* Black knights: " << pieceCounter[BLACK][KNIGHT]	<< "        *\n";
			os << "* Black bishops: " << pieceCounter[BLACK][BISHOP]	<< "        *\n";
			os << "* Black queen:   " << pieceCounter[BLACK][QUEEN]		<< "        *\n";
			os << "* Black king:    " << pieceCounter[BLACK][KING]		<< "        *\n";
			os << "* White pawns:   " << pieceCounter[WHITE][PAWN]		<< "        *\n";
			os << "* White rooks:   " << pieceCounter[WHITE][ROOK]		<< "        *\n";
			os << "* White knights: " << pieceCounter[WHITE][KNIGHT]	<< "        *\n";
			os << "* White bishops: " << pieceCounter[WHITE][BISHOP]	<< "        *\n";
			os << "* White queen:   " << pieceCounter[WHITE][QUEEN]		<< "        *\n";
			os << "* White king:    " << pieceCounter[WHITE][KING]		<< "        *\n";

			if (pieceCounter[WHITE][KING] == 1 && pieceCounter[BLACK][KING] == 1)
			{
				os << "* Result: ON GOING GAME   *\n";
			}
			else if (pieceCounter[WHITE][KING] == 0 && pieceCounter[BLACK][KING] == 1)
			{
				os << "* Result: BLACK WIN       *\n";
			}
			else if (pieceCounter[WHITE][KING] == 1 && pieceCounter[BLACK][KING] == 0)
			{
				os << "* Result: WHITE WIN       *\n";
			}
			
			if (blackScore == whiteScore) {
				os << "* Who is winning?: NONE   *\n";
			}
			else if (blackScore > whiteScore) {
				os << "* Who is winning?: BLACK  *\n";
			}
			else if (blackScore < whiteScore) {
				os << "* Who is winning?: WHITE  *\n";
			}
		}

		void MainMenu(std::istream& is, std::ostream& os) {
			os << "***************************\n";
			os << "* *************************\n";
			os << "*   ***********************\n";
			os << "*     *********************\n";
			os << "*       *******************\n";
			os << "*         *****************\n";
			os << "*           ***************\n";
			os << "*             *************\n";
			os << "*               ***********\n";
			os << "*                 *********\n";
			os << "*                   *******\n";
			os << "*                     *****\n";
			os << "*                       ***\n";
			os << "*                         *\n";
			os << "***************************\n";
			os << "* SWTube CHESS ENGINE     *\n";
			os << "* Minha Ju                *\n";
			os << "* 2021 / 07 / 05          *\n";
			os << "***************************\n\n";

			bool bIsFirstView = true;
			int input = 0;
			while (input != 4) {
				bool errorFlag = false;

				std::string fileName;
				std::ifstream inputFile;
				while (!is.eof())
				{
					PrintMenu(os, bIsFirstView);

					if (bIsFirstView)
					{
						bIsFirstView = false;
					}

					is >> input;

					if (is.fail() || !IsValidInput(input))
					{
						if (is.eof())
						{
							std::string trash;
							is >> trash;
							input = 4;
							break;
						}
						is.clear();
						std::string trash;
						is >> trash;
					}
					else
					{
						if (input == 2 || input == 3)
						{
							is >> fileName;
							inputFile.open(fileName);

							if (inputFile.is_open())
							{
								break;
							}
						}
						else 
						{
							break;
						}
					}
					os << std::endl;
					PrintError(os);
				}

				os << std::endl;
				
				switch (input)
				{
					case 1:
						PrintInitialBoard(os);
						break;
					case 2:
						LoadBoard(inputFile, os);
						break;
					case 3:
						PrintGameInformation(inputFile, os);
						break;
					case 4:
						PrintEnd(os);
						break;
					default:
						assert(false);
						break;
				}

				inputFile.close();
			}
		}

		void PrintMenu(std::ostream& os, bool bIsFirstTime)
		{
			if (bIsFirstTime)
			{
				os << "***************************\n";
			}
			else
			{
				os << "*-------------------------*\n";
			}
			os << "* 1. PrintBoard           *\n";
			os << "* 2. LoadBoard            *\n";
			os << "* 3. PrintGameInformation *\n";
			os << "* 4. Exit                 *\n";
			os << "*-------------------------*\n";
			os << "  Command: ";
		}

		void PrintError(std::ostream& os)
		{
			os << "*-------------------------*\n";
			os << "* INVALID INPUT!          *\n";
			os << "* PLEASE TRY AGAIN!       *\n";
		}

		void PrintEnd(std::ostream& os)
		{
			os << "*-------------------------*\n";
			os << "* THANK YOU FOR PLAYING!  *\n";
			os << "***************************\n";
		}

		constexpr bool IsValidInput(int input)
		{
			return 1 <= input && input <= 4;
		}

		constexpr bool IsValidPiece(char piece)
		{
			return (piece == 'p' || piece == 'P'
				|| piece == 'n' || piece == 'N'
				|| piece == 'b' || piece == 'B'
				|| piece == 'r' || piece == 'R'
				|| piece == 'q' || piece == 'Q'
				|| piece == 'k' || piece == 'K');
		}

		constexpr size_t GetCoordinateFromChar(char ch)
		{
			assert (('a' <= ch && ch <= 'h') || ('A' <= ch && ch <= 'H'));

			if ('a' <= ch && ch <= 'h')
			{
				return ch - 'a';
			}
			else
			{
				return ch - 'A';
			}
		}

		constexpr bool IsValidCoordinateXY(int x, int y)
		{
			return 0 <= x && x < 7 && 0 <= y && y < 7;
		}

		constexpr bool IsValidCoordinate(char x, int y)
		{
			return (('a' <= x && x <= 'h') || ('A' <= x && x <= 'H')) && 0 <= y && y < 7;
		}

		constexpr size_t GetPieceFromChar(char ch)
		{
			switch(ch)
			{
				case 'k':
					[[fallthrough]];
				case 'K':
					return KING;
				case 'q':
					[[fallthrough]];
				case 'Q':
					return QUEEN;
				case 'r':
					[[fallthrough]];
				case 'R':
					return ROOK;
				case 'b':
					[[fallthrough]];
				case 'B':
					return BISHOP;
				case 'n':
					[[fallthrough]];
				case 'N':
					return KNIGHT;
				case 'p':
					[[fallthrough]];
				case 'P':
					return PAWN;
				default:
					return PIECE_EMPTY;
			}
		}

		constexpr size_t GetColorFromChar(char ch)
		{
			switch(ch)
			{
				case 'k':
					[[fallthrough]];
				case 'q':
					[[fallthrough]];
				case 'r':
					[[fallthrough]];
				case 'b':
					[[fallthrough]];
				case 'n':
					[[fallthrough]];
				case 'p':
					return WHITE;
				case 'K':
					[[fallthrough]];
				case 'Q':
					[[fallthrough]];
				case 'R':
					[[fallthrough]];
				case 'B':
					[[fallthrough]];
				case 'N':
					[[fallthrough]];
				case 'P':
					return BLACK;
				default:
					return COLOR_EMPTY;
			}
		}
	}
}