#include <iostream>
#include "MarsStation/MarsStation.h"
using namespace std;

int main()
{

	MarsStation MarsStration_Obj;
	MarsStration_Obj.Load();
	//MarsStration_Obj.ReadMode();


	//while (!MarsStration_Obj.End_Sim())
	//{
	//	MarsStration_Obj.ExecuteEvents();
	//	MarsStration_Obj.Assign();
	//	if (MarsStration_Obj.End_Sim()) 
	//	{

	//	}

	//}
	return 0;
}