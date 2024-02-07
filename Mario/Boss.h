#pragma once
#include "Enemy.h"
class Boss : public Enemy
{
private:
	void InitVariables()override;
	void InitComponent(Texture& texture_sheet)override;
public:
	Boss(float x, float y, float speed, Texture& texture_sheet, const bool patrol,
		const Vector2f PatrolPositionEnd, const Vector2f PatrolPositionStart, float hp,
		Vector2f interestRange, float damage, short type, const map<string, Sound>& sounds, const FloatRect& update_range);
};
