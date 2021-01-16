#pragma once
#include "Hazard.h"
#include <iostream>
#include "overloadingAllocations_cpp.h"
using namespace std;
class Pit:public Hazard
{
public:
	Pit() { ; }
	virtual std::string MessageRoomHazard() const { return "Pit is near"; }
	virtual std::string MessageAttackInRoom() const { return "Pit is whistling"; }
	virtual std::string MessageClashInRoom() const { return "You fell into pit"; }

};

