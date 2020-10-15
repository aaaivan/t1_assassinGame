#ifndef ASSASSIN_H
#define ASSASSIN_H
#include <utility>

class Assassin
{
public:
	const int id;
private:
	std::pair<int, int> coordinates;
	Assassin* target;
	Assassin* chaser;
public:
	Assassin(int _id, std::pair<int, int> _coordinates, Assassin* _target, Assassin* _chaser);
	void setTarget(Assassin* assassin);
	Assassin* getTarget();
	void setChaser(Assassin* assassin);
	Assassin* getChaser();
	std::pair<int, int> getCoordinates();
	std::pair<int, int> escapeChaser();
	std::pair<int, int> chaseTarget();
	void killTarget();//delete target and fix dengling target/chaser relations
};

#endif // !ASSASSIN_H
