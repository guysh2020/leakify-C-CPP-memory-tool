#pragma once
#include "Room.h"
//
#include "overloadingAllocations.h"
//
class SealedRoom:public Room
{
public:
	SealedRoom(int n1, int n2, int n3) :Room(n1, n2, n3) {}

};

