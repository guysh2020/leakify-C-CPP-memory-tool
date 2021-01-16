#pragma once
#include"maze.h"
#include<random>
#include<chrono>
#include <cstdlib>
#include <ctime>



class MazeGeneratorInterface{
public:
	MazeGeneratorInterface() = default;
	~MazeGeneratorInterface() = default;
	virtual Maze2d generate(int size, string name) = 0;
	virtual string measureAlgorithmTime(int size, string name) = 0;
};


class Maze2dGenerator: public MazeGeneratorInterface
{
public:
	Maze2dGenerator():MazeGeneratorInterface(), _end(nullptr),_start(nullptr) {};
	~Maze2dGenerator() = default;
	virtual Maze2d generate(int size, string name) = 0;
	virtual string measureAlgorithmTime(int size, string name);
	cell* getRandomadjacent(cell* ptr);
	int getRandomNumber();
	void removeWalls(cell* one, cell* two);

protected:
	vector <vector<cell>> _maze;
	stack<cell*> _list;
	cell* _start;
	cell* _end;

};


class myMaze2dGenerator : public Maze2dGenerator
{
public:
	myMaze2dGenerator() :Maze2dGenerator() {};
	~myMaze2dGenerator() = default;
	virtual Maze2d generate(int size, string name);
};


class simpleMaze2dGenerator : public Maze2dGenerator
{
public:
	simpleMaze2dGenerator() :Maze2dGenerator() {};
	~simpleMaze2dGenerator() = default;
	void setRandomStartEnd();
	virtual Maze2d generate(int size, string name);
};