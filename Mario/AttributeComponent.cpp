#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this-> level = level;
	this->Xp = 0;
	this->XpNext = (static_cast<double>(50) / 3) * (pow(this->level, 3)) - 6 * (pow(this->level, 2) + (this->level * 17) - 12);
	this->attributePoints = 2;
	this->vitality = 1;
	this->agility = 1;

	this->Att_strength = 1.f;
	this->Att_speed = 1.f;
	this->Att_defense= 1.f;

	this->updateLevel();
	this->updateStats(true);
	
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::updateStats(const bool reset)
{
	this->HpMax = this->vitality * 9 + this->vitality + this->Att_strength;
	this->MaxDamage = this->Att_strength * 2 + this->Att_strength / 2;
	this->MinDamage = this->Att_strength * 2 + this->Att_strength / 4;
	this->Att_defense = this->agility * 2 + this->agility / static_cast<float>(3);
	if(reset)
		this->Hp = HpMax;
}

void AttributeComponent::GainExp(const unsigned exp)
{
	this->Xp += exp;
	this->updateLevel();
}

void AttributeComponent::debug()
{
	cout << "level: " << this->level<<'\n';
	cout << "XP: " << this->Xp<<"\n";
	cout << "attributepts: " << this->attributePoints << "\n";
	
}

void AttributeComponent::updateLevel()
{
	while (this->Xp >= XpNext)
	{
		this->level++;
		this->Xp -= this->XpNext;
		this->XpNext = (static_cast<double>(50) / 3) * (pow(this->level, 3)) - 6 * (pow(this->level, 2) + (this->level * 17) - 12);
		this->attributePoints++;
		
	}
}

void AttributeComponent::update()
{
	this->updateLevel();

}


