#include "MarsStation.h"
#include<fstream>

void MarsStation::Load()
{
	//getting file name from the user
	UI_ptr->OutputStr("Enter file name (without the .txt extension) ");
	string filename = UI_ptr->getInput();
	//opening the input file
	ifstream file;
	file.open(filename + ".txt", ios::in);
	//checking if the file is open
	while (!file.is_open()) {
		UI_ptr->OutputStr("Error: file not found.");
		UI_ptr->OutputStr("Enter file name (without the .txt extenstion) ");
		file.open(filename + ".txt", ios::in);
	}
	//adding the rovers to their respective queues
	AddtoRoverQ(file);
	//reading no. of events
	int content;
	file >> content;
	AddtoEventQ(file, content);
}

void MarsStation::Save()
{
	/*if (Day == 1) {

	}
	while (!Completed_M.IsEmpty()) {
		Mission* mission;
		Completed_M.dequeue(mission);
		

	}*/
}

void MarsStation::AddtoEventQ(ifstream & file, int NumEvents)
{
	for (int i = 0; i < NumEvents; i++) {
		//reading event information
		char MissionTyp;
		file >> MissionTyp;
		int day;
		file >> day;
		int id;
		file >> id;
		int targetloc;
		file >> targetloc;
		int duration;
		file >> duration;
		int sig;
		file >> sig;
		
		//creating event
		if (MissionTyp == 'P') {
			Event* event = new Event(Polar, day, id, targetloc, duration, sig);
			num_PM++;
		}
		else {
			Event* event = new Event(Emergency, day, id, targetloc, duration, sig);
			num_EM++;
		}
	}
}

bool MarsStation::Assign()
{

	return false;
}

void MarsStation::AddtoRoverQ(ifstream & file)
{
	//reading file content
	int content;
	file >> content;
	num_PR = content;
	file >> content;
	num_ER = content;
	file >> content;
	int PR_speed = content;
	file >> content;
	int ER_speed = content;
	file >> content;
	int MaxMission = content;
	file >> content;
	int PR_checkup = content;
	file >> content;
	int ER_checkup = content;
	//creating rovers and adding them to the queue
	for (int i = 0; i < num_PR; i++) {
		Rover* rover = new Rover(Polar_Rover, PR_speed, PR_checkup, MaxMission);
		Av_PR.enqueue(rover);
	}
	for (int i = 0; i < num_ER; i++) {
		Rover* rover = new Rover(Emergency_Rover, ER_speed, ER_checkup, MaxMission);
		Av_ER.enqueue(rover);
	}
}
