#pragma once
#pragma once

class Event
{
protected:
	int Day;
	int MissionID;

public:

	Event(int d, int id); // Constructor
	virtual void Execute();
	~Event(); // Destructor
};
