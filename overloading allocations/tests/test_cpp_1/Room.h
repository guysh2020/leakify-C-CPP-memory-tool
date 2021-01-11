#pragma once
#include <string>
#include "Cave.h"
#include "Hazard.h"
#include <string>
//
#include "overloadingAllocations.h"
//
using namespace std;

class Hazard;
class RegularRoom;
class SealedRoom;
#pragma pack(push, 1)
class Room
{
public:
	Room(int tunnel1, int tunnel2, int tunnel3);
	bool attackInRoom(std::string& message) const;
	int getTunnel1() const;
	int getTunnel2() const;
	int getTunnel3() const;
	std::string roomHazard() const;
	const Hazard* getHazard() const;
	bool roomIsEmpty() const;
	bool isMushMushHere() const;
	bool clashInRoom(std::string& msg) const;
	//virtual bool getPlayer()=0;
//	virtual void setPlayer() = 0;
	void setHaz(const std::string& msg);


protected:
	const Hazard* _hazard;
private:
	int _tunnels[3];
};
#pragma pack(pop)

