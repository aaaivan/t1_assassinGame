#include "UserInput.h"
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
//get board size from player
int askBoardSize() {
	std::cout << "Board size: ";
	int input=0;
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore unlimited characters until a \n is removed
	return input;
}

//get number of assassins from player
int askNumOfAssassins() {
	std::cout << "How many assassins (max 10)? ";
	int input = 0;
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore unlimited characters until a \n is removed
	return input;
}

//get movement pattern
std::pair<int, int> askMovementPattern() {
	std::cout << "How many escaping moves? ";
	int input1 = 0;
	std::cin >> input1;
	std::cout << "How many chasing moves? ";
	int input2 = 0;
	std::cin >> input2;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore unlimited characters until a \n is removed
	return std::make_pair(input1, input2);
}

//get initial coordinates of the assassins
std::vector<std::pair<int, int>> askInitialPositions(int numOfAssassins) {
	std::cout << "Enter " << numOfAssassins << " distinct and valid pairs of space-separated numbers" <<
		" representing the position of each assassin on the board.\nOne pair per line." << std::endl;
	std::vector<std::pair<int, int>> v;
	for (int i = 0; i < numOfAssassins; i++) {
		std::string input;
		std::getline(std::cin, input);
		std::stringstream ss(input);
		std::string s1;
		std::string s2;
		ss >> s1;
		ss >> s2;
		v.push_back(std::make_pair(std::stoi(s1), std::stoi(s2)));
	}
	std::cout << std::endl;
	return v;
}
