#pragma once
#include"searcher.h"
#include <cmath>
#include <map>

template<class type>
class heuristic
{
public:
	heuristic() = default;
	~heuristic() = default;
	virtual double calculate(type* curr, type* goal, double step_cost) = 0;
};



class MazeAirDistance : public heuristic<mazeState>
{
public:
	MazeAirDistance() = default;
	~MazeAirDistance() = default;
	virtual double calculate(mazeState* curr, mazeState* goal, double step_cost);

};


class MazeManheten : public heuristic<mazeState>
{
public:
	MazeManheten() = default;
	~MazeManheten() = default;
	virtual double calculate(mazeState* curr, mazeState* goal, double step_cost);

};
