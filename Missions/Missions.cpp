#include "Missions.h"

Mission::Mission(MissionType T, int id, int FD, int MD, int sig, int TL)
{
	Type = T;
	ID = id;
	FormulationDay = FD;
	MissionDuration = MD;
	Significance = sig;
	TLocation = TL;
	m_rover = nullptr;
	WaitingDays = 0;
}
void Mission::Assign(Rover* R)
{
	m_rover = R;
	CalculateED();
	CalculateCD();
	DaysToBeOver = ExecutionDays;
}

int Mission::GetID() 
{
	return ID;
}

int Mission::GetFD() 
{
	return FormulationDay;
}
int Mission::GetWD() 
{
	return WaitingDays;
}
int Mission::GetED() 
{
	return ExecutionDays;
}

void Mission::CalculateED() 
{
	ExecutionDays = ((TLocation * 2) / (m_rover->GetSpeed() * 25)) + MissionDuration;
}

void Mission::CalculateCD() 
{
	CompletionDay = FormulationDay + WaitingDays + ExecutionDays;

}

void Mission::CalculatePriority()  //Higher number -> Higher priority
{
	//First: Assigning a weight for each criteria 
	int FD_W = -4; //Weight is negative because we want the mission with the less formulation day (Formulated first) to have higher priority
	int Location_W = -1; //The closer to the base station, the higher priority
	int MD_W = -1; //The less the duration, the higher priority (logic: in order to finish more quickly)
	int Significance_W = 5; //The higher the significance, the higher the priority
	float Total_W = 4 + 1 + 1 + 5; //Taking the modulus of the weights to divide by them

	// Second: Calculating the priority using the following priority equation (Like GPA):
     priority = ((FormulationDay * FD_W) + (TLocation * Location_W) + (MissionDuration * MD_W) + (Significance * Significance_W)) / (Total_W);
}


void Mission::IncrementWD()
{
	WaitingDays++;
}

void Mission::DecrementEX()
{
	DaysToBeOver--;
}

float Mission::GetPriority()
{
	return priority;
}
MissionType Mission::GetTypeOfMission()
{
	return Type;
}

int Mission::GetCD()
{
	return CompletionDay;
}
void Mission::Reformulate(int day)
{
	FormulationDay = day;
	WaitingDays = 0;
}
Mission::~Mission()
{

}

