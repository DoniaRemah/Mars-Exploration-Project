#include <iostream>
#include "MarsStation/MarsStation.h"
using namespace std;


int main()
{
	srand(time(NULL)); //seed for the random number generator (mission failure)

	MarsStation MarsStration_Obj;
	MarsStration_Obj.Load();
	MarsStration_Obj.ReadMode();


	while (!MarsStration_Obj.End_Sim())
	{
		MarsStration_Obj.ExecuteEvents();
		MarsStration_Obj.Assign();

	
		MarsStration_Obj.Refresh(); // Moving to Next Day

		MarsStration_Obj.Save(); // Saving to output File
		MarsStration_Obj.PrintOutput(); // Printing to console 


		if (MarsStration_Obj.End_Sim()) // for printing statistics
		{
			MarsStration_Obj.OutputStatistics();
			break;
		}

		MarsStration_Obj.IncrementDay();

	}

	return 0;
}