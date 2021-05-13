#pragma once
#include "Events.h"

class FormulationEvent: public Events
{


public:

	FormulationEvent(int d, int id);

	virtual void Execute();

	~FormulationEvent();
};
