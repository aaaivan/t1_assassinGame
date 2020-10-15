#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <utility>
#include <vector>
#include <string>

int askBoardSize(std::string s);
int askNumOfAssassins();
std::pair<int, int> askMovementPattern();
std::vector<std::pair<int, int>> askInitialPositions(int numOfAssassins);

#endif // !USER_INPUT_H

