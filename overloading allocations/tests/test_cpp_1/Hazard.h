#pragma once
#include <string>
//
#include "overloadingAllocations.h"
//
using namespace std;
class Bat;
class MushMush;
class Pit;

class Hazard
{
public:
	Hazard() { ; }
	virtual std::string MessageRoomHazard() const = 0;
	virtual std::string MessageAttackInRoom() const = 0;
	virtual std::string MessageClashInRoom() const = 0;
};



