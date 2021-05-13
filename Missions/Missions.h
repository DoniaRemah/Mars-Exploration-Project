#pragma once
#include "..\Defs.h"
#include "..\Rovers\Rovers.h"

class Mission
{
private:

	Rover* m_Rover; // Pointer to rover assigned to mission. Initially Set to Null

	MissionType Type;

	int ID;
	int FormulationDay;
	int WaitingDays;
	int ExecutionDays;
	int CompletionDays;
	int MissionDuration;
	int Significance;
	int TLocation;

	bool AutoPromotion; // Set to False 

public:

	Mission(MissionType T, int id, int FD, int MD, int sig, int TL); // Constructor (Initializing Input Data)

	void Assign(Rover* R);

	void CalculateED(); // Calculates Execution Days
	void CalculateCD(int d); // Calculates Completion Day

	// Getters
	int GetID();
	bool GetAutoP(); // gets status of AutoPromotion
	int GetFD(); // Gets Formulation Day
	int GetWD(); // Gets Waiting Days
	int GetED(); // Gets Execution Days

	// Setters

	void SetAutoP(bool status);


	~Mission(); // Destructor

};
