#pragma once
#include "Hazard.h"
#include <iostream>
//
#include "overloadingAllocations.h"
//
using namespace std;

class MushMush:public Hazard
{
public:
	MushMush() { ; }
	virtual std::string MessageRoomHazard() const { return "MushMush is near"; }
	virtual std::string MessageAttackInRoom() const { return "You got MushMush"; }
	virtual std::string MessageClashInRoom() const { return "MushMush got you"; }

};

