#include "Cave.h"
#include "SealedRoom.h"
#include "RegularRoom.h"
Cave :: Cave(const int* const sealedRooms, int size)
{
	caveMatrix[0] = new RegularRoom(2 ,18 ,19);
	caveMatrix[1] = new RegularRoom(5, 17, 18);
	caveMatrix[2] = new RegularRoom(0 , 4 , 17);
	caveMatrix[3] = new RegularRoom(7, 16, 19);
	caveMatrix[4] = new RegularRoom(2, 6, 15);
	caveMatrix[5] = new RegularRoom(1, 9, 14);
	caveMatrix[6] = new RegularRoom(4, 8, 13);
	caveMatrix[7] = new RegularRoom(3, 11, 12);
	caveMatrix[8] = new RegularRoom(6, 10, 11);
	caveMatrix[9] = new RegularRoom(5, 10, 13);
	caveMatrix[10] = new RegularRoom(8, 9, 12);
	caveMatrix[11] = new RegularRoom(7, 8, 15);
	caveMatrix[12] = new RegularRoom(7, 10, 14);
	caveMatrix[13] = new RegularRoom(6, 9, 17);
	caveMatrix[14] = new RegularRoom(5, 12, 16);
	caveMatrix[15] = new RegularRoom(4, 11, 19);
	caveMatrix[16] = new RegularRoom(3, 14, 18);
	caveMatrix[17] = new RegularRoom(1, 2, 13);
	caveMatrix[18] = new RegularRoom(0, 1, 16);
	caveMatrix[19] = new RegularRoom(0, 3, 15);

	for (int i = 0; i < size; i++)
	{
		int t1=caveMatrix[sealedRooms[i]]->getTunnel1();
		int t2 = caveMatrix[sealedRooms[i]]->getTunnel2();
		int t3 = caveMatrix[sealedRooms[i]]->getTunnel3();
		delete caveMatrix[sealedRooms[i]];
		caveMatrix[sealedRooms[i]]=new SealedRoom(t1, t2, t3);
	}
	player = -1;
}

Cave::~Cave()
{
	for (int i = 0; i < 20; i++)
		delete caveMatrix[i];
}


void Cave::plotHazard(int idx, const std::string& eventName)
{
	if ((idx < 0) || (idx > 19) || (caveMatrix[idx]->getHazard() != NULL))
		throw ("Invalid Index Exception");
	caveMatrix[idx]->setHaz(eventName);

	
}
void Cave::plotPlayerIdx(int idx)
{
	if ((idx < 0) || (idx > 19) || (caveMatrix[idx]->getHazard() != NULL))
		throw ("Invalid Index Exception");
	else
		player = idx;
}

int Cave::findMushMush(void) const
{
	for (int i = 0; i < 20; i++)
	{
		if (caveMatrix[i]->isMushMushHere())
			return i;
	}
	throw ("MushMush Not Found Exception");
}

void Cave::movePlayer(int idx)
{
	if ((caveMatrix[player]->getTunnel1() == idx) || (caveMatrix[player]->getTunnel2() == idx) || (caveMatrix[player]->getTunnel3() == idx) && idx <= 19 && idx >= 0)
		player = idx;
	else
		throw ("Invalid Index Exception");
	if (caveMatrix[idx]->isMushMushHere()||caveMatrix[idx]->roomHazard()=="Pit is near")
		_gameOver = true;
}


std::string Cave::playerAttack(int idx)
{
	bool flag;
	string str;

	if (idx > 19 || idx < 0)
		throw "Invalid Index Exception";

	if (idx != caveMatrix[player]->getTunnel1() && idx != caveMatrix[player]->getTunnel2() && idx != caveMatrix[player]->getTunnel3())
		throw "Invalid Index Exception";

		flag = caveMatrix[player]->attackInRoom(str);
		if (flag == false)
		{
			int t1 = caveMatrix[player]->getTunnel1();
			int t2 = caveMatrix[player]->getTunnel2();
			int t3 = caveMatrix[player]->getTunnel3();
			if (caveMatrix[t1]->roomIsEmpty())
			{
				caveMatrix[t1]->setHaz("MushMush");
				return str;
			}
			if (caveMatrix[t2]->roomIsEmpty())
			{
				caveMatrix[t2]->setHaz("MushMush");
				return str;
			}
			if (caveMatrix[t3]->roomIsEmpty())
			{
				caveMatrix[t3]->setHaz("MushMush");
				return str;
			}
		}
		else
		{
			if (str == "you just shoot yourself")
			{
				_gameOver = true;
				return str;
			}
			if (str == "you got MushMush")
			{
				_gameOver = true;
				return str;
			}


		}
	

	// if ((caveMatrix[flag]->getTunnel1() == NULL) || (caveMatrix[flag]->getTunnel2() == NULL) || (caveMatrix[flag]->getTunnel3() == NULL))
	// 	caveMatrix[flag]->setHaz("MushMush");
	return str;
}

bool Cave::gameOver() const
{
	return _gameOver;
}
const Room* Cave:: getRoomAtIndex(int index) const
{
	if ((index > 19) || (index < 0))
	{
		throw ("Invalid Index Exception");
	}
	return caveMatrix[index];
}
 
std::string Cave::playerClash(int idx)
{
	string theMessage;
	if (idx > 19 || idx < 0)
		throw "Invalid Index Exception";

	else if (caveMatrix[player]->roomHazard() == "Bat is near")     //there is a Bat in the room
	{
		caveMatrix[player]->setHaz("removeBat");					//hazard will be Null, no longer Bat
		movePlayer(idx);											//move the player to room idx
																	//recursive for the pusibility there is a Bat in the idx room
		return playerClash(idx + 1);								//return the last message
	}

	else if (caveMatrix[player]->clashInRoom(theMessage) == false)		//no clash - hazard == Null
		return theMessage;                                          //return ""

	else
	{
		_gameOver = true;
		caveMatrix[player]->clashInRoom(theMessage);						//there is a clash
		return theMessage;											 //return clash message
	}

}

void Cave::hazardNearPlayer(std::string* hazards) const
{

	int t1 = caveMatrix[player]->getTunnel1();
	int t2 = caveMatrix[player]->getTunnel2();
	int t3 = caveMatrix[player]->getTunnel3();

	hazards[0] = caveMatrix[t1]->roomHazard();
	hazards[1] = caveMatrix[t2]->roomHazard();
	hazards[2] = caveMatrix[t3]->roomHazard();
}

