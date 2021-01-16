#pragma once
#include"generator.h"
#include"bfs.h"
#include"Astar.h"
#include"controler.h"
#include"cli.h"

class Demo
{
public:
    Demo();
    ~Demo();
    void run(int size, string name);
private:
    controler* _con;
};
