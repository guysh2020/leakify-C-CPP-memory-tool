#include<unordered_map>
#include"command.h"
#include"controler.h"
#include "overloadingAllocations_cpp.h"



	controler::controler(CLI* cli): _view(nullptr), _model(nullptr)
	{
		srand((int)time(0));
		_view = new view(this, cli);
		_model = new model(this);
		_commands["dir"] = new dirCommand();
		_commands["generate maze"] = new generateMazeCommand();
		_commands["display"] = new displayCommand();
		_commands["save maze"] = new saveMazeCommand();
		_commands["load maze"] = new loadMazeCommand();
		_commands["maze size"] = new mazeSizeCommand();
		_commands["file size"] = new fileSizeCommand();
		_commands["solve"] = new solveCommand();
		_commands["display solution"] = new displaySolutionCommand();
		_commands["exit"] = new exitCommand();
	}

	controler::~controler()
	{
		for (auto it = _commands.begin(); it != _commands.end(); it++)
			delete it->second;

		delete _view;
		delete _model;
	}

	model* controler::getModel() { return _model; };

	view* controler::getView() { return _view; };

	string controler::getInput(string ask)
	{
		return _view->getInput(ask);
	}

	void controler::start(istream& in, ostream& out)
	{
		_view->start(in, out);
	}

	void controler::runCommand(vector<string> line)
	{
		string command;
		int flag = 0;
		command = line[0];

		if (line.size() < 2 && command != "exit")
		{
			_view->print("invalid input, try again.");
			return;
		}

		if (command == "exit")
			return;



		if (command == "dir" || command == "solve" || command == "display" && line[1] != "solution")
		{
			auto it = _commands.find(command);
			if (it != _commands.end())
				_commands[command]->execute(line, this);
			else
				flag = 1;
		}	
		else
		{
			command += " " + line[1];

			auto it = _commands.find(command);
			if (it != _commands.end())
				_commands[command]->execute(line, this);
			else
				flag = 1;
		}

		if (flag)
			_view->print("invalid input, try again.");

	}


