#include "UI.h"
using namespace std;
#include<iostream>
#include<string>
#include"../Defs.h"
#include <Windows.h>

void UI::OutputStr(string str)
{
	cout << str << endl;

}

string UI::getInput()
{
	string str;
	//using getline to consider any spaces in line name
	getline(cin, str);
	return str;
}



UI::UI() 
{
	m_mode = 0;
}

int UI::ReadMode() 
{
	int mode_ = -1;
	cout << "Choose the mode: " << endl;
	cout << "------------------------------" << endl;
	cout << "1: Interactive Mode " << endl;
	cout << "2: Step by Step Mode " << endl;
	cout << "3: Silent Mode " << endl;
	cin >> mode_;
	cin.get(); //to ignore the "enter" key press and not save it in the buffer
	while (true)
	{
		if (mode_ == 1 || mode_ == 2 || mode_ == 3)
		{
			m_mode = mode_;
			break;
		}
		else
		{
				cout << "Wrong number, please enter again: ";
				cin >> mode_;
				cin.get();
		}
	} 

	return m_mode;
}

void UI::PrintOutput(int day, int TotalNumberOfWaitingMission, int counter_waiting_EM, int* arr_EM, int counter_waiting_PM, int* arr_PM, int counter_EMInEXEC, int* arr_InExec_EM_rover, int counter_PMInEXEC, int* arr_InExec_PM_rover, int counter_Av_ER, int* arr_Av_ER, int counter_Av_PR, int* arr_Av_PR, int counter_InCheckUp_ER, int* arr_InCheckUp_ER, int counter_InCheckUp_PR, int* arr_InCheckUp_PR, int counter_Completed_EM, Queue<int>& Completed_EM,int  counter_Completed_PM, Queue<int>& Completed_PM)
{
	if (m_mode ==1 || m_mode ==2)
	{
		cout << "Current day:" << day << endl;
		cout << TotalNumberOfWaitingMission << " " << "Waiting Missions: [" ;
		for (int i = 0; i < counter_waiting_EM; i++)
		{
			cout << arr_EM[i];
			if (i != counter_waiting_EM - 1)
			{
				cout << ",";
			}
		}
		cout << "] ";
		cout << "(";
		for (int i = 0; i < counter_waiting_PM; i++)
		{
			cout << arr_PM[i];
			if (i != counter_waiting_PM - 1)
			{
				cout << ",";
			}
		}
		cout << ")" << endl;
		cout << "------------------------------------------" << endl;
		cout << (counter_EMInEXEC + counter_PMInEXEC) << "  In-Execution Missions/Rovers: [";
		for (int i = 0; i < (counter_EMInEXEC*2); i = i + 2)
		{
			cout << arr_InExec_EM_rover[i] << "/" << arr_InExec_EM_rover[i + 1];
			if (i != (counter_EMInEXEC * 2) - 2)
			{
				cout << ",";
			}
		}
		cout << "] (";
		for (int i = 0; i < (counter_PMInEXEC*2); i = i + 2)
		{
			cout << arr_InExec_PM_rover[i] << "/" << arr_InExec_PM_rover[i + 1];
			if (i != (counter_PMInEXEC*2) - 2)
			{
				cout << ",";
			}
		}
		cout << ")" << endl;
		cout << "------------------------------------------" << endl;
		cout << (counter_Av_ER + counter_Av_PR)<<" "<< "Available Rovers: [";
		for (int i = 0; i < counter_Av_ER; i = i++)
		{
			cout << arr_Av_ER[i];
			if (i != counter_Av_ER - 1)
			{
				cout << ",";
			}
		}
		cout << "] (";
		for (int i = 0; i < counter_Av_PR; i = i++)
		{
			cout << arr_Av_PR[i];
			if (i != counter_Av_PR - 1)
			{
				cout << ",";
			}
		}
		cout << ")" << endl;
		cout << "------------------------------------------" << endl;
		cout << (counter_InCheckUp_ER + counter_InCheckUp_PR) << "  In-Checkup Rovers: [";
		for (int i = 0; i < counter_InCheckUp_ER; i = i++)
		{
			cout << arr_InCheckUp_ER[i];
			if (i != counter_InCheckUp_ER - 1)
			{
				cout << ",";
			}
		}
		cout << "] (";
		for (int i = 0; i < counter_InCheckUp_PR; i = i++)
		{
			cout << arr_InCheckUp_PR[i];
			if (i != counter_InCheckUp_PR - 1)
			{
				cout << ",";
			}
		}
		cout << ")" << endl;
		cout << "------------------------------------------" << endl;
		cout << (counter_Completed_PM + counter_Completed_EM) << " Completed Missions: [";

		Queue<int> copy_data;
		int x;
		int counter = 1;
		while (!Completed_EM.IsEmpty()) // Printing ids of finished emergency missions.
		{
			Completed_EM.dequeue(x);
			cout << x;
			if (counter != counter_Completed_EM )
			{
				cout << ",";
			}
			counter++;
			copy_data.enqueue(x);
		}

		while (!copy_data.IsEmpty()) // Getting back ids into queue
		{
			copy_data.dequeue(x);
			Completed_EM.enqueue(x);
		}

		cout << "] (";
		counter = 1;

		while (!Completed_PM.IsEmpty()) // Printing ids of finished polar missions.
		{
			Completed_PM.dequeue(x);
			cout << x;
			if (counter != counter_Completed_PM)
			{
				cout << ",";
			}
			counter++;
			copy_data.enqueue(x);
		}

		while (!copy_data.IsEmpty()) // Getting back ids into queue
		{
			copy_data.dequeue(x);
			Completed_PM.enqueue(x);
		}


		cout << ")";

		cout << endl <<"--------------------------------------------------" << endl;
		cout << endl;
		if (m_mode == 1)
		{
			cout << "Press Enter to Continue...";
			cin.get();
			cout << endl;
		}
		else if (m_mode == 2)
		{
			Sleep(2000);
		}

	}
	if (m_mode == 3)
	{
		cout << "Silent Mode" << endl;
		cout << "Simulation Starts..." << endl;
		cout << "Simulation ends,output file created" << endl;
	}
}


