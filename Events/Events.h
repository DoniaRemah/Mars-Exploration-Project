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

	Event(MarsStation* myStation, MissionType T, int d, int id, int targetloc, int duration, int significance); // Constructor

	void Execute();

	~Event(); // Destructor

};
