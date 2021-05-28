#pragma once
#include "..\Defs.h"
using namespace std;
#include<string>

class UI
{

private:

	int mode;

public:

	UI(); // defualt constructor (Empty)

	void ReadMode();  // Reads mode from user and stores it in m_mode.

	void PrintOutput(); // prints to console output according to the chosen mode.

	void OutputStr(string); //prints a string to the user interface

	string getInput(); //takes a string from the user

};