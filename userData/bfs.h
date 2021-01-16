#pragma once
#include"searcher.h"

class BFS : public commonSearcher<mazeState>
{
public:
	BFS() = default;
	~BFS() = default;
	virtual Solution<mazeState> search(searchable<mazeState>* s);
};