#pragma once
#include"maze.h"
#include"dirent.h"
#include"view.h"
#include"model.h"
#include<fstream>

class controler;


class command {
public:
	command() = default;
	~command() = default;
	virtual void execute(vector<string> vec, controler* con) = 0;
};

class exitCommand : public command
{
public:
	exitCommand() = default;
	~exitCommand() = default;
	virtual void execute(vector<string>vec, controler* con);
};


class mazeSizeCommand : public command 
{
public:
	mazeSizeCommand() = default;
	~mazeSizeCommand() = default;
	virtual void execute(vector<string>vec, controler* con);
};


class displaySolutionCommand : public command
{
public:
	displaySolutionCommand() = default;
	~displaySolutionCommand() = default;
	virtual void execute(vector<string> vec, controler* con);
};


class solveCommand : public command
{
public:
	solveCommand() = default;
	~solveCommand() = default;
	virtual void execute(vector<string> vec, controler* con);
};


class fileSizeCommand : public command
{
public:
	fileSizeCommand() = default;
	~fileSizeCommand() = default;
	virtual void execute(vector<string> vec, controler* con);

};


class generateMazeCommand : public command {
public:
	generateMazeCommand() = default;
	~generateMazeCommand() = default;
	virtual void execute(vector<string> vec, controler* con);
};


class dirCommand : public command
{
public:
	dirCommand() = default;
	~dirCommand() = default;
	virtual void execute(vector<string> vec, controler* con);
};



class displayCommand : public command {
public:
	displayCommand() = default;
	~displayCommand() = default;
	virtual void execute(vector<string> vec, controler* con);
};


class saveMazeCommand : public command {
public:
	saveMazeCommand() = default;
	~saveMazeCommand() = default;
	virtual void execute(vector<string> vec, controler* con);
};



class loadMazeCommand : public command {
public:
	loadMazeCommand() = default;
	~loadMazeCommand() = default;
	virtual void execute(vector<string> vec, controler* con);
};