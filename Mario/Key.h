#pragma once
#include "Consumables.h"

class Key : public Consumables
{
private:
	unsigned quantity;
public:
	Key(unsigned quantity);
};

