#pragma once
#include"heuristic.h"



class Astar : public commonSearcher<mazeState>
{
public:
	Astar(heuristic< mazeState>* h = nullptr);
	~Astar();

	void setHuristic(heuristic<mazeState>* h);

	virtual Solution<mazeState> search(searchable<mazeState>* s);

private:
	heuristic<mazeState>* _h;
	map<Position, double> _openSeen;
	map<Position, double> _closedSeen;

};

