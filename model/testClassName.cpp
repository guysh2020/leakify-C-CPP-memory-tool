#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include"cell.h"
#include"state.h"


template<class type>
class Maze
{
public:
	Maze(type* start, type* end, string name) : _start(start), _end(end), _isSolved(false), _mazeName(name) {};
	Maze() :_start(nullptr), _end(nullptr), _isSolved(false), _mazeName("") {};
	~Maze() = default;
	void setSolved(bool isSolved) { _isSolved = true; };
	type* getStartPosition()const{ return _start; }
	type* getGoalPosition()const{ return _end; }
	void setStart(type* start) { _start = start; };
	void setEnd(type* end) { _end = end; };
	void setName(string name) { _mazeName = name; };
	virtual vector<string> getPossibleMoves(Position pos)const = 0;

protected:
	bool _isSolved;
	type* _start;
	type* _end;
	string _mazeName;
};


class Maze2d : public Maze<cell>
{
public:
	Maze2d(vector<vector<cell>> maze, string name, cell* start, cell* end);
	Maze2d(vector<vector<int>> maze);

	Maze2d(const Maze2d& m);
	Maze2d() :Maze() {};
	~Maze2d() = default;
	virtual vector<string> getPossibleMoves(Position pos)const;
	cell* getCell(Position pos);
	vector<int> getData();

	cell* findCell(string str, const cell* curr);
	vector<vector<cell>>& getBoard() { return _maze; };

private:
	vector<vector<cell>> _maze;
};