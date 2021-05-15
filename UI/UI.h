#pragma once
#include "..\Defs.h"

class UI
{

private:

	Mode m_mode;

public:

	UI(); // defualt constructor (Empty)

	void ReadMode();  // Reads mode from user and stores it in m_mode.

	void PrintOutput(); // prints to console output according to the chosen mode.

};