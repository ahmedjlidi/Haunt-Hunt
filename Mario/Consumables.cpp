#include "stdafx.h"
#include "Consumables.h"


Consumables::Consumables(unsigned quantity) : Item()
{
	this->quantity = quantity;
}

unsigned int& Consumables::getQuantity()
{
	return this->quantity;
}

const bool Consumables::isEmpty() const
{
	return this->quantity <= 0;
}


void Consumables::Use(const bool decrement)
{
	if (decrement)
	{
		if (this->quantity > 0)
		{
			--this->quantity;
		}
	}
}


void Consumables::increase(const int* value)
{
	if (value)
		this->quantity += *value;
	else
		++this->quantity;
}