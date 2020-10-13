#include "Assassin.h"
#include "Board.h"

//constructor
Assassin::Assassin(int _id, std::pair<int, int> _coordinates, Assassin* _target, Assassin* _chaser):
	id(_id), coordinates(_coordinates), target(_target), chaser(_chaser) { }

//set target assassin
void Assassin::setTarget(Assassin* assassin) {
	target = assassin;
}

//get target assassin
Assassin* Assassin::getTarget() {
	return target;
}

//set chaser assassin
void Assassin::setChaser(Assassin* assassin) {
	chaser = assassin;
}

//get chaser assassin
Assassin* Assassin::getChaser() {
	return chaser;
}

//get the current position of the assassin
std::pair<int, int> Assassin::getCoordinates() {
	return coordinates;
}

//return position of the assassin before the move happens
std::pair<int, int> Assassin::escapeChaser(){
	int xMove;
	int yMove;

	//calculate the direction in which the assassin wants to move
	if (chaser->coordinates.first > coordinates.first) {
		xMove = -1;}
	else if (chaser->coordinates.first < coordinates.first) {
		xMove = 1;}
	else
		xMove = 0;
	if (chaser->coordinates.second > coordinates.second) {
		yMove = -1;}
	else if (chaser->coordinates.second < coordinates.second) {
		yMove = 1;}
	else
		yMove = 0;

	std::pair<int, int> newCoord = std::make_pair(xMove + coordinates.first, yMove + coordinates.second);//coordinates after the move
	
	//check new position is within the board bounds
	if (newCoord.first >= Board::getSize() || newCoord.first < 0)
		return coordinates;
	if (newCoord.second >= Board::getSize() || newCoord.second < 0)
		return coordinates;

	//check whether the target is in the new coordinates
	//if so kill it and move
	if (newCoord == target->coordinates) {
		std::pair<int, int> tempC = coordinates;
		coordinates = newCoord;
		killTarget();
		return tempC;
	}
	//check whether another assassin (not target) is in the new coordinates
	//if so do not move
	else if (Board::getAssassinAtCell(newCoord.first, newCoord.second)!=nullptr)
		return coordinates;

	//move to new coordinates
	std::pair<int, int> tempC = coordinates;
	coordinates = newCoord;
	return tempC;
}

//return position of the assassin before the move happens
std::pair<int, int> Assassin::chaseTarget() {
	int xMove;
	int yMove;

	//calculate the direction in which the assassin wants to move
	if (target->coordinates.first > coordinates.first) {
		xMove = 1;}
	else if (target->coordinates.first < coordinates.first) {
		xMove = -1;}
	else
		xMove = 0;
	if (target->coordinates.second > coordinates.second) {
		yMove = 1;}
	else if (target->coordinates.second < coordinates.second) {
		yMove = -1;}
	else
		yMove = 0;

	std::pair<int, int> newCoord = std::make_pair(xMove + coordinates.first, yMove + coordinates.second);

	//check whether the target is in the new coordinates
	//if so kill it and move
	if (newCoord == target->coordinates) {
		std::pair<int, int> tempC = coordinates;
		coordinates = newCoord;
		killTarget();
		return tempC;
	}
	//check whether another assassin (not target) is in the new coordinates
	//if so do not move
	else if (Board::getAssassinAtCell(newCoord.first, newCoord.second) != nullptr)
		return coordinates;

	//move to new coordinates
	std::pair<int, int> tempC = coordinates;
	coordinates = newCoord;
	return tempC;
}

//Kill the target Assassin
void Assassin::killTarget() {
	if (target == this)
		return;
	else {
		target = target->target;
		delete target->chaser;
		target->chaser = this;
	}
}