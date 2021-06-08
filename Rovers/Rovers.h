#pragma once

#include "..\Defs.h"
#include "..\Missions\Missions.h"

class Mission;


class Rover
{
private:

	RoverType Type;

	int CheckUp_Duration;
	int speed;
	int Num_Of_ExecMissions;
	int MaxMissions; // Maximum Number of Missions Before Checkup
	int DaysChOver;
	static int ID;
	int ThisID; //The rover object's ID

	Mission* m_mission; // Pointer to mission the rover is assigned to. Initially set to Null

public:

	Rover(RoverType T, int sp, int ChD, int MM); // Constructor (Initializing input data)

	void ResetMissions(); // Resets number of executed missions to 0
	void IncrementMissions(); // Increments number of Executed missions after one is completed
	void Assign(Mission* R); //Assigning a rover to a mission

	// Setters 

	void SetID(int I_D); //sets ID for this rover
	void SetDaysOver(int x);
	// Getters

	int GetNumOfMissions(); // Gets number of executed Missions by this rover
	int GetSpeed(); //Returns the rover speed
	Mission* GetMission(); //Returns the pointer to the mission the rover is assigned to
	int GetID();//Returns the ID for this rover
	int GetDaysOver();
	RoverType GetType();

	// simulation
	bool MoveToCheckup(); //returns true if the rover excuted a number of missions equal to max missions
	bool EngineFail();	//returns true if the rover's engine failed and it failed to complete the mission
	void HalfSpeed();
	~Rover(); // Destructor
};


