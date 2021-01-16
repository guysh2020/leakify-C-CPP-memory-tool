#include"cell.h"
#include<iostream>
#include "overloadingAllocations_cpp.h"

//		Position

ostream& operator<<(ostream& output, const Position& pos) {
	output << "{" << pos.getPos_y() << "," << pos.getPos_x() << "}";
	return output;
}

Position::Position(const cell* pos)
{
	_pos = pos->getPos().getPosition();
}

bool Position::operator ==(const Position& other)const
{
	if (getPosition() == other.getPosition())
		return true;

	return false;
}


//    cell

cell::cell(int x , int y ) : _top(true), _right(true), _bottom(true), _left(true), _visited(false), _position(y, x) {};
cell::cell(const cell& a) :_top(a._top), _right(a._right), _bottom(a._bottom), _left(a._left), _visited(a._visited), _position(a._position) {};
cell::cell(const cell* a) :_top(a->_top), _right(a->_right), _bottom(a->_bottom), _left(a->_left), _visited(a->_visited), _position(a->_position) {};



bool cell::operator==(const cell& other)const
{
	return _position == other.getPos();
}

bool Position::operator<(const Position& other)const
{

	string one = to_string(this->_pos.first) + to_string(this->_pos.second);
	string two = to_string(other._pos.first) + to_string(other._pos.second);
	bool ans = one < two;
	return ans;
}

void cell::setPos(int y, int x)
{
	_position.setPos_x(x);
	_position.setPos_y(y);
	_adjacent.push_back({ y - 1,x });
	_adjacent.push_back({ y ,x + 1 });
	_adjacent.push_back({ y + 1 ,x });
	_adjacent.push_back({ y ,x - 1 });
};

void cell::setAdjencts()
{
	int x = _position.getPos_x();
	int y = _position.getPos_y();

	_adjacent.push_back({ y - 1,x });
	_adjacent.push_back({ y ,x + 1 });
	_adjacent.push_back({ y + 1 ,x });
	_adjacent.push_back({ y ,x - 1 });
};

bool cell::getWall(string str) const
{
	if (str == "top")
		return _top;
	if (str == "right")
		return _right;
	if (str == "bottom")
		return _bottom;
	if (str == "left")
		return _left;

	return false;
}

void cell::removeWall(string str)
{
	if (str == "top")
		_top = false;
	if (str == "right")
		_right = false;
	if (str == "bottom")
		_bottom = false;
	if (str == "left")
		_left = false;
};