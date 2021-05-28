#pragma once
#include "..\UI\UI.h"
#include "..\Data Structures\PriorityQueue.h"
#include"..\Data Structures\Queue.h"
#include "..\Events\Events.h"
#include "..\Missions\Missions.h"
#include "..\Rovers\Rovers.h"

class MarsStation
{

private:
	UI* UI_ptr; // ptr to class dealing with input/output

	int Day;
	int num_PM; // total number of Polar missions
	int num_EM; // total number of Emergency missions

	int num_PR; // total number of Polar Rovers
	int num_ER; // total number of Emergency Rovers

	float Avg_Wait; // average waiting time
	float Avg_InExec;  // average In Execution time
	

	// Lists 

	Queue<Event> Events; // List of all Events in Simulation (From Input File)

	// Waiting Missions Lists
	PriorityQueue<Mission*> Waiting_EM; // List of Waiting Emergency Missions (Sorted according to priority equation)
	Queue<Mission*> Waiting_PM; // List of Waiting polar missions (First in First Out)

	// Available Rovers Lists
	Queue<Rover*> Av_ER; // List of Available Emergency Rovers
	Queue<Rover*> Av_PR; // List of Available polar Rovers

	// UnAvailable Rovers Lists
	Queue<Rover*> InCheckUp_PR; // In check up Polar rovers
	Queue<Rover*> InCheckUp_ER; // In check up Emergency rovers
	PriorityQueue<Rover*> InExec_rov; // Rovers on a mission

	// Completed Missions
	Queue<Mission*> Completed_M; // List of Completed Missions 

public:

	MarsStation(); // Constructor 

	////////////////////////////////////////////////
	void Load();
	void Save();
	///////////////////////////////////////////////
	void AddtoRoverQ(ifstream&); //Adds rovers to a waiting rovers' Queue
	void AddtoEventQ(ifstream &,int); //Add Events to events' Q

	//Simulation Functions

	bool ExecuteEvents(); // checks if it's time to execute an event and does (returns true). If it's not time returns false. (Changeable)
	bool End_Sim(); // Checks if All events are completed
	void Refresh(); // Increments Day, does necessary movements across lists.
	bool Assign(); // checks if missions can be assigned. returns true if yes. false if not.

	// UI Functions

	void ReadMode(); // Calls on UI to read mode from user.
	void PrintOutput(); //Calls on Printoutput from UI


	// Destructor
	~MarsStation();
};