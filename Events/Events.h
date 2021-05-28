#pragma once
#include "../Defs.h"
#pragma once

class Event
{
protected:
	MissionType MType;
	int Day;
	int MissionID;
	int Tloc; //mission target location
	int MDuration; //duration needed to fulfill mission requirements
	int MSignificance; // Mission significance

public:

	Event(MissionType, int d, int id, int targetloc, int duration, int significance) // Constructor
	{

	}
	virtual void Execute()
	{

	}
	~Event() // Destructor
	{

	}
};
