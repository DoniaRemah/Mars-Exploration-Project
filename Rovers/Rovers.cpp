#include "Rovers.h"

Rover::Rover(RoverType T, int sp, int ChD, int MM) // Constructor (Initializing input data)
{
	Type = T;
	speed = sp;
	CheckUp_Duration = ChD;
	MaxMissions = MM;
}






Rover::~Rover() // Destructor
{

}