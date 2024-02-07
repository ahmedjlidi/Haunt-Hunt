#pragma once
class AttributeComponent
{


public:
	//leveling
	unsigned level;
	unsigned Xp;
	unsigned XpNext;
	unsigned attributePoints;
	unsigned vitality;
	unsigned agility;

	//attributes
	float Att_strength;
	float Att_speed;
	float Att_defense;
	
	


	//stats
	int Hp, HpMax;
	int Damage, MaxDamage, MinDamage;


	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	
	void updateStats(const bool reset);
	void GainExp(const unsigned exp);
	void debug();
	void updateLevel();
	void update();
};

