#include <iostream>
#include "MarsStation/MarsStation.h"
using namespace std;


int main()
{
	srand(time(NULL)); //seed for the random number generator (mission failure)

	MarsStation* MarsStration_Obj = new MarsStation;
	bool ValidFile=MarsStration_Obj->Load();

	if (!ValidFile) return 0; //if zero missions or zero rovers were loaded the simulation ends
	MarsStration_Obj->ReadMode();

	
	while (!MarsStration_Obj->End_Sim())
	{
		MarsStration_Obj->Simulate();
	}

	delete MarsStration_Obj;

	return 0;
}