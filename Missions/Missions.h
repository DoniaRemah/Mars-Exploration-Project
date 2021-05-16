#pragma once
#include "..\Defs.h"

class Mission
{
private:

	MissionType Type;

	int ID;
	int FormulationDay;
	int WaitingDays;
	int ExecutionDays;
	int CompletionDays;
	int MissionDuration;
	int Significance;
	int TLocation;
	float priority; // For emergency missions only. Initially set to 0.

public:

	Mission(MissionType T, int id, int FD, int MD, int sig, int TL); // Constructor (Initializing Input Data)

	void Assign(Rover* R);

	void CalculateED(); // Calculates Execution Days
	void CalculateCD(int d); // Calculates Completion Day

	// Getters
	int GetID();
	int GetFD(); // Gets Formulation Day
	int GetWD(); // Gets Waiting Days
	int GetED(); // Gets Execution Days

	~Mission(); // Destructor

};
