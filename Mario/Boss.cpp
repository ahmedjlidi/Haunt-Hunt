#include "stdafx.h"
#include "Boss.h"

void Boss::InitVariables()
{
}

void Boss::InitComponent(Texture& texture_sheet)
{
	//movement component
	//animation component
	this->createAnimationComponent(texture_sheet);


	this->animationcomponent->AddAnimation("IDLE", 8.f, 0, 4, 5, 4, 240, 240);

	this->animationcomponent->AddAnimation("WALK_RIGHT", 8.f, 0, 0, 6, 0, 240, 240);
	this->animationcomponent->AddAnimation("WALK_LEFT", 8.f, 3, 5, 9, 3, 240, 240);

	this->animationcomponent->AddAnimation("CHASE_RIGHT", 8.f, 0, 0, 6, 0, 240, 240);
	this->animationcomponent->AddAnimation("CHASE_LEFT", 8.f, 3, 5, 9, 5, 240, 240);

	this->animationcomponent->AddAnimation("ATTACK_LEFT", 8.f, 0, 1, 9, 1, 240, 240);

	this->animationcomponent->AddAnimation("DIE", 10.f, 6, 8, 9, 8, 240, 240);

	//hitbox component

	this->createHitBoxComponent(this->sprite, 150.f, 100, 240, 240);
	//attribute component
	this->createAttributeComponent(0);
	//inventory component
	this->createInventoryComponent();
}

Boss::Boss(float x, float y, float speed, Texture& texture_sheet, const bool patrol,
	const Vector2f PatrolPositionEnd, const Vector2f PatrolPositionStart,
	float hp, Vector2f interestRange, float damage, short type,
	const map<string, Sound>& sounds, const FloatRect& update_range) :
	Enemy(x, y, texture_sheet, patrol, PatrolPositionEnd, PatrolPositionStart, hp, interestRange, damage, type, sounds, update_range)
{
	this->InitVariables();
	this->SetSpawnPosition(x, y);
	this->createMovement(speed, speed * 5.f, speed * 3.5f);
	this->InitComponent(texture_sheet);
	this->textureSheet = texture_sheet;
}