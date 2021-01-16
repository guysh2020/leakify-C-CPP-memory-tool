#pragma once
#include "Room.h"
#include "overloadingAllocations_cpp.h"
class RegularRoom:public Room
{
public:
	RegularRoom(int n1, int n2, int n3) :Room(n1, n2, n3) {}
};

