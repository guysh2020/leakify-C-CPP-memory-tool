#include"bfs.h"
#include <math.h>
#include <map>


Solution<mazeState> BFS::search(searchable<mazeState>* s)
{
	while (!_openList.empty())
		_openList.pop();

	mazeSearchable* ms = dynamic_cast<mazeSearchable*>(s);
	mazeState end = ms->getGoalState();
	Position endPos = end.getState()->getPos();
	Solution<mazeState> ans;

	mazeState* start = new mazeState(ms->getStartState());
	double cost = ms->getStepCost();

	start->calculateCost(cost,start);

	this->_openList.push(start);												//push first node

	while (!this->_openList.empty())
	{
		mazeState* curState = this->_openList.top();
		this->_openList.pop();

		curState->getState()->setVisited(true);
		this->_evaluatedNodes++;

		if (curState->getState()->getPos() == endPos)
		{
			
			while (curState != nullptr)
			{
				ans.pushState(*curState);

				State<cell>* tmp = curState->getPrev();

				curState = dynamic_cast<mazeState*>(tmp);
			}
			return ans;
		}

		vector<mazeState*> tmp = ms->getAllPossibleStates(curState);		// get next possible states

		for (int i = 0; i < (signed)tmp.size(); i++)
		{
			if (tmp[i]->getState()->isVisited())
			{
				delete tmp[i];
				continue;
			}
				

			tmp[i]->setPrev(curState);
			tmp[i]->calculateCost(cost,curState);
			this->_openList.push(tmp[i]);
		}
	}

	ans.notGood();
	return ans;
};





