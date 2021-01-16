#pragma once
#include"maze.h"
#include"generator.h"
#include"searchable.h"
#include<unordered_map>
#include"Astar.h"
#include"bfs.h"
#include"zip.h"


class controler;

class model
{
public:
	model(controler* cont);
	~model();
	bool generteMaze(int size, string name, string type);
	void loadMaze(vector<vector<int>> data, string name);
	int getMazeSize(string name);
	int getEvaluatedNodes(string alg);
	vector<mazeState> getSolution(string name);
	Maze2d* getMaze(string name);
	vector<vector<int>> unCompress(vector<int> vec);
	vector<int> compress(vector<int> vec);
	bool solve(string name, string alg, string h, bool check = true);

private:
	unordered_map<string, Maze2d*> _mazes;
	unordered_map<string, Solution<mazeState>> _solutions;
	controler* _cont;
	MazeGeneratorInterface* _simpleGenerator;
	MazeGeneratorInterface* _myGenerator;
	Astar* _Astar;
	BFS* _BFS;
	searchable<mazeState>* _searchable;
	zip* _zip;

};