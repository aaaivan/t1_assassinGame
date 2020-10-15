#ifndef BOARD_H
#define BOARD_H
#include "Assassin.h"
#include <utility>
#include <vector>

class Board
{
private:
	static int height;
	static int width;
	static Assassin* movingAssassin;
	static std::vector<bool> movementPattern; //moves that make up a turn (true=escape false=chase) 
											  //e.g. {true, false, false} -> escape once, chase twice
	static unsigned int movementPatternCurrentIndex;
	static Assassin*** board; //2d array of pointers to Assassin
public:
	Board(int _height, int _width, int _numOfAssassins,
		std::vector<std::pair<int, int>> _coordinates,
		int _escapeSteps, int _chaseSteps);
	~Board();
	static void printBoard();
	static void updateBoard(); //perform next move
	static bool isGameEnded(); //check if only one assassin is left
	static Assassin* getAssassinAtCell(int x1, int x2);
	static int getHeight();
	static int getWidth();
};
#endif // !BOARD_H
