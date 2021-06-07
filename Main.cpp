#include <iostream>
#include "MarsStation/MarsStation.h"
using namespace std;


int main()
{
	srand(time(NULL)); //seed for the random number generator (mission failure)

	MarsStation* MarsStration_Obj = new MarsStation;
	MarsStration_Obj->Load();
	MarsStration_Obj->ReadMode();


	while (!MarsStration_Obj->End_Sim())
	{
		MarsStration_Obj->Simulate();
	}

	delete MarsStration_Obj;

	return 0;
}