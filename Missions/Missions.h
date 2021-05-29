#pragma once
#include "..\Defs.h"
#include"..\Rovers\Rovers.h"

class Rover;

class Mission
{
private:

	MissionType Type;

	int ID;
	int FormulationDay;
	int WaitingDays;
	int ExecutionDays;
	int CompletionDay;
	int MissionDuration;   
	int Significance;
	int TLocation;   // Distance from location of the mission from the base station
	float priority; // For emergency missions only. Initially set to 0.
	int DaysToBeOver;
	Rover* m_rover;

public:

	Mission(MissionType T, int id, int FD, int MD, int sig, int TL); // Constructor (Initializing Input Data)

	void Assign(Rover* R); // Assigning a rover to a mission

	void CalculateED(); // Calculates Execution Days
	void CalculateCD(); // Calculates Completion Day
	void CalculatePriority(); // (For EMERGENCY MISSIONS ONLY) Creating a priority equation depending on : FD, Target  location, the mission duration, and the significance 

	// Incrementing Functions

	void IncrementWD();
	void DecrementEX();

	// Getters
	int GetID();
	int GetFD(); // Gets Formulation Day
	int GetWD(); // Gets Waiting Days
	int GetED(); // Gets Execution Days
	int GetCD(); // Gets Completion Day
	float GetPriority(); // Gets Priority of mission
	MissionType GetTypeOfMission();
	~Mission(); // Destructor

};
