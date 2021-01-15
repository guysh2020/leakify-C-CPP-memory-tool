#include"state.h"

// maze state         

mazeState::mazeState(cell* pos, State<cell>* prev, double cost) :State<cell>(pos, prev, cost) {};


mazeState::~mazeState() {};


bool mazeState::operator<(State<cell>* other)const
{
	cout << "left: " << this->_cost + this->_h_cost << " right: " << other->getStateCost()<< endl;
	if (this->_cost + this->_h_cost < other->getStateCost())
	{
		cout << "choose left" << endl;
		return true;
	}

	cout << "choose right" << endl;
	return false;
};



void mazeState::calculateCost(double stepCost, mazeState* from, double h_cost)
{
	this->_cost = 0;
	this->_h_cost = 0;
	if (from == this)
		this->_cost = 0;
	else
		this->_cost = from->_cost + stepCost;

	this->_h_cost = h_cost;
}



bool mazeState::operator == (State<cell>* other)const
{
	mazeState* tmp = dynamic_cast<mazeState*>(other);
	if (this->_state == tmp->_state)
		return true;

	return false;
}
