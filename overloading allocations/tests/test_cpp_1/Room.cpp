#include "Room.h"
#include"Hazard.h"
#include "MushMush.h"
#include"SealedRoom.h"
#include "Bat.h"
#include "Pit.h"
#include "Cave.h"
#include <string>
#include <typeinfo>
using namespace std;

Room::Room(int tunnel1, int tunnel2, int tunnel3)
{
	_tunnels[0] = tunnel1;
	_tunnels[1] = tunnel2;
	_tunnels[2] = tunnel3;
	_hazard = NULL;
}
int Room::getTunnel1() const
{
	return _tunnels[0];

}
int Room::getTunnel2() const
{
	
	return _tunnels[1];
}
int Room::getTunnel3() const
{
	return _tunnels[2];
}

bool Room::roomIsEmpty() const
{
	if (_hazard == NULL)
		return true;
	return false;
}
std::string Room::roomHazard() const
{
	if (roomIsEmpty())
		return "\0";
	return _hazard->MessageRoomHazard();
}
const Hazard* Room ::getHazard() const
{
		return _hazard;
}

bool Room::attackInRoom(std::string& message) const
{
	if (typeid(this)==typeid(SealedRoom))
	{
		message="you just shot yourself";
		return true;
	}
	if (roomIsEmpty())
	{
		message = "";
		return false;
	}
	message = _hazard->MessageAttackInRoom();
	return true;

}
bool Room::clashInRoom(std::string& msg) const
{
	if (roomIsEmpty())
	{
		msg = "";
		return true;
	}
	msg = _hazard->MessageClashInRoom();
	return true;

}
bool Room::isMushMushHere() const
{
	if (typeid(_hazard)==typeid(MushMush))
		return true;
	return false;
}

void Room :: setHaz(const std::string& msg) 
{
	if (msg == "MushMush")
		_hazard = new MushMush();
	else
	{
		if (msg == "Pit")
			_hazard = new Pit();
		else
		{

			if (msg == "Bat")
				_hazard = new Bat();
		}
	}
	
}

