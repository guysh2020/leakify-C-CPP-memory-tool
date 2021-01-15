#include"controler.h"
#include"view.h"
#include"cli.h"



view::view(controler* cont, CLI* cli) : _cont(cont),_cli(cli) {};
view::~view() {};

void view::printMaze(vector<vector<cell>>& _maze, cell* start, cell* end, vector<mazeState>* s )
{
	vector<Position> tmp;
	Position p;

	if (s)
	{
		for (int i = 0; i < (signed)s->size(); i++)
		{
			p = (*s)[i].getState()->getPos();
			tmp.push_back(p);
		}
	}

	vector<vector<char>> ans;
	int size = _maze.size();

	int size2 = size * 2 + 1;
	ans.resize(size2);


	for (int i = 0; i < size2; i++)
	{
		ans[i].resize(size2);
		fill(ans[i].begin(), ans[i].end(), 1);
	}

	char wall = 0;
	char free = 1;

	vector<Position>::iterator it;

	int a = 1;
	for (int i = 0; i < size; i++)
	{
		int b = 1;
		for (int j = 0; j < size; j++)
		{
			if (_maze[i][j].getWall("top"))
			{
				if (ans[a - 1][b - 1] == free)
					ans[a - 1][b - 1] = wall;

				if (ans[a - 1][b] == free)
					ans[a - 1][b] = wall;

				if (ans[a - 1][b + 1] == free)
					ans[a - 1][b + 1] = wall;
			}

			if (_maze[i][j].getWall("right"))
			{
				if (ans[a - 1][b + 1] == free)
					ans[a - 1][b + 1] = wall;

				if (ans[a][b + 1] == free)
					ans[a][b + 1] = wall;

				if (ans[a + 1][b + 1] == free)
					ans[a + 1][b + 1] = wall;
			}

			if (_maze[i][j].getWall("bottom"))
			{
				if (ans[a + 1][b - 1] == free)
					ans[a + 1][b - 1] = wall;

				if (ans[a + 1][b] == free)
					ans[a + 1][b] = wall;

				if (ans[a + 1][b + 1] == free)
					ans[a + 1][b + 1] = wall;
			}

			if (_maze[i][j].getWall("left"))
			{
				if (ans[a - 1][b - 1] == free)
					ans[a - 1][b - 1] = wall;

				if (ans[a][b - 1] == free)
					ans[a][b - 1] = wall;

				if (ans[a + 1][b - 1] == free)
					ans[a + 1][b - 1] = wall;
			}

			b += 2;
		}

		a += 2;
	}


	if (s)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				Position p1 = _maze[i][j].getPos();
				for(int n = 0 ; n < (signed)tmp.size(); n++)
				{
					if(tmp[n] == p1)
						ans[it->getPos_y() * 2 + 1][it->getPos_x() * 2 + 1] = 3;

					break;
				}
					
			}
		}
	}


	p = start->getPos();
	ans[p.getPos_y() * 2 + 1][p.getPos_x() * 2 + 1] = 4;

	p = end->getPos();
	ans[p.getPos_y() * 2 + 1][p.getPos_x() * 2 + 1] = 5;

	//for (int i = 0; i < size; i++)
	//{
	//	if (i == 0)
	//		cout << "   ";
	//	cout << i << i << "  ";
	//}
	//cout << endl;

	int row = 0;
	for (int i = 0; i < size2; i++)
	{
		//if (i % 2 == 0)
		//	cout << " ";
		//else
		//	cout << row++;

		for (int j = 0; j < size2; j++)
		{
			if (ans[i][j] == 0)
				cout << "||";

			if (ans[i][j] == 1)
				cout << "  ";

			if (ans[i][j] == 3)
				cout << "++";

			if (ans[i][j] == 4)
				cout << "S ";

			if (ans[i][j] == 5)
				cout << "E ";
		}

		cout << endl;
	}
}
void view::printSolution(vector<mazeState>& solution)
{
	int size = solution.size();
	if (size == 0)
	{
		_cli->getOutStream() << "there is no solution available for this maze." << endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		cout << "state " << i << " :" << solution[i].getState()->getPos() << endl;
	}
}

void view::print(string str)
{
	_cli->getOutStream() << str << endl;
}

void view::start(istream& in , ostream& out)
{
	_cli = new CLI(in , out);
	std::cout << _cli << "%%%%%%%%%%%%%%";
	int *x = new int();
	std::cout << "basa";
	std::cout << x;
	std::cout << "ojojoj";
	_cli->start(this);
	//delete x;
}

void view::runCommand(vector<string> s)
{
	_cont->runCommand(s);
}

string view::getInput(string ask)
{
	char tmp[256];
	istream& in = _cli->getInStream();
	ostream& out = _cli->getOutStream();

	out << ask << endl;
	in.getline(tmp, 256, '\n');

	return tmp;
}
controler* view::getControler() { return _cont; };

