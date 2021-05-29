#include "MarsStation.h"
#include<fstream>
#include"../UI/UI.h"
MarsStation::MarsStation()
{
	Day = 1;
}
void MarsStation::Load()
{
	//getting file name from the user
	UI_ptr->OutputStr("Enter the input file name (without the .txt extension) ");
	string filename = UI_ptr->getInput();
	//opening the input file
	ifstream file;
	file.open(filename + ".txt", ios::in);
	//checking if the file is open
	while (!file.is_open()) {
		UI_ptr->OutputStr("Error: file not found.");
		UI_ptr->OutputStr("Enter the input file name (without the .txt extenstion) ");
		filename = UI_ptr->getInput();
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
	if (Day == 1) {
		//getting the file name from the user
		UI_ptr->OutputStr("Enter the output file name (without the .txt extension) ");
		string FileName = UI_ptr->getInput();
		//creating the file
		ofstream* savefile = new ofstream;
		savefile->open(FileName + ".txt", ios::out);
		//saving a pointer to the file in the data member DestinationFile
		DestinationFile = savefile;
		//printing the header
		*savefile << "CD" << "\t" << "ID" << "\t" << "FD" << "\t" << "WD" << "\t" << "ED" << endl;
	}
	//saving the completed missions information
	Save_CompleteM();
	if (End_Sim()) {
		//output the statistics
		*DestinationFile << "Missions: " << num_EM + num_PM << "[P: " << num_PM << " E: " << num_EM << "]" << endl;
		*DestinationFile << "Rovers: " << num_ER + num_PR << "[P: " << num_PR << " E: " << num_ER << "]" << endl;
		*DestinationFile << "Average Wait= " << Total_Wait / (num_EM + num_PM) << "\t" << "Average Exec= " << Total_InExec / (num_EM + num_PM) << endl;
		//closing the file
		DestinationFile->close();
		delete DestinationFile;
	}

}

void MarsStation::Save_CompleteM()
{
	//Dequeue- Save - Delete
	while (!Completed_M.IsEmpty()) {
		Mission* CompletedM;
		Completed_M.dequeue(CompletedM);
		*DestinationFile << CompletedM->GetCD() << "\t" << CompletedM->GetID() << "\t" << CompletedM->GetFD() << "\t" << CompletedM->GetWD() << "\t" << CompletedM->GetED() << endl;
		Completed_ID.enqueue(CompletedM->GetID());
		Total_Wait += CompletedM->GetWD(); //incrementing statistics
		Total_InExec += CompletedM->GetED();
		delete CompletedM;
	}
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
			Event* newevent = new Event(Polar, day, id, targetloc, duration, sig);
			Events.enqueue(newevent);
			num_PM++;
		}
		else {
			Event* newevent = new Event(Emergency, day, id, targetloc, duration, sig);
			Events.enqueue(newevent);
			num_EM++;
		}
	}
}

bool MarsStation::Assign()
{
	bool CanAssign = false;
	Mission* availableM;
	Rover* availableR;
	//assigning Emergency missions first
	while (!Waiting_EM.IsEmpty() && (!Av_ER.IsEmpty() || !Av_PR.IsEmpty())) {
		Waiting_EM.dequeueFront(availableM);
		if (!Av_ER.IsEmpty()) {
			Av_ER.dequeue(availableR);
		}
		else {
			Av_PR.dequeue(availableR);
		}
		availableR->Assign(availableM);
		availableM->Assign(availableR);
		InExec_rov.enqueue(availableR, availableM->GetCD());
		CanAssign = true;
	}
	//assigning Polar missions
	while (!Waiting_PM.IsEmpty() && !Av_PR.IsEmpty()) {
		Waiting_PM.dequeue(availableM);
		Av_PR.dequeue(availableR);
		availableR->Assign(availableM);
		availableM->Assign(availableR);
		InExec_rov.enqueue(availableR, availableM->GetCD());
		CanAssign = true;
	}
	return CanAssign;
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
		Rover* newrover = new Rover(Polar_Rover, PR_speed, PR_checkup, MaxMission);
		Av_PR.enqueue(newrover);
	}
	for (int i = 0; i < num_ER; i++) {
		Rover* newrover = new Rover(Emergency_Rover, ER_speed, ER_checkup, MaxMission);
		Av_ER.enqueue(newrover);
	}
}


void MarsStation::ReadMode()
{
	UI_ptr->ReadMode();
}

MarsStation::~MarsStation()
{
}

bool MarsStation::End_Sim() 
{
	if (Events.IsEmpty() && Waiting_EM.IsEmpty() && Waiting_PM.IsEmpty()) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void MarsStation::Refresh()
{
	Day++; // Incrementing Day for MarsStation class.
	// Re-arranging Queues. 
	//(TODO: Have to add functions where it checks on when to move pointers)
	InCrementWaiting();
	DeCrementCheckUp();
	DeCrementInExecution();


}

void MarsStation::InCrementWaiting()
{
	Mission* m_mission;

	PriorityQueue<Mission*> temp;

	while (!Waiting_EM.IsEmpty()) // Incrementing waiting Days of Emergency Queue
	{
		Waiting_EM.dequeueFront(m_mission);
		m_mission->IncrementWD();
		temp.enqueue(m_mission,m_mission->GetPriority());
	}

	while (!temp.IsEmpty()) // returning missions to original queue
	{
		temp.dequeueFront(m_mission);
		Waiting_EM.enqueue(m_mission,m_mission->GetPriority());
	}

	Queue <Mission*> p_temp;

	while (!Waiting_PM.IsEmpty()) // Incrementing waiting Days of Polar Queue
	{
		Waiting_PM.dequeue(m_mission);
		m_mission->IncrementWD();
		p_temp.enqueue(m_mission);
	}

	while (!p_temp.IsEmpty()) // returning missions to original queue
	{
		p_temp.dequeue(m_mission);
		Waiting_PM.enqueue(m_mission);
	}

}

void MarsStation::DeCrementInExecution()
{
	PriorityQueue<Rover*> temp;

	Rover* m_rover;

	while (!InExec_rov.IsEmpty()) // Decremnting Days left for missions to be executed.
	{
		InExec_rov.dequeueFront(m_rover);
		m_rover->GetMission()->DecrementEX();
		temp.enqueue(m_rover, m_rover->GetMission()->GetCD());
	}

	while (!temp.IsEmpty()) // returning rovers to original queue
	{
		temp.dequeueFront(m_rover);
		InExec_rov.enqueue(m_rover, m_rover->GetMission()->GetCD());
	}
}

void MarsStation::DeCrementCheckUp()
{
	Queue<Rover*> tPR; 
	Queue<Rover*> tER;

	Rover* m_rover;
	while (!InCheckUp_ER.IsEmpty()) // Dec days left for rover on checkup
	{
		InCheckUp_ER.dequeue(m_rover);
		m_rover->DecDaysOver();
		tER.enqueue(m_rover);
	}

	while (!tER.IsEmpty()) // returning rovers to original queue
	{
		tER.dequeue(m_rover);
		InCheckUp_ER.enqueue(m_rover);
	}

	while (!InCheckUp_PR.IsEmpty()) // Dec days left for rover on checkup
	{
		InCheckUp_PR.dequeue(m_rover);
		m_rover->DecDaysOver();
		tPR.enqueue(m_rover);
	}

	while (!tPR.IsEmpty()) // returning rover to original queue
	{
		tPR.dequeue(m_rover);
		InCheckUp_PR.enqueue(m_rover);
	}

}