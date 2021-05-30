#include <iostream>
#include "MarsStation/MarsStation.h"
using namespace std;

int main()
{

	MarsStation MarsStration_Obj;
	MarsStration_Obj.Load();
	MarsStration_Obj.ReadMode();


	while (!MarsStration_Obj.End_Sim())
	{
		MarsStration_Obj.ExecuteEvents();
		MarsStration_Obj.Assign();

		MarsStration_Obj.PrintOutput(); // Printing to console 

		MarsStration_Obj.Save(); // Saving to output File
		MarsStration_Obj.Refresh(); // Moving to Next Day

		if (MarsStration_Obj.End_Sim()) // for printing statistics
		{
			break;
		}

	}

	return 0;
}