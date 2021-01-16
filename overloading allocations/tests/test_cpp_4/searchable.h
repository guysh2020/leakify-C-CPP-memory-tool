#pragma once

#include"state.h"
#include"maze.h"

template<class type>
class Solution
{
public:
	Solution() = default;
	~Solution() = default;

	void pushState(type a)
	{
		_solution.insert(_solution.begin(), a);
	};

	vector<type> getSolution()const { return _solution; };
	void notGood() { _solution.resize(0); };
private:
	vector<type> _solution;
};


template<class type>
class searchable {
private:
public:
	searchable() = default;
	~searchable() {}
	virtual const type& getStartState() const = 0;
	virtual const type& getGoalState() const = 0;
	virtual vector<type*> getAllPossibleStates(type* curr) = 0;

};


class mazeSearchable : public searchable<mazeState>
{
public:
	mazeSearchable(Maze2d& maze);

	~mazeSearchable();

	virtual const mazeState& getStartState()const;

	virtual const mazeState& getGoalState() const;

	virtual vector<mazeState*> getAllPossibleStates(mazeState* curr);

	double getStepCost()const;

	void print();

private:
	Maze2d _maze;
	double _stepCost;
	mazeState* _start;
	mazeState* _end;
};