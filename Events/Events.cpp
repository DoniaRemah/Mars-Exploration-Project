#include "Events.h"

Event::Event(MarsStation* myStation,MissionType T, int d, int id, int targetloc, int duration, int significance) // Constructor
{
	MType = T;
	Day = d;
	MissionID = id;
	Tloc = targetloc;
	MDuration = duration;
	MSignificance = significance;
	Station = myStation;
}


void Event::Execute()
{
	Station->CreateMission(MType, MissionID, Day, MDuration, MSignificance, Tloc); // Calling on function create mission in Marsstation class
}


int Event::GetDay()
{
	return Day;
}

Event::~Event() // Destructor
{

}
