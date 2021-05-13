#pragma once
#include "Events.h"

class PromotionEvent : public Events
{


public:

	PromotionEvent(int d, int id);

	virtual void Execute();

	~PromotionEvent();
};