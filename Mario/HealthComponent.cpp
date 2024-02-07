#include "stdafx.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent(const float hp, Vector2f size, Vector2f position)
	:hp(hp), size(size), position(position), MaxSize(size), MaxHp(hp)
{
	this->healthBar.setSize(size);
	this->healthBar.setPosition(position);
	this->healthBar.setFillColor(Color::Red);
	this->healthBar.setOutlineThickness(1.f);
	this->healthBar.setOutlineColor(Color::Black);

}

float& HealthComponent::getHp() 
{
	return this->hp;
}

void HealthComponent::restoreHp()
{
	this->hp = this->MaxHp;
	this->size = this->MaxSize;
	this->healthBar.setSize(Vector2f(this->size));
}



const bool HealthComponent::HP_is_0()const
{
	return this->hp <= 0.f;
}

void HealthComponent::updateHp(const float damage)
{
	
	this->damage = (static_cast<float>(this->MaxSize.x) / static_cast<float>(this->MaxHp)) * damage;
	

	
	this->size.x += this->damage;
	
	
	if (this->size.x <= 0)
		this->size.x = 0.f;
	
	this->healthBar.setSize(this->size);
	this->hp = damage  + this-> hp <= 0.f  ? 0.f : this->hp + damage;
}

void HealthComponent::render(RenderTarget& target, Vector2f* position)
{
	if (position)
	{
		this->healthBar.setPosition(*position);
	}
	target.draw(this->healthBar);
}
