#include"command.h"
#include"controler.h"

void exitCommand::execute(vector<string>vec, controler* con)
{
	return;
}



void mazeSizeCommand::execute(vector<string>vec, controler* con)
{
	if (vec.size() < 3)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}

	int ans = con->getModel()->getMazeSize(vec[2]);
	string tmp = "the size of the maze in memory is: " + to_string(ans) + " bytes.";
	con->getView()->print(tmp);
}



void displaySolutionCommand::execute(vector<string> vec, controler* con)
{
	if (vec.size() < 3)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}
	view* v = con->getView();
	model* m = con->getModel();
	vector<mazeState> sol = m->getSolution(vec[2]);
	v->printSolution(sol);

}



void solveCommand::execute(vector<string> vec, controler* con)
{
	if (vec[2] != "BFS" && vec[2] != "Astar")
	{
		con->getView()->print("invalid input, please try again.");
		return;
	}
	if (vec[2] == "Astar" && vec[3] != "manheten" && vec[3] != "airdist")
	{
		con->getView()->print("invalid input, please try again.");
		return;
	}
	else if( vec[2] == "Astar")
		con->getModel()->solve(vec[1], vec[2], vec[3]);
	else
		con->getModel()->solve(vec[1], vec[2], "");
	con->getView()->print("solution for " + vec[1] + " is ready");
}


void fileSizeCommand::execute(vector<string> vec, controler* con)
{
	if (vec.size() < 3)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}

	string filename = vec[2];
	struct stat stat_buf;
	int rc = stat(filename.c_str(), &stat_buf);
	if (rc != 0)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}
	else
	{
		string ans = to_string(stat_buf.st_size) + " bytes";
		con->getView()->print(ans);
	}
}


void generateMazeCommand::execute(vector<string> vec, controler* con)		
{
	if (vec.size() < 5)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}
	int size = stoi(vec[2]);
	if (con->getModel()->generteMaze(size, vec[3], vec[4]))
		return;
	else
	{
		con->getView()->print("invalid input - a maze with this name already exist.");
	}
}


void dirCommand::execute(vector<string> vec, controler* con)
{
	if (vec.size() < 2)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}
	string _dirName = vec[1];

	DIR* _dir;
	struct dirent* dire;
	struct stat sta;
	_dir = opendir(_dirName.c_str());
	if (!_dir) {
		con->getView()->print("invalid path, try again.");
		return;
	}
	while ((dire = readdir(_dir)) != NULL)
	{
		if (dire->d_name[0] != '.') {
			string path = string(_dirName) + "/" + string(dire->d_name);
			con->getView()->print(path);
		}
	}
	closedir(_dir);
}



void displayCommand::execute(vector<string> vec, controler* con)
{
	if (vec.size() < 2)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}
	Maze2d* tmp = con->getModel()->getMaze(vec[1]);
	con->getView()->printMaze(tmp->getBoard(), tmp->getStartPosition(), tmp->getGoalPosition());
}


void saveMazeCommand::execute(vector<string> vec, controler* con)
{
	if (vec.size() < 4)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}

	string filename = vec[3];
	string name = vec[2];
	ofstream out_file;

	Maze2d* tmp = con->getModel()->getMaze(name);
	if (tmp == nullptr)
	{
		con->getView()->print("invalid input, no such maze.");
		return;
	}

	vector<int> saveme = tmp->getData();

	saveme = con->getModel()->compress(saveme);

	out_file.open(filename, ios::out | ios::binary);
	for (int i = 0; i < (signed)saveme.size(); i++)
		out_file.write((char*)&saveme[i], sizeof(int));

	out_file.close();

}



void loadMazeCommand::execute(vector<string> vec, controler* con)
{
	if (vec.size() < 4)
	{
		con->getView()->print("invalid input, try again.");
		return;
	}

	string filename = vec[2];
	string maze_name = vec[3];
	ifstream in_file;
	vector<int> ans;
	vector < vector<int>> uncomp;

	in_file.open(filename, ios::in | ios::binary);
	while (!in_file.eof())
	{
		int tmp;

		in_file.read((char*)&tmp, sizeof(int));
		ans.push_back(tmp);

	}
	in_file.close();

	uncomp = con->getModel()->unCompress(ans);

	con->getModel()->loadMaze(uncomp, maze_name);
}
