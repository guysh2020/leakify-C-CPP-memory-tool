#include"searchable.h"
#include<vector>

#include"..\appData\overloadingAllocations_cpp.h"
using namespace std;


	mazeSearchable::mazeSearchable(Maze2d& maze) :searchable(), _maze(maze), _start(nullptr), _end(nullptr)
	{
		_start = new mazeState(_maze.getStartPosition(), nullptr);
		_end = new mazeState(_maze.getGoalPosition(), nullptr);
		_stepCost = 1.5;
	};

	mazeSearchable::~mazeSearchable()
	{
		delete _start;
		delete _end;
	}

	const mazeState& mazeSearchable::getStartState()const
	{
		return *_start;
	}

	const mazeState& mazeSearchable::getGoalState() const
	{
		return *_end;
	}

	vector<mazeState*> mazeSearchable::getAllPossibleStates(mazeState* curr)
	{

		/*validtion*/

		

		/*validtion*/

		Position tmp = curr->getState()->getPos();
		vector<mazeState*> vec;
		vector<string> moves;
		moves = _maze.getPossibleMoves(tmp);

		while (!moves.empty())
		{
			string str = moves.back();
			moves.pop_back();
			cell* pos = _maze.findCell(str, curr->getState());

			vec.push_back(new mazeState(pos, curr));
		}

		return vec;
	}

	double mazeSearchable::getStepCost()const { return _stepCost; };

	void mazeSearchable::print()
	{
		//_maze.print();
	}

