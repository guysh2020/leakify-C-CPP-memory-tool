#pragma once
#include"searchable.h"
#include<queue>

template<class type>
class searcher
{
public:
	searcher() = default;
	virtual Solution<type> search(searchable<type>* sol) = 0;
	virtual int getNumberOfEvaluated() = 0;
	~searcher() = default;
};


template<class type>
class commonSearcher : public searcher<type> {
public:
	commonSearcher() : _evaluatedNodes(0) {};
	~commonSearcher()
	{
		int size = _openList.size();
		type* tmp;
		for (int i = 0; i < size; i++)
		{
			tmp = _openList.top();
			_openList.pop();

			delete tmp;
		}
	}
	virtual int getNumberOfEvaluated() { return _evaluatedNodes; };						// need to build
	void resetEnodes() { this->_evaluatedNodes = 0; }

protected:
	int _evaluatedNodes;
	priority_queue <type*,vector<type*>, myComperator> _openList;
};