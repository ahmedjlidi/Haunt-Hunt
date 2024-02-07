#include "stdafx.h"
#include "Item.h"




Item::Item(Texture* texture, Sprite* sprite, const bool isEquipped)
{
	if (texture && sprite)
	{
		this->animationComponent = new AnimationComponent(*sprite, *texture);
	}
    this->isEquipped = isEquipped;

	
}



void Item::addAnimation(const string name, float speed, unsigned start_x, unsigned start_y, unsigned end_x, unsigned end_y, unsigned width, unsigned height)
{
	this->animationComponent->AddAnimation(name, speed, start_x, start_y, end_x, end_y, width, height);
}

void Item::reload(unsigned int& magazineQuantity)
{

}

const int Item::getMagazineSize() const
{
	return 0;
}

void Item::reduceAmmo(const int* amount)
{
}



const float Item::getDamage() const
{
	return 0.0f;
}

void Item::Use(const bool decrement)
{

}

void Item::increase(const int* value)
{

}

unsigned int& Item::getQuantity()
{
	return this->quantity;
}




const bool Item::isEmpty() const
{
	return false;
}

void Item::setDamage(const float damage)
{
}

void Item::renderShooting(RenderTarget& target)
{
}


void Item::updateUseAnimation(const float& dt, unsigned int Status, const Vector2f& GunPos)
{

}

void Item::updateMovementAnimation(const short MovementStatus, const float& dt)
{

}

