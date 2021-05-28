#include "MarsStation.h"
#include"../UI/UI.h"
void MarsStation::ReadMode()
{
	UI_ptr->ReadMode();
}

bool MarsStation::End_Sim() 
{
	if (Events.IsEmpty() && Waiting_EM.IsEmpty() && Waiting_PM.IsEmpty()) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}