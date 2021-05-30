#pragma once
#include "../Defs.h"
#include "..\MarsStation\MarsStation.h"
#pragma once
class MarsStation;

class Event
{
private:
	MissionType MType;
	int Day;
	int MissionID;
	int Tloc; //mission target location
	int MDuration; //duration needed to fulfill mission requirements
	int MSignificance; // Mission significance
	// Pointer to MarsStation
	MarsStation* Station;

public:

	Event(MissionType type, int d, int id, int targetloc, int duration, int significance) // Constructor
	{
		Day = d;
		MissionID = id;
		Tloc = targetloc;
		MDuration = duration;
		MSignificance = significance;
		MType = type;
	}
	virtual void Execute()
	{

	~Event(); // Destructor

};
