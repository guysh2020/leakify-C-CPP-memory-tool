#include"maze.h"
#include<map>
#include "overloadingAllocations_cpp.h"

//     maze2d

Maze2d::Maze2d(vector<vector<cell>> maze, string name, cell* start, cell* end) : Maze(start, end,name)
{
	_maze = maze;
	_isSolved = false;
	_start = &_maze[start->getPos().getPos_y()][start->getPos().getPos_x()];
	_end = &_maze[end->getPos().getPos_y()][end->getPos().getPos_x()];
	_mazeName = name;
};

Maze2d::Maze2d(const Maze2d& m) :Maze(), _maze(m._maze)
{
	Position s = m.getStartPosition()->getPos();
	Position e = m.getGoalPosition()->getPos();

	_start = &_maze[s.getPos_y()][s.getPos_x()];
	_end = &_maze[e.getPos_y()][e.getPos_x()];
	_mazeName = m._mazeName;
};

cell* Maze2d::getCell(Position pos)
{
	return &_maze[pos.getPos_y()][pos.getPos_x()];
}

cell* Maze2d::findCell(string str, const cell* curr)
{
	Position tmp = curr->getPos();


	int x = tmp.getPos_x();
	int y = tmp.getPos_y();

	if (str == "UP")
		return &_maze[tmp.getPos_y() - 1][tmp.getPos_x()];

	if (str == "RIGHT")
		return &_maze[tmp.getPos_y()][tmp.getPos_x() + 1];

	if (str == "DOWN")
		return &_maze[tmp.getPos_y() + 1][tmp.getPos_x()];

	if (str == "LEFT")
		return &_maze[tmp.getPos_y()][tmp.getPos_x() - 1];

	return nullptr;
}

vector<string> Maze2d::getPossibleMoves(Position pos)const
{

	const cell* tmp = &_maze[pos.getPos_y()][pos.getPos_x()];
	bool t = tmp->getWall("top");
	bool r = tmp->getWall("right");
	bool b = tmp->getWall("bottom");
	bool l = tmp->getWall("left");

	vector<string> ans;

	if (!t)
		ans.push_back("UP");
	if (!r)
		ans.push_back("RIGHT");
	if (!b)
		ans.push_back("DOWN");
	if (!l)
		ans.push_back("LEFT");


	
	return ans;
}

vector<int> Maze2d::getData()
{
	vector<int> ans;
	string name = _mazeName;
	ans.push_back(name.length());

	for (int i = 0; i < (signed)name.length(); i++)
		ans.push_back(name[i]);

	ans.push_back(_maze.size());
	ans.push_back(_start->getPos().getPos_y());
	ans.push_back(_start->getPos().getPos_x());
	ans.push_back(_end->getPos().getPos_y());
	ans.push_back(_end->getPos().getPos_x());


	for (int i = 0; i < (signed)_maze.size(); i++)
	{
		for (int n = 0; n < (signed)_maze.size(); n++)
		{
			bool t = _maze[i][n].getWall("top");
			bool l = _maze[i][n].getWall("left");
			bool b = _maze[i][n].getWall("bottom");
			bool r = _maze[i][n].getWall("right");
			ans.push_back(t);
			ans.push_back(r);
			ans.push_back(b);
			ans.push_back(l);
		}
	}
	return ans;
}

Maze2d::Maze2d(vector<vector<int>> maze) :Maze()
{

	string name = "";
	for (int i = 0; i < (signed)maze[0].size(); i++)
		name += (char)maze[0][i];

	_mazeName = name;
	pair<int, int> start;
	pair<int, int> end;

	int size = maze[1][0];
	start.first = maze[1][1];
	start.second = maze[1][2];
	end.first = maze[1][3];
	end.second = maze[1][4];

	_maze.resize(size);
	for (int i = 0; i < size; i++)
	{
		_maze[i].resize(size);
		for (int j = 0; j < size; j++)
		{
			_maze[i][j].setPos(i, j);
		}
	}


	_start = &_maze[start.first][start.second];
	_end = &_maze[end.first][end.second];


	int n = 0;
	int row = 0;
	for (int i = 2; i < (signed)maze.size(); i++)
	{
		if (maze[i][0] == 0)
			_maze[row][n].removeWall("top");

		if (maze[i][1] == 0)
			_maze[row][n].removeWall("right");

		if (maze[i][2] == 0)
			_maze[row][n].removeWall("bottom");

		if (maze[i][3] == 0)
			_maze[row][n].removeWall("left");

		n++;
		if (n == size)
			row++;

		n %= size;

	}

}