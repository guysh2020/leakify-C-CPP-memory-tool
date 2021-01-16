#include"model.h"



#include"..\appData\overloadingAllocations_cpp.h"
	model::model(controler* cont) :_cont(cont), _myGenerator(nullptr), _simpleGenerator(nullptr), _Astar(nullptr), _BFS(nullptr), _searchable(nullptr)
	{
		_simpleGenerator = new simpleMaze2dGenerator();
		_myGenerator = new myMaze2dGenerator();
		_Astar = new Astar();
		_BFS = new BFS();
		_zip = new zip();
	}

	model::~model()
	{
		delete _simpleGenerator;
		delete _myGenerator;
		delete _Astar;
		delete _BFS;
		delete _searchable;
		delete _zip;
	}

	vector<int> model::compress(vector<int> vec)
	{
		return _zip->compress(vec);
	}

	bool model::generteMaze(int size, string name, string type)
	{
		auto it = _mazes.find(name);
		if (it != _mazes.end())
		{
			return false;
		}

		if (type == "my")
			_mazes[name] = new Maze2d(_myGenerator->generate(size, name));
		else
			_mazes[name] = new Maze2d(_simpleGenerator->generate(size, name));

		return true;
	}

	void model::loadMaze(vector<vector<int>> data, string name)
	{
		_mazes[name] = new Maze2d(data);
		_mazes[name]->setName(name);
	}

	int model::getMazeSize(string name)
	{
		
		int size = 0;
		size += sizeof(bool);
		size += (sizeof(cell*) * 2);
		size += sizeof(name);
		size += sizeof(cell) * _mazes[name]->getBoard().size();
		return size;
	}

	int model::getEvaluatedNodes(string alg)
	{
		if (alg == "BFS")
			return _BFS->getNumberOfEvaluated();
		else if (alg == "Astar")
			return _Astar->getNumberOfEvaluated();

		return 0;
	}

	vector<mazeState> model::getSolution(string name)
	{
		vector<mazeState> vec;
		auto it = _solutions.find(name);
		if (it == _solutions.end())
		{
			vector<mazeState> vec;
			vec.resize(0);
			return vec;
		}

		else
			return _solutions[name].getSolution();
	}

	Maze2d* model::getMaze(string name)
	{
		auto it = _mazes.find(name);
		if (it == _mazes.end())
			return nullptr;
		else
			return _mazes[name];
	}

	vector<vector<int>> model::unCompress(vector<int> vec)
	{
		return _zip->uncompress(vec);
	}

	bool model::solve(string name, string alg, string h , bool check )
	{
		auto it = _mazes.find(name);
		if (it == _mazes.end())
			return false;

		if (check)
		{
			auto it1 = _solutions.find(name);
			if (it1 != _solutions.end())
				return true;
		}

		_searchable = new mazeSearchable(*it->second);

		mazeSearchable* maze = dynamic_cast<mazeSearchable*>(_searchable);
		Solution<mazeState> ans;

		if (alg == "Astar")
		{
			if (h == "manheten")
				_Astar->setHuristic(new MazeManheten());
			else if (h == "air_distance")
				_Astar->setHuristic(new MazeAirDistance());
			else
			{
				delete _searchable;
				_searchable = nullptr;
				return false;
			}
			ans = _Astar->search(maze);
		}
		else if (alg == "BFS")
			ans = _BFS->search(maze);
		else
		{
			delete _searchable;
			_searchable = nullptr;
			return false;
		}



		if (ans.getSolution().size() == 0)
			return false;
		else
		{
			_solutions[name] = ans;
			delete _searchable;
			_searchable = nullptr;
			return true;
		}

		return true;

	}
