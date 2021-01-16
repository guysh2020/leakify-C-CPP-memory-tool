#pragma once
#include<iostream>
#include<vector>
#include<string>


using namespace std;
class cell;

class Position
{
public:
	Position(const cell* pos);
	Position(int y = 0, int x = 0) : _pos(y, x) {};
	Position(const Position& p) : _pos(p._pos) {};
	Position(pair<int, int> pos) : _pos(pos) {};

	~Position() = default;
	int getPos_x()const { return _pos.second; };
	int getPos_y()const { return _pos.first; };
	pair<int, int> getPosition()const { return _pos; };
	friend ostream& operator<<(ostream& output, const Position& pos);
	void setPos_x(int x) { _pos.second = x; };
	void setPos_y(int y) { _pos.first = y; };
	bool operator ==(const Position& other)const;
	bool operator<(const Position& other)const;
private:
	pair<int, int> _pos;
};

class cell
{
public:
	cell(int x = 0, int y = 0);
	cell(const cell& a);
	cell(const cell* a);
	~cell() = default;
	bool isVisited() const { return _visited; };
	void setVisited(bool state) { _visited = state; };
	Position getPos()const { return _position; };
	vector<pair<int, int>> getAdjacents()const { return _adjacent; };
	bool operator ==(const cell& other)const;
	void setPos(int y, int x);
	void setAdjencts();
	bool getWall(string str) const;
	void removeWall(string str);

private:
	bool _top;
	bool _right;
	bool _bottom;
	bool _left;
	bool _visited;
	vector<pair<int, int>> _adjacent;
	Position _position;
};