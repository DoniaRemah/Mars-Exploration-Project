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





Rover::~Rover() // Destructor
{

}