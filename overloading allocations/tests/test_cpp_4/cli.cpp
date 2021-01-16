#include"cli.h"
#include "Demo.h"
#include "overloadingAllocations_cpp.h"



CLI::CLI(istream& in, ostream& out) : _in(in), _out(out) {};

CLI::~CLI() {};

void CLI::start(view* v)
{
	string input;
	string command;
	vector<string> line;
	
	while (input != "exit")
	{
		printMenue();
		cout << ">";
		getline(cin, input);

		line = splitInput(input);
		system("cls");
		v->runCommand(line);
	}
}

istream& CLI::getInStream()const { return _in; };
ostream& CLI::getOutStream()const { return _out; };

void CLI::printMenue()
{
	_out << endl;
	_out << "commands format:" << endl;
	_out << "dir <path>" << endl;
	_out << "generate maze <size> <name> <type - my/simple>" << endl;
	_out << "display <name>" << endl;
	_out << "save maze <name> <file name>" << endl;
	_out << "load maze <file name> <name>" << endl;
	_out << "maze size <name>" << endl;
	_out << "file size <name>" << endl;
	_out << "solve <name> <algorithem - Astar/BFS> <heuristic - manheten/airdist (optional)>" << endl;
	_out << "display solution <name>" << endl;
	_out << "exit" << endl;
}

vector<string> CLI::splitInput(string input)
{
	vector<string> ans;
	string tmp;

	for (auto it : input)
	{
		if (it == ' ')
		{
			ans.push_back(tmp);
			tmp.clear();
		}
		else
			tmp += it;
	}
	ans.push_back(tmp);
	return ans ;
}
