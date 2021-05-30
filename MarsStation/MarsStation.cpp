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
			Event* event = new Event(this, Polar, day, id, targetloc, duration, sig);
			Events.enqueue(event);
			num_PM++;
		}
		else {
			Event* event = new Event(this, Emergency, day, id, targetloc, duration, sig);
			Events.enqueue(event);
			
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
void MarsStation::PrintOutput()
{
	PriorityQueue<Mission*> copydata;
	Mission*t;
	int counter_waiting_EM = 0;
	while (Waiting_EM.dequeueFront(t))
	{
		copydata.enqueue(t,t->GetPriority());
		counter_waiting_EM++;
	}
	int* arr_EM = new int[counter_waiting_EM++];
	int i = 0;
	while (copydata.dequeueFront(t))
	{
		Waiting_EM.enqueue(t,t->GetPriority());
		arr_EM[i] = (t->GetID());
	}
	int counter_waiting_PM = 0;
	Queue<Mission*> copydata_;
	while (Waiting_PM.dequeue(t))
	{
		copydata_.enqueue(t);
		counter_waiting_PM++;
	}
	int TotalNumberOfWaitingMission = counter_waiting_PM + counter_waiting_EM;
	int* arr_PM = new int[counter_waiting_PM++];
	while (copydata_.dequeue(t))
	{
		Waiting_PM.enqueue(t);
		arr_PM[i] = (t->GetID());
	}
	Rover* M;
	PriorityQueue<Rover*> copydata2;
	int counter_EMInEXEC = 0;
	int counter_PMInEXEC = 0;
	while (InExec_rov.dequeueFront(M))
	{
		if (M->GetMission()->GetTypeOfMission() == Emergency)
		{
			counter_EMInEXEC++;
		}
		else
		{
			counter_PMInEXEC++;

		}
		copydata2.enqueue(M,M->GetMission()->GetCD());
	}
	int* arr_InExec_EM_rover = new int[counter_EMInEXEC * 2];
	int* arr_InExec_PM_rover = new int[counter_PMInEXEC * 2];
	int j = 0;
	int f = 0;
	while (copydata2.dequeueFront(M))
	{
		if (M->GetMission()->GetTypeOfMission() == Emergency)
		{
			arr_InExec_EM_rover[j] = M->GetMission()->GetID();
			j++;
			arr_InExec_EM_rover[j] = M->GetID();
		}
		else
		{
			arr_InExec_PM_rover[f] = M->GetMission()->GetID();
			f++;
			arr_InExec_PM_rover[f] = M->GetID();
		}
	}
	j = 0;
	Queue<Rover*>k_;
	int counter_Av_ER=0;
	while (Av_ER.dequeue(M))
	{
		counter_Av_ER++;
		k_.enqueue(M);
	}
	int* arr_Av_ER = new int[counter_Av_ER];
	while (k_.dequeue(M))
	{
		arr_Av_ER[j] = M->GetID();
		Av_ER.enqueue(M);
	}
	j = 0;
	int counter_Av_PR = 0;
	while (Av_PR.dequeue(M))
	{
		counter_Av_PR++;
		k_.enqueue(M);
	}
	int* arr_Av_PR = new int[counter_Av_PR];
	while (k_.dequeue(M))
	{
		arr_Av_PR[j] = M->GetID();
		Av_PR.enqueue(M);
	}
	j = 0;
	int counter_InCheckUp_PR = 0;
	while (InCheckUp_PR.dequeue(M))
	{
		counter_InCheckUp_PR++;
		k_.enqueue(M);
	}
	int* arr_InCheckUp_PR = new int[counter_InCheckUp_PR];
	while (k_.dequeue(M))
	{
		arr_InCheckUp_PR[j] = M->GetID();
		InCheckUp_PR.enqueue(M);
	}
	int counter_InCheckUp_ER = 0;
	while (InCheckUp_PR.dequeue(M))
	{
		counter_InCheckUp_ER++;
		k_.enqueue(M);
	}
	int* arr_InCheckUp_ER = new int[counter_InCheckUp_ER];
	while (k_.dequeue(M))
	{
		arr_InCheckUp_ER[j] = M->GetID();
		InCheckUp_ER.enqueue(M);
	}
	int counter_Completed_EM = 0;
	int counter_Completed_PM = 0;
	while (Completed_M.dequeue(t))
	{
		if (t->GetTypeOfMission() == Emergency)
		{
			counter_Completed_EM++;
		}
		else 
		{
			counter_Completed_PM++;
		}
		copydata_.enqueue(t);
	}
	int* arr_Completed_EM = new int[counter_Completed_EM];
	int* arr_Completed_PM = new int[counter_Completed_PM];
	int E = 0;
	int P = 0;
	while (copydata_.dequeue(t))
	{
		if (t->GetTypeOfMission() == Emergency)
		{
			arr_Completed_EM[E] = t->GetID();
		}
		else
		{
			arr_Completed_PM[P] = t->GetID();
		}
		Completed_M.enqueue(t);
	}

	UI_ptr->PrintOutput(Day, TotalNumberOfWaitingMission, counter_waiting_EM, arr_EM, counter_waiting_PM, arr_PM, counter_EMInEXEC, arr_InExec_EM_rover, counter_PMInEXEC, arr_InExec_PM_rover, counter_Av_ER, arr_Av_ER, counter_Av_PR, arr_Av_PR, counter_InCheckUp_ER, arr_InCheckUp_ER, counter_InCheckUp_PR, arr_InCheckUp_PR, counter_Completed_EM, arr_Completed_EM, counter_Completed_PM, arr_Completed_PM);
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
	InCrementWaiting();
	DeCrementCheckUp();
	DeCrementInExecution();

	// Moving Functions

	MoveCompMissions();
	MoveCheckUpRovers();

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
	float x = 0;
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

void MarsStation::CreateMission(MissionType T, int id, int FD, int MD, int sig, int TL)
{
	Mission* NewMission = new Mission(T, id, FD, MD, sig, TL); // Creating a mission object

	if (T == 0) // If mission is an emergency mission add to Priority Queue of waiting emergency missions
	{
		NewMission->CalculatePriority(); // calculating priority if mission is emergency.
		Waiting_EM.enqueue(NewMission, NewMission->GetPriority()); 
	}
	else if (T == 1) // If mission is a polar mission add to Queue of waiting polar missions
	{
		Waiting_PM.enqueue(NewMission); 
	}
}

void MarsStation::MoveCompMissions()
{
	Rover* m_rover;

	// Checking on Finished Missions

	while (InExec_rov.peekBack(m_rover)) // Getting mission soon to be finished / finished.
	{
		if (m_rover->GetMission()->GetCD() == Day) // If the day to be finished has come
		{
			float x;
			InExec_rov.dequeueBack(m_rover, x); // Getting Finished mission
			Completed_M.enqueue(m_rover->GetMission()); // Putting it in completed missions queue
		}
		else
		{
			break;
		}
	}
}

void MarsStation::MoveCheckUpRovers()
{
	// Checking on Rovers in Checkup-Queues.

	Rover* m_rover;

	while (InCheckUp_ER.peek(m_rover)) // Getting Emergency rover soon to be finished / finished.
	{
		if (m_rover->GetDaysOver() == 0) // If rover has finished checkup
		{
			InCheckUp_ER.dequeue(m_rover); // remove from checkup queue
			Av_ER.enqueue(m_rover); // Add to available queue.
		}
		else
		{
			break;
		}
	}

	while (InCheckUp_PR.peek(m_rover)) // Getting Polar rover soon to be finished / finished.
	{
		if (m_rover->GetDaysOver() == 0) // If rover has finished checkup
		{
			InCheckUp_PR.dequeue(m_rover); // remove from checkup queue
			Av_PR.enqueue(m_rover); // Add to available queue.
		}
		else
		{
			break;
		}
	}
}

bool MarsStation::ExecuteEvents()
{
	return true;
}

void MarsStation::PrintStatistics()
{

}