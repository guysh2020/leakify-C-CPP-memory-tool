#include"generator.h"

//     maze2d generator

int Maze2dGenerator::getRandomNumber()
{
	std::random_device rd1;
	std::uniform_int_distribution<int> distribution(0, 8191);
	int tmp = distribution(rd1);
	return tmp;
}

void Maze2dGenerator::removeWalls(cell* one, cell* two)
{
	string one_wall;
	string two_wall;

	Position one_pos = one->getPos();
	Position two_pos = two->getPos();

	if (one_pos.getPos_x() == two_pos.getPos_x())
	{
		if (one_pos.getPos_y() < two_pos.getPos_y())
		{
			one_wall = "bottom";
			two_wall = "top";
		}
		else
		{
			one_wall = "top";
			two_wall = "bottom";
		}
	}
	else
	{
		if (one_pos.getPos_x() > two_pos.getPos_x())
		{
			one_wall = "left";
			two_wall = "right";
		}
		else
		{
			one_wall = "right";
			two_wall = "left";
		}
	}

	one->removeWall(one_wall);
	two->removeWall(two_wall);
}

string Maze2dGenerator::measureAlgorithmTime(int size, string name)
{
	auto start = chrono::high_resolution_clock::now();
	Maze2d maze = generate(size, name);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

	string tmp = "time taken in seconds:";

	return to_string(duration.count());
}

cell* Maze2dGenerator::getRandomadjacent(cell* ptr)
{
	vector <pair<int, int>> ans;
	vector <pair<int, int>> tmp = ptr->getAdjacents();
	int size = _maze.size();
	int num = 4;

	for (int i = 3; i >= 0; i--)
	{
		if (tmp[i].first == -1 || tmp[i].first >= size || tmp[i].second == -1 || tmp[i].second >= size || _maze[tmp[i].first][tmp[i].second].isVisited())
			num--;
		else
			ans.push_back(tmp[i]);
	}

	if (num == 0)
		return nullptr;



	int index = rand();
	index %= num;

	return &_maze[ans[index].first][ans[index].second];
};


//     mymaze2d generator


Maze2d myMaze2dGenerator::generate(int size, string name)
{
	_maze.resize(size);
	for (int i = 0; i < size; i++)
	{
		_maze[i] = vector<cell>(size);
		for (int j = 0; j < size; j++)
		{
			_maze[i][j].setPos(i, j);
			_maze[i][j].setAdjencts();
			_list.push(&_maze[i][j]);
		}
	}

	
	_end = &_maze[size - 1][size - 1];
	_start = &_maze[0][0];

	cell* curr = &_maze[0][0];
	cell* next = nullptr;

	pair<int, int> position;
	curr->setVisited(true);

	while (!_list.empty())						// while stack not empty
	{
		next = getRandomadjacent(curr);			// if any neigbhors
		if (next != nullptr)
		{
			removeWalls(curr, next);							// remove walls
			_list.push(curr);
			curr = next;
			curr->setVisited(true);
		}
		else
		{
			curr = _list.top();
			_list.pop();
		}
	}

	for (int i = 0; i < size ;i++)
	{
		for (int j = 0; j < size; j++)
		{
			_maze[i][j].setVisited(false);
		}
	}

	Maze2d ans(_maze, name, _start, _end);
	return  ans;
};


	//     simpleMaze2d generator

void simpleMaze2dGenerator::setRandomStartEnd()
{


	pair<int, int> pos;
	pair<int, int> pos2;
	int size = _maze.size();
	int num = getRandomNumber();
	num %= 4;

	switch (num)
	{
	case 0:			// top
		pos.first = 0;
		pos.second = getRandomNumber() % size;

		pos2.first = size - 1;
		pos2.second = getRandomNumber() % size;
		break;

	case 1:				// right
		pos.first = getRandomNumber() % size;;
		pos.second = size - 1;

		pos2.first = getRandomNumber() % size;;
		pos2.second = 0;
		break;

	case 2:				// bottom
		pos.first = size - 1;
		pos.second = getRandomNumber() % size;

		pos2.first = 0;
		pos2.second = getRandomNumber() % size;
		break;

	case 3:				// left
		pos.first = getRandomNumber() % size;;
		pos.second = 0;

		pos2.first = getRandomNumber() % size;;
		pos2.second = size - 1;
		break;
	}

	_start = &_maze[pos.first][pos.second];
	_end = &_maze[pos2.first][pos2.second];

}

Maze2d simpleMaze2dGenerator::generate(int size, string name) { _maze.resize(size);
	
	for (int i = 0; i < size; i++)
	{
		_maze[i] = vector<cell>(size);
		for (int j = 0; j < size; j++)
		{
			_maze[i][j].setPos(i, j);
			_maze[i][j].setAdjencts();
			_list.push(&_maze[i][j]);
		}
	}

	setRandomStartEnd();
	pair<int, int>pos1 = _start->getPos().getPosition();
	pair<int, int> pos2;
	pair<int, int>end = _end->getPos().getPosition();

	cell* curr = _start;
	cell* next;

	bool done = false;


	while (pos1 != end)								     	// go to end
	{
		pos2 = pos1;
		if (pos2.first > end.first)
			pos2.first--;
		else if (pos2.first < end.first)
			pos2.first++;

		if (pos2 == pos1)
		{
			if (pos2.second > end.second)
				pos2.second--;
			else if (pos2.second < end.second)
				pos2.second++;
		}

		removeWalls(&_maze[pos1.first][pos1.second], &_maze[pos2.first][pos2.second]);
		pos1 = pos2;
	}

	int y, x;
	int iterations = size * size;
	for (int i = 0; i < iterations; i++)
	{
		y = getRandomNumber() % size;
		x = getRandomNumber() % size;
		curr = &_maze[y][x];
		next = getRandomadjacent(curr);
		if (next == nullptr)
			continue;
		removeWalls(curr, next);
	}



	return Maze2d(_maze, name, _start,_end);
};