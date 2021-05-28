#include "Missions.h"

Mission::Mission(MissionType T, int id, int FD, int MD, int sig, int TL)
{
	Type = T;
	ID = id;
	FormulationDay = FD;
	MissionDuration = MD;
	Significance = sig;
	TLocation = TL;
}



