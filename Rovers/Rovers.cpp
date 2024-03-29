#include "Rovers.h"
#include<iostream>
#include<math.h>
using namespace std;

int Rover::ID = 1; //Initializing the static data member ID

Rover::Rover(RoverType T, int sp, int ChD, int MM) // Constructor (Initializing input data)
{
	Type = T;
	speed = sp;
	CheckUp_Duration = ChD;
	MaxMissions = MM;
	m_mission = nullptr;
	SetID(ID);
	ID++;
}


void Rover::Assign(Mission* M) 
{
	m_mission = M;
}


int Rover::GetSpeed() 
{
	return speed;
}

Mission* Rover::GetMission()
{
	return m_mission;
}

void Rover::ResetMissions() 
{
	Num_Of_ExecMissions = 0;
}

void Rover::IncrementMissions() 
{
	Num_Of_ExecMissions++;
}





int Rover::GetNumOfMissions() 
{
	return Num_Of_ExecMissions;
}
void Rover:: SetID(int I_D)
{
	ThisID=I_D;
}
int Rover::GetID()
{
	return ThisID;
}
void Rover::SetDaysOver(int current_day)
{
	DaysChOver = CheckUp_Duration + current_day ;
}

int Rover::GetDaysOver()
{
	return DaysChOver;
}

RoverType Rover::GetType()
{
	return Type;
}

bool Rover::MoveToCheckup()
{
	if (Num_Of_ExecMissions == MaxMissions) {
		return true;
	}
	return false;
}

bool Rover::EngineFail()
{
	//returns a random number from 1 to 100
	int random = rand() % 101;
	//5% fail
	if (random >= 1 && random <= 5){
		return true;
	}
	return false;
}

void Rover::HalfSpeed()
{
	speed = (speed + 1) / 2;
}

Rover::~Rover() // Destructor
{

}
