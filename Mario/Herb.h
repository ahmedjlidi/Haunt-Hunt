#pragma once
#include "Consumables.h"
class Herb : public Consumables
{
private:
	unsigned quantity;

public:
	Herb(unsigned quantity);
};

