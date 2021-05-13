#pragma once
#include "Events.h"
class CancellationEvent : public Events
{


public:

	CancellationEvent(int d, int id);

	virtual void Execute();

	~CancellationEvent();
};