#include"Astar.h"



#include"..\appData\overloadingAllocations_cpp.h"
	Astar::Astar(heuristic< mazeState>* h) : commonSearcher<mazeState>(), _h(h) {};
	Astar::~Astar()
	{
		delete _h;
	}

	void Astar::setHuristic(heuristic<mazeState>* h)
	{
		delete _h;
		_h = h;
	}

	Solution<mazeState> Astar::search(searchable<mazeState>* s)
	{
		while (!_openList.empty())
			_openList.pop();

		_openSeen.clear();
		_closedSeen.clear();

		_evaluatedNodes = 0;

		mazeSearchable* ms = dynamic_cast<mazeSearchable*>(s);
		mazeState end = ms->getGoalState();
		Position endPos = end.getState()->getPos();
		Solution<mazeState> ans;

		mazeState* start = new mazeState(ms->getStartState());

		double stepCost = ms->getStepCost();
		double h_cost = _h->calculate(start, &end, stepCost);										// calculate huristic cost
		start->calculateCost(stepCost, start, h_cost);									// calculate cost

		this->_openList.push(start);													// start in open liset
		resetEnodes();

		while (!this->_openList.empty())												// while open not empty
		{
			mazeState* curr = this->_openList.top();									// get best node
			_openList.pop();
			_evaluatedNodes++;

			Position p = curr->getState()->getPos();


			if (p == endPos)
			{
				while (curr != nullptr)
				{
					ans.pushState(*curr);
					State<cell>* tmp = curr->getPrev();
					curr = dynamic_cast<mazeState*>(tmp);
				}
				return ans;
			}

			vector<mazeState*> tmp = ms->getAllPossibleStates(curr);		// get next possible states


			for (int i = 0; i < (signed)tmp.size(); i++)
			{
				h_cost = _h->calculate(tmp[i], &end, stepCost);
				tmp[i]->calculateCost(stepCost, curr, h_cost);

				p = tmp[i]->getState()->getPos();
				auto it = _openSeen.find(p);
				if (it != _openSeen.end())
				{
					if (_openSeen[p] < tmp[i]->getStateCost())
					{
						delete tmp[i];
						continue;
					}
				}

				it = _closedSeen.find(p);
				if (it != _closedSeen.end())
				{
					if (_closedSeen[p] < tmp[i]->getStateCost())
					{
						delete tmp[i];
						continue;
					}
				}

				tmp[i]->setPrev(curr);
				this->_openList.push(tmp[i]);
				_openSeen[p] = tmp[i]->getStateCost();
			}

			_closedSeen[curr->getState()->getPos()] = curr->getStateCost();				// remember pos and cost in closed
			_openSeen.erase(curr->getState()->getPos());
		}

		ans.notGood();
		return ans;
	}



