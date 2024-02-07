#include "stdafx.h"
#include "ghost.h"

void ghost::InitVariables()
{
}

void ghost::InitComponent(Texture& texture_sheet)
{
	//movement component
	//animation component
	this->createAnimationComponent(texture_sheet);
	

	this->animationcomponent->AddAnimation("IDLE", 8.f, 0, 1, 0, 1, 64, 128);
	this->animationcomponent->AddAnimation("WALK_RIGHT", 8.f, 10, 1, 14, 1, 128, 128);
	this->animationcomponent->AddAnimation("WALK_LEFT", 8.f, 0, 1, 4, 1, 128, 128);

	this->animationcomponent->AddAnimation("CHASE_RIGHT", 8.f, 5, 1, 9, 1, 128, 128);
	this->animationcomponent->AddAnimation("CHASE_LEFT", 8.f, 11, 0, 15, 0, 128, 128);
	this->animationcomponent->AddAnimation("ATTACK_LEFT", 8.f, 0, 0, 6, 0, 128, 128);

	this->animationcomponent->AddAnimation("DIE", 8.f, 7, 0, 10, 0, 128, 128);

	//hitbox component
	
	this->createHitBoxComponent(this->sprite, 100, 100, 80, 64);
	//attribute component
	this->createAttributeComponent(0);
	//inventory component
	this->createInventoryComponent();

}

ghost::ghost(float x, float y, float speed, Texture& texture_sheet, const bool patrol,
	const Vector2f PatrolPositionEnd, const Vector2f PatrolPositionStart, float hp,
	Vector2f interestRange, float damage, short type, const map<string, Sound>& sounds, const FloatRect& update_range)
	:Enemy(x, y, texture_sheet, patrol, PatrolPositionEnd, PatrolPositionStart, hp, interestRange, damage, type, sounds, update_range)
{
	this->InitVariables();
	this->SetSpawnPosition(x, y);
	this->createMovement(speed, speed * 5.f, speed * 3.5f);
	this->InitComponent(texture_sheet);
	this->textureSheet = texture_sheet;
}
