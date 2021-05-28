#include "Rovers.h"

Rover::Rover(RoverType T, int sp, int ChD, int MM) // Constructor (Initializing input data)
{
	Type = T;
	speed = sp;
	CheckUp_Duration = ChD;
	MaxMissions = MM;
	m_mission = nullptr;
}


void Rover::Assign(Mission* M) 
{
	m_mission = M;
}


int Rover::GetSpeed() 
{
	return speed;
}

Mission* Rover::GetMission()
{
	return m_mission;
}

void Rover::ResetMissions() 
{
	Num_Of_ExecMissions = 0;
}

void Rover::IncrementMissions() 
{
	Num_Of_ExecMissions++;
}

void Rover::SetInCheckUp(bool status) 
{
	InCheckUp = status;
}

void Rover::SetIsAvailable(bool status)
{
	IsAvailable = status;
}

bool Rover:: GetAvailable()
{
	return IsAvailable;
}

bool Rover::GetInCheckup() 
{
	return InCheckUp;
}

int Rover::GetNumOfMissions() 
{
	return Num_Of_ExecMissions;
}


void Rover::DecDaysOver()
{
	DaysChOver--;
}

Rover::~Rover() // Destructor
{

}