#pragma once
#include "..\MarsStation\MarsStation.h"
#include "..\Defs.h"

class Rover
{
private:

	RoverType Type;

	int CheckUp_Duration;
	int speed;
	int Num_Of_ExecMissions;
	int MaxMissions; // Maximum Number of Missions Before Checkup

	bool InCheckUp; 
	bool IsAvailable;

public:

	Rover(RoverType T, int sp, int ChD, int MM); // Constructor (Initializing input data)

	void ResetMissions(); // Resets number of executed missions to 0
	void IncrementMissions(); // Increments number of Executed missions after one is completed

	// Setters 

	void SetInCheckUp(bool status); // Sets Incheckup Status
	void SetIsAvailable(bool status); // sets available status

	// Getters

	bool GetAvailable(); // Gets available status
	bool GetInCheckup(); // Gets Incheckup Status
	int GetNumOfMissions(); // Gets number of executed Missions by this rover

	~Rover(); // Destructor
};
