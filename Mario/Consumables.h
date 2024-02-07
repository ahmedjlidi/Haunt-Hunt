#pragma once
#include "Item.h"
class Consumables : public Item
{
protected:
	unsigned quantity;

public:
	Consumables(unsigned quantity);
	virtual unsigned int&  getQuantity() ;
	virtual const bool isEmpty()const;
	virtual void Use(const bool decrement) override;
	virtual void increase(const int* value = nullptr) override;
};

