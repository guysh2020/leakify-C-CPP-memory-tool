#pragma once
#include"cell.h"


template<class type>
class State {
public:
	State(type* state, State* prev, double cost = 0);
	State() :_cameFrom(nullptr), _state(nullptr),_cost(0), _h_cost(0) {};
	~State();

	virtual double getStateCost()const;
	virtual double getState_Gcost()const;
	virtual double getState_h_cost()const;
	State* getPrev();
	type* getState();
	void setPrev(State* prev);
	virtual bool operator<(State* other)const = 0;
	virtual bool operator == (State* other)const = 0;

protected:
	double _cost;
	double _h_cost;
	State* _cameFrom;
	type* _state;
};




class mazeState : public State<cell>
{
public:
	mazeState(cell* pos, State<cell>* prev, double cost = 0);
	mazeState() :State() {};

	~mazeState();
	void calculateCost(double stepCost, mazeState* from, double h_cost = 0);
	virtual bool operator == (State<cell>* other)const;
	virtual bool operator<(State<cell>* other)const;

};

class myComperator
{
public:
	int operator() (mazeState* p1, mazeState* p2) { return p1->getStateCost() > p2->getStateCost(); };
};

template<class type>
State<type>::State(type* state, State* prev, double cost) : _cameFrom(prev), _cost(cost), _state(state), _h_cost(0) {};

template<class type>
State<type>::~State() {};

template<class type>
double State<type>::getStateCost()const { return   this->_h_cost + this->_cost; };

template<class type>
double State<type>::getState_h_cost()const { return   this->_h_cost; };

template<class type>
double State<type>::getState_Gcost()const { return  this->_cost; };

template<class type>
State<type>* State<type>::getPrev() { return this->_cameFrom; };

template<class type>
void State<type>::setPrev(State* prev) { this->_cameFrom = prev; };

template<class type>
type* State<type>::getState() { return this->_state; };








