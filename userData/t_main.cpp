#include"cell.h"
#include"maze.h"
#include"state.h"
#include"generator.h"
#include"dirent.h"
#include<istream>
#include<ostream>
#include<unordered_map>
#include"zip.h"
#include"bfs.h"
#include"Astar.h"
#include"controler.h"
#include"Demo.h"



#include"..\appData\overloadingAllocations_cpp.h"

int main()
{
	controler c(new CLI());
	c.start(cin, cout);
}

