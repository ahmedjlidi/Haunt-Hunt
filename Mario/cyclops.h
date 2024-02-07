#pragma once
#include "Enemy.h"



class Enemy;

class cyclops : public Enemy
{
private:


public:

	void InitVariables()override;
	void InitComponent(Texture& texture_sheet)override;

	cyclops(float x, float y,float speed, Texture& texture_sheet, const bool patrol,
		const Vector2f PatrolPositionEnd, const Vector2f PatrolPositionStart, float hp,
		Vector2f interestRange, float damage, short type, const map<string, Sound>& sounds, const FloatRect& update_range);
	 
};

