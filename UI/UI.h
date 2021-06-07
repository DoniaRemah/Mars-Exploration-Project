#pragma once
#include "..\Defs.h"
using namespace std;
#include<string>
#include "..\Data Structures\Queue.h"
class UI
{

private:

	int m_mode;

public:

	UI(); // defualt constructor (Empty)

	int ReadMode();  // Reads mode from user and stores it in m_mode.

	void PrintOutput(int day, int TotalNumberOfWaitingMission, int counter_waiting_EM, int *arr_EM, int counter_waiting_PM, int *arr_PM, int counter_EMInEXEC, int *arr_InExec_EM_rover, int counter_PMInEXEC, int *arr_InExec_PM_rover, int counter_Av_ER,int * arr_Av_ER, int counter_Av_PR, int *arr_Av_PR, int counter_InCheckUp_ER, int *arr_InCheckUp_ER, int counter_InCheckUp_PR, int *arr_InCheckUp_PR, int counter_Completed_EM, Queue<int>& Completed_EM,int  counter_Completed_PM, Queue<int>& Completed_PM); // prints to console output according to the chosen mode.

	void PrintStatistics();

	void OutputStr(string); //prints a string to the user interface


	string getInput(); //takes a string from the user

};