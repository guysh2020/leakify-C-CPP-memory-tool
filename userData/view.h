#pragma once
#include"maze.h"

class CLI;
class controler;

class view
{
public:
	view(controler* cont, CLI* cli);
	~view();
	void printMaze(vector<vector<cell>>& _maze, cell* start, cell* end, vector<mazeState>* s = nullptr);
	void printSolution(vector<mazeState>& solution);
	void print(string str);
	void start(istream& in, ostream& out);
	void runCommand(vector<string> s);
	string getInput(string ask);
	controler* getControler();

private:
	controler* _cont;
	CLI* _cli;
};