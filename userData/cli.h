#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"view.h"

using namespace std;

class CLI
{
public:
	CLI(istream& in = cin, ostream& out = cout );
	~CLI();

	void start(view* v);
	istream& getInStream()const;
	ostream& getOutStream()const;
	vector<string> splitInput(string input);
	void printMenue();

private:
	istream& _in;
	ostream& _out;
};