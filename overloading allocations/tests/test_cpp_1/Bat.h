#pragma once
#include "Hazard.h"
#include <iostream>
//
#include "overloadingAllocations.h"
//
using namespace std;
class Bat:public Hazard
{
public:
	Bat() { ; }
	virtual std::string MessageRoomHazard() const { return "Bat is near"; }
	virtual std::string MessageAttackInRoom() const { return "Bat is laughing"; }
	virtual std::string MessageClashInRoom() const { return "A bat will move you"; }
};

