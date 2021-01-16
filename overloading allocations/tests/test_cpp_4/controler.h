#pragma once
#include<unordered_map>
#include"command.h"


class controler
{
public:
	controler(CLI* cli);
	~controler();

	model* getModel();
	view* getView();
	string getInput(string ask);
	void runCommand(vector<string> line);
	void start(istream& in , ostream& out);

private:
	view* _view;
	model* _model;
	unordered_map<string, command*> _commands;

};
