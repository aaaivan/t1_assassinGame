#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <utility>
#include <vector>

int askBoardSize();
int askNumOfAssassins();
std::pair<int, int> askMovementPattern();
std::vector<std::pair<int, int>> askInitialPositions(int numOfAssassins);

#endif // !USER_INPUT_H

