#ifndef BOARD_H
#define BOARD_H
#include "Assassin.h"
#include <utility>
#include <vector>

class Board
{
private:
	static int size;
	static Assassin* movingAssassin;
	static std::vector<bool> movementPattern; // true=escape false=chase
	static unsigned int movementPatternCurrentIndex;
	static Assassin*** board;
public:
	Board(int _size, int _numOfAssassins, std::vector<std::pair<int, int>> _coordinates, int _escapeSteps, int _chaseSteps);
	~Board();
	static void printBoard();
	static void updateBoard();
	static bool isGameEnded();
	static Assassin* getAssassinAtCell(int x1, int x2);
	static int getSize();
};
#endif // !BOARD_H
