#pragma once
#pragma once

class Events
{
protected:
	int Day;
	int MissionID;

public:

	Events(int d, int id); // Constructor
	virtual void Execute() = 0;
};
