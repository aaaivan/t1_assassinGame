#include "Assassin.h"
#include "Board.h"
#include "UserInput.h"
#include <vector>
#include <utility>
#include <iostream>

int main() {
	int height = askBoardSize("height");
	int width = askBoardSize("width");
	int numOfAssassins = askNumOfAssassins();
	std::pair<int, int> movementPattern = askMovementPattern();
	std::vector<std::pair<int, int>> coordinates = askInitialPositions(numOfAssassins);

	Board* b = new Board(height, width, numOfAssassins, coordinates, movementPattern.first, movementPattern.second);
	b->printBoard();
	while (!b->isGameEnded()) {
		b->updateBoard();
	}
	delete b;

	return 0;
}