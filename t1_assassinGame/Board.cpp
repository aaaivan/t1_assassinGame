#include "Board.h"
#include <iostream>

//initialize static variables
int Board::size = 0;
Assassin* Board::movingAssassin=nullptr;
std::vector<bool> Board::movementPattern={}; // true=escape false=chase
unsigned int Board::movementPatternCurrentIndex=0;
Assassin*** Board::board=nullptr;


//constructor
Board::Board(int _size, int _numOfAssassins, std::vector<std::pair<int,int>> coordinates, int _escapeSteps, int _chaseSteps) {
	size = _size;
	
	//allocate memory for each assassin and define for each its target/chaser
	Assassin* first = new Assassin(0, coordinates[0],nullptr, nullptr);
	Assassin* temp1 = first;
	for (int i = 1; i < _numOfAssassins; i++) {
		Assassin* temp2= new Assassin(i, coordinates[i], nullptr, temp1);
		temp1->setTarget(temp2);
		temp1 = temp2;
	}
	temp1->setTarget(first);
	first->setChaser(temp1);
	movingAssassin = first;

	//fill the movement pattern vector _escapeSteps times true followed by _chaseSteps false
	//true represent an escape move, false a chase move
	movementPatternCurrentIndex = 0;
	for (int i = 0; i < _escapeSteps; i++)
		movementPattern.push_back(true);
	for (int i = 0; i < _chaseSteps; i++)
		movementPattern.push_back(false);

	//create an 2d array of Assassin* representng the layout of the game
	board = new Assassin** [size];
	for (int i = 0; i < size; i++) {
		board[i] = new Assassin*[size];
		for (int j = 0; j < size; j++) {
			board[i][j] = nullptr;
		}
	}
	Assassin* temp = movingAssassin;
	do{
		board[temp->getCoordinates().first][temp->getCoordinates().second] = temp;
		temp = temp->getTarget();
	} while (temp != movingAssassin);
}

//print the board
void Board::printBoard() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == nullptr)
				std::cout << ".";
			else
				std::cout << board[i][j]->id;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::updateBoard() {
	//based on pattern call a move function from assassin
	std::pair<int, int> oldCell;
	if (movementPattern[movementPatternCurrentIndex]){ 
		std::cout << "Assassin " << movingAssassin->id << " moves away from assassin " << movingAssassin->getChaser()->id<<std::endl;
		oldCell = movingAssassin->escapeChaser(); 
	}
	else {
		std::cout << "Assassin " << movingAssassin->id << " chases assassin " << movingAssassin->getTarget()->id << std::endl;
		oldCell = movingAssassin->chaseTarget();
	}

	//update board
	board[oldCell.first][oldCell.second] = nullptr;
	std::pair<int, int> newCell= movingAssassin->getCoordinates();
	board[newCell.first][newCell.second] = movingAssassin;
	
	//print board
	printBoard();

	//increase movementPatternCurrentIndex and move to the next asassin if necessary
	if (movementPatternCurrentIndex == movementPattern.size() - 1) {
		//all the moves for one turn have been completed
		//reset movementPatternCurrentIndex to 0 and go to the next assassin still alive
		movementPatternCurrentIndex = 0;
		movingAssassin = movingAssassin->getTarget();
	}
	else {
		movementPatternCurrentIndex++;
	}
}

//check if only one assassin remains
bool Board::isGameEnded() {
	if (movingAssassin->getTarget() == movingAssassin) {
		std::cout << "Assassin number " << movingAssassin->id << " is the winner!";
		delete movingAssassin; //delete last assassin alive
		return true;
	}
	return false;
}

//destructor
Board::~Board() {
	//delete memory allocated for 2d Assassin* array 'board'
	for (int i = 0; i < size; i++) {
		delete[] board[i];
	}
	delete[] board;
}

//get the assassin at the specified cell. Return nullptr if cell is empty.
Assassin* Board::getAssassinAtCell(int x1, int x2) {
	return board[x1][x2];
}

int Board::getSize() {
	return size;
}
