#include "MarsStation.h"
#include<fstream>
#include"../UI/UI.h"
MarsStation::MarsStation()
{
	Day = 1;
	Count_Completed_EM = 0;
	Count_Completed_PM = 0;
	UI_ptr = new UI;
}
bool MarsStation::Load()
{
	//getting file name from the user
	UI_ptr->OutputStr("Enter the INPUT file name (without the .txt extension) ");
	string filename = UI_ptr->getInput();
	//opening the input file
	ifstream file;
	file.open(filename + ".txt", ios::in);
	//checking if the file is open
	while (!file.is_open()) {
		UI_ptr->OutputStr("Error: file not found.");
		UI_ptr->OutputStr("Enter the INPUT file name (without the .txt extenstion) ");
		filename = UI_ptr->getInput();
		file.open(filename + ".txt", ios::in);
	}
	//adding the rovers to their respective queues
	AddtoRoverQ(file);
	//reading no. of events
	int content;
	file >> content;
	AddtoEventQ(file, content);
	//checking if there were no rovers or no missions loaded
	if (num_PR == 0 && num_ER == 0 || num_EM == 0 && num_PM == 0) {
		UI_ptr->OutputStr("No Rovers/No Events were loaded...Ending Simulation.");
		return false;
	}
	return true;
}

void MarsStation::Save()
{
	if (Day == 1) 
	{
		//getting the file name from the user
		UI_ptr->OutputStr("Enter the OUTPUT file name (without the .txt extension) ");
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
}

void MarsStation::OutputStatistics()
{
	*DestinationFile << "������������������" << endl << "������������������" << endl;
	//output the statistics
	*DestinationFile << "Missions: " << num_EM + num_PM << "[P: " << num_PM << " E: " << num_EM << "]" << endl;
	*DestinationFile << "Rovers: " << num_ER + num_PR << "[P: " << num_PR << " E: " << num_ER << "]" << endl;
	*DestinationFile << "Average Wait= " << Total_Wait / (num_EM + num_PM) << "\t" << "Average Exec= " << Total_InExec / (num_EM + num_PM) << endl;
	//closing the file
	DestinationFile->close();
	delete DestinationFile;
}

void MarsStation::Save_CompleteM()
{
	//Dequeue- Save - Delete
	while (!Completed_M.IsEmpty()) {
		Mission* CompletedM;
		Completed_M.dequeue(CompletedM);
		*DestinationFile << CompletedM->GetCD() << "\t" << CompletedM->GetID() << "\t" << CompletedM->GetFD() << "\t" << CompletedM->GetWD() << "\t" << CompletedM->GetED() << endl;
		if (CompletedM->GetTypeOfMission() == Emergency) {
			CompletedE_ID.enqueue(CompletedM->GetID());
			Count_Completed_EM++;
		}
		else {
			CompletedP_ID.enqueue(CompletedM->GetID());
			Count_Completed_PM++;
		}
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

void MarsStation::Assign()
{
	Mission* availableM;
	Rover* availableR;
	//assigning Emergency missions first
	while (!Waiting_EM.IsEmpty() && (!Av_ER.IsEmpty() || !Av_PR.IsEmpty() || !Maintenance_ER.IsEmpty() || !Maintenance_PR.IsEmpty())  ) {
		Waiting_EM.dequeueFront(availableM);
		if (!Av_ER.IsEmpty()) {
			Av_ER.dequeue(availableR);
		}
		else if(!Av_PR.IsEmpty()){
			Av_PR.dequeue(availableR);
		}
		else if (!Maintenance_ER.IsEmpty())
		{
			Maintenance_ER.dequeue(availableR);
			availableR->HalfSpeed();
		}
		else
		{
			Maintenance_PR.dequeue(availableR);
			availableR->HalfSpeed();
		}


		availableM->SetWaiting(Day - availableM->GetFD());
		availableR->Assign(availableM);
		availableM->Assign(availableR);
		InExec_rov.enqueue(availableR, availableM->GetCD());
	}

	//assigning Polar missions
	while (!Waiting_PM.IsEmpty() && (!Av_PR.IsEmpty()|| !Maintenance_PR.IsEmpty())) {

		Waiting_PM.dequeue(availableM);
		if (!Av_PR.IsEmpty())
		{
			Av_PR.dequeue(availableR);
		}
		else
		{
			Maintenance_PR.dequeue(availableR);
			availableR->ResetMissions();
			availableR->HalfSpeed();
		}

		availableM->SetWaiting(Day - availableM->GetFD());
		availableR->Assign(availableM);
		availableM->Assign(availableR);
		InExec_rov.enqueue(availableR, availableM->GetCD());
	}
	return;
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
	while (Waiting_EM.dequeueFront(t))//count number of Emergency mission in waiting list 
	{
		copydata.enqueue(t,t->GetPriority());
		counter_waiting_EM++;
	}

	int* arr_EM = new int[counter_waiting_EM];//create array for Emergency Mission'S IDS 
	int i = 0;
	while (copydata.dequeueFront(t))// put Emergency Mission'S IDS in arr_em
	{
		Waiting_EM.enqueue(t,t->GetPriority());
		arr_EM[i] = (t->GetID());
		i++;
	}
	int counter_waiting_PM = 0;
	Queue<Mission*> copydata_;
	while (Waiting_PM.dequeue(t))//count number of polar mission in waiting list
	{
		copydata_.enqueue(t);
		counter_waiting_PM++;
	}
	int TotalNumberOfWaitingMission = counter_waiting_PM + counter_waiting_EM;
	int* arr_PM = new int[counter_waiting_PM];//create array for Polar Mission'S IDS 
	i = 0;
	while (copydata_.dequeue(t))//put Emergency Mission'S IDS in arr_pm
	{
		Waiting_PM.enqueue(t);
		arr_PM[i] = (t->GetID());
		i++;
	}
	Rover* M;
	PriorityQueue<Rover*> copydata2;
	int counter_EMInEXEC = 0;
	int counter_PMInEXEC = 0;
	while (InExec_rov.dequeueFront(M))
	{
		if (M->GetMission()->GetTypeOfMission() == Emergency)//count number of Emergence mission in execlist 
		{
			counter_EMInEXEC++;
		}
		else//count number of polar mission in execlist 
		{
			counter_PMInEXEC++;

		}
		copydata2.enqueue(M,M->GetMission()->GetCD());
	}
	int* arr_InExec_EM_rover = new int[counter_EMInEXEC * 2];//create array for IDS of Emergency missions and IDS of rovers which assigned to in exclist
	int* arr_InExec_PM_rover = new int[counter_PMInEXEC * 2];//create array for IDS of polar missions in exclist and IDS of rovers which assigned to in exclist
	int j = 0;
	int f = 0;
	while (copydata2.dequeueFront(M))
	{
		if (M->GetMission()->GetTypeOfMission() == Emergency)//put IDS of Emergency missions and IDS of rovers which assigned to in exclist
		{
			arr_InExec_EM_rover[j] = M->GetMission()->GetID();
			j++;
			arr_InExec_EM_rover[j] = M->GetID();
			j++;
		}
		else
		{
			arr_InExec_PM_rover[f] = M->GetMission()->GetID();//put IDS of polar missions in exclist and IDS of rovers which assigned to in exclist
			f++;
			arr_InExec_PM_rover[f] = M->GetID();
			f++;
		}
		InExec_rov.enqueue(M, M->GetMission()->GetCD());
	}
	j = 0;
	Queue<Rover*>k_;
	int counter_Av_ER=0;
	while (Av_ER.dequeue(M))//count the number of available emergency rovers 
	{
		counter_Av_ER++;
		k_.enqueue(M);
	}
	int* arr_Av_ER = new int[counter_Av_ER];//create an array for available Emergency rovers 
	while (k_.dequeue(M))//put IDS for available Emergency rovers
	{
		arr_Av_ER[j] = M->GetID();
		j++;
		Av_ER.enqueue(M);
	}
	j = 0;
	int counter_Av_PR = 0;
	while (Av_PR.dequeue(M))//count the number of available polar rovers 
	{
		counter_Av_PR++;
		k_.enqueue(M);
	}
	int* arr_Av_PR = new int[counter_Av_PR];//create an array for available polar rovers 
	while (k_.dequeue(M))//put IDS for available polar rovers
	{
		arr_Av_PR[j] = M->GetID();
		j++;
		Av_PR.enqueue(M);
	}
	j = 0;
	int counter_InCheckUp_PR = 0;
	while (InCheckUp_PR.dequeue(M))//count the number of  polar rovers which it in check up time 
	{
		counter_InCheckUp_PR++;
		k_.enqueue(M);
	}
	Queue<Rover*>l_;
	while (Maintenance_PR.dequeue(M)) //count of polar rovers in extra maintenance
	{
		counter_InCheckUp_PR++;
		l_.enqueue(M);
	}
	int* arr_InCheckUp_PR = new int[counter_InCheckUp_PR];//create an array for IDs of polar rovers which is in check up time  
	while (k_.dequeue(M))//put IDs of polar rovers which is in check up time in arr_InCheckUp_PR
	{
		arr_InCheckUp_PR[j] = M->GetID();
		InCheckUp_PR.enqueue(M);
		j++;
	}
	while (l_.dequeue(M)) //adding the IDs of polar rovers that are in extra maintenance
	{
		arr_InCheckUp_PR[j] = M->GetID();
		Maintenance_PR.enqueue(M);
		j++;
	}
	j = 0;
	int counter_InCheckUp_ER = 0;
	while (InCheckUp_ER.dequeue(M))//count the number of Emergency rovers which is in check up time 
	{
		counter_InCheckUp_ER++;
		k_.enqueue(M);
	}
	while (Maintenance_ER.dequeue(M)) //count of emergency rovers in extra maintenance
	{
		counter_InCheckUp_ER++;
		l_.enqueue(M);
	}
	int* arr_InCheckUp_ER = new int[counter_InCheckUp_ER];;//create an array for IDs of Emergency rovers which is in check up time 
	while (k_.dequeue(M))//put IDs of emergency rovers which is in check up time in arr_InCheckUp_ER
	{
		arr_InCheckUp_ER[j] = M->GetID();
		InCheckUp_ER.enqueue(M);
		j++;
	}
	while (l_.dequeue(M)) //adding the IDs of emergency rovers that are in extra maintenance
	{
		arr_InCheckUp_ER[j] = M->GetID();
		Maintenance_ER.enqueue(M);
		j++;
	}
	UI_ptr->PrintOutput(Day, TotalNumberOfWaitingMission, counter_waiting_EM, arr_EM, counter_waiting_PM, arr_PM, counter_EMInEXEC, arr_InExec_EM_rover, counter_PMInEXEC, arr_InExec_PM_rover, counter_Av_ER, arr_Av_ER, counter_Av_PR, arr_Av_PR, counter_InCheckUp_ER, arr_InCheckUp_ER, counter_InCheckUp_PR, arr_InCheckUp_PR, Count_Completed_EM, CompletedE_ID, Count_Completed_PM, CompletedP_ID);
	
	delete[]arr_Av_ER; delete[] arr_Av_PR; delete[] arr_EM; delete[] arr_InCheckUp_ER; delete[] arr_InCheckUp_PR;
	delete[]arr_InExec_EM_rover; delete[] arr_InExec_PM_rover; delete[] arr_PM; 
}

void MarsStation::IncrementDay()
{
	Day++;
}


void MarsStation::ReadMode()
{
	mode = UI_ptr->ReadMode();
}

MarsStation::~MarsStation()
{
	delete UI_ptr;
}

bool MarsStation::End_Sim() 
{
	if (Events.IsEmpty() && Waiting_EM.IsEmpty() && Waiting_PM.IsEmpty() && InExec_rov.IsEmpty() && InCheckUp_ER.IsEmpty() && InCheckUp_PR.IsEmpty()) 
	{
		return true;
	}
	else 
	{
		return false;
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
			InExec_rov.dequeueBack(m_rover); // Getting Finished mission
			if (!CheckMissionFail(m_rover))  //checking on mission failure possibility 
			{
				Completed_M.enqueue(m_rover->GetMission()); // Putting it in completed missions queue

				if (m_rover->GetMission()->GetED() >= 30) // checking possibility of Extra Maintenance
				{
					if (m_rover->GetType() == Emergency_Rover)
					{
						Maintenance_ER.enqueue(m_rover);
						m_rover->SetDaysOver(Day);
					}
					else
					{
						Maintenance_PR.enqueue(m_rover);
						m_rover->SetDaysOver(Day);
					}
				}
				else
				{
					m_rover->IncrementMissions();
					MoveRover(m_rover);
				}

			}


		}
		else
		{
			break;
		}
	}
}

void MarsStation::MoveRover (Rover * rov)
{
	//moving rovers to checkup
	if (rov->MoveToCheckup()) {
		if (rov->GetType() == Emergency_Rover) {
			InCheckUp_ER.enqueue(rov);
			rov->SetDaysOver(Day);
		}
		else {
			InCheckUp_PR.enqueue(rov);
			rov->SetDaysOver(Day);
		}

		return;
	}

	//returning rovers to the available list
	if (rov->GetType() == Emergency_Rover) {
		Av_ER.enqueue(rov);
	}
	else {
		Av_PR.enqueue(rov);
	}
	return;
}

bool MarsStation::CheckMissionFail(Rover* rov)
{
	if (rov->EngineFail()) {

		//moving rover to checkup
		if (rov->GetType() == Emergency_Rover) {
			InCheckUp_ER.enqueue(rov);
			rov->SetDaysOver(Day);
		}
		else {
			InCheckUp_PR.enqueue(rov);
			rov->SetDaysOver(Day);
		}


		//reformulating mission
		Mission* mission = rov->GetMission();
		mission->Reformulate(Day);
		if (mission->GetTypeOfMission() == Emergency) 
		{
			Waiting_EM.enqueue(mission,mission->GetPriority());
		}
		else
		{
			Waiting_PM.enqueue(mission);
		}
		return true;
	}
	return false;
}

void MarsStation::MoveCheckUpRovers()
{
	// Checking on Rovers in Checkup-Queues.

	Rover* m_rover;

	while (InCheckUp_ER.peek(m_rover)) // Getting Emergency rover soon to be finished / finished.
	{
		if (m_rover->GetDaysOver() == Day) // If rover has finished checkup
		{
			InCheckUp_ER.dequeue(m_rover); // remove from checkup queue
			m_rover->ResetMissions();
			Av_ER.enqueue(m_rover); // Add to available queue.
		}
		else
		{
			break;
		}
	}

	while (InCheckUp_PR.peek(m_rover)) // Getting Polar rover soon to be finished / finished.
	{
		if (m_rover->GetDaysOver() == Day) // If rover has finished checkup
		{
			InCheckUp_PR.dequeue(m_rover); // remove from checkup queue
			m_rover->ResetMissions();
			Av_PR.enqueue(m_rover); // Add to available queue.
		}
		else
		{
			break;
		}
	}

	while (Maintenance_ER.peek(m_rover))
	{
		if (m_rover->GetDaysOver() == Day)
		{
			Maintenance_ER.dequeue(m_rover);
			m_rover->ResetMissions();
			Av_ER.enqueue(m_rover);
		}
		else
		{
			break;
		}
	}

	while (Maintenance_PR.peek(m_rover))
	{
		if (m_rover->GetDaysOver() == Day)
		{
			Maintenance_PR.dequeue(m_rover);
			m_rover->ResetMissions();
			Av_PR.enqueue(m_rover);
		}
		else
		{
			break;
		}
	}
}



void MarsStation::ExecuteEvents()
{
	Event* m_event;
	while (Events.peek(m_event) && m_event->GetDay() == Day) 
	{
		Events.dequeue(m_event);
		m_event->Execute();  // Create the mission and add it to waiting queue.
	}
}

void MarsStation::Simulate()
{

	ExecuteEvents();
	Assign();
	// Moving on to the next day


	// Moving Functions
	MoveCompMissions();
	MoveCheckUpRovers();

	Save();


	if (mode == 3 && End_Sim())
	{
		PrintOutput();
	}
	else if(mode ==1 || mode ==2)
	{
		PrintOutput();
	}


	if (End_Sim()) // for printing statistics
	{
		OutputStatistics();
	}

	IncrementDay();

}
