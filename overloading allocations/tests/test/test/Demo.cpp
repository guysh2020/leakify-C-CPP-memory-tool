#include "Demo.h"

Demo::Demo() : _con(nullptr)
{
    _con = new controler(new CLI());
}

Demo::~Demo()
{
    delete _con;
}

void Demo::run(int size, string name)
{

    _con->getModel()->generteMaze(size, name, "my");
    Maze2d *cur = _con->getModel()->getMaze(name);
    vector<mazeState> sol;
    view *v = _con->getView();
    model *m = _con->getModel();
    v->printMaze(cur->getBoard(), cur->getStartPosition(), cur->getGoalPosition());
    v->print("");

    m->solve(name, "BFS", "", false);
    sol = _con->getModel()->getSolution(name);
    v->printMaze(cur->getBoard(), cur->getStartPosition(), cur->getGoalPosition(), &sol);
    cout << "here" << endl;
    int bfs_nodes = _con->getModel()->getEvaluatedNodes("BFS");
    v->print("");

    cout << "here" << endl;
    m->solve(name, "Astar", "manheten", false);
    sol = _con->getModel()->getSolution(name);
    v->printMaze(cur->getBoard(), cur->getStartPosition(), cur->getGoalPosition(), &sol);
    v->printSolution(sol);
    v->print("");
    int a_manheten = _con->getModel()->getEvaluatedNodes("Astar");
    cout << "here2" << endl;
    m->solve(name, "Astar", "air_distance", false);
    sol = _con->getModel()->getSolution(name);
    v->printMaze(cur->getBoard(), cur->getStartPosition(), cur->getGoalPosition(), &sol);
    v->printSolution(sol);
    int a_air = _con->getModel()->getEvaluatedNodes("Astar");
    v->print("");

    v->print("");
    v->print("number of evaluated nodes for bfs: " + to_string(bfs_nodes));
    v->print("number of evaluated nodes for A* manheten: " + to_string(a_manheten));
    v->print("number of evaluated nodes for A* air dist: " + to_string(a_air));
}
