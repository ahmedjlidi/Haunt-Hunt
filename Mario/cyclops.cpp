#include "stdafx.h"
#include "cyclops.h"

void cyclops::InitComponent(Texture& texture_sheet)
{
	//movement component
	//animation component
	this->createAnimationComponent(texture_sheet);

	this->animationcomponent->AddAnimation("IDLE", 8.f, 7, 3, 7, 3, 64, 64);
	this->animationcomponent->AddAnimation("WALK_RIGHT", 8.f, 8, 0, 13, 0, 64, 64);
	this->animationcomponent->AddAnimation("WALK_LEFT", 8.f, 2, 0, 7, 0, 64, 64);

	this->animationcomponent->AddAnimation("CHASE_RIGHT", 8.f, 8, 1, 12, 1, 64, 64);
	this->animationcomponent->AddAnimation("CHASE_LEFT", 8.f, 2, 1, 7, 1, 64, 64);
	this->animationcomponent->AddAnimation("ATTACK_LEFT", 8.f, 0, 3, 7, 3, 64, 64);
	this->animationcomponent->AddAnimation("ATTACK_RIGHT", 8.f, 7, 3, 12, 3, 64, 64);

	this->animationcomponent->AddAnimation("DIE", 8.f, 4, 2, 6, 2, 64, 64);

	//hitbox component
	this->createHitBoxComponent(this->sprite, 25, 40, 80, 64);
	//attribute component
	this->createAttributeComponent(0);
	//inventory component
	this->createInventoryComponent();
}

void cyclops::InitVariables()
{

}


cyclops::cyclops(float x, float y, float speed, Texture& texture_sheet, const bool patrol,
	const Vector2f PatrolPositionEnd, const Vector2f PatrolPositionStart, float hp,
	Vector2f interestRange, float damage, short type, const map<string, Sound>& sounds, const FloatRect& update_range)
	:Enemy(x,y,texture_sheet,patrol, PatrolPositionEnd, PatrolPositionStart,hp,interestRange, damage,type, sounds, update_range)
		
{
    this->InitVariables();
    this->SetSpawnPosition(x, y);
    this->createMovement(speed, speed * 5.f, speed * 3.5f);
    this->InitComponent(texture_sheet);
    this->textureSheet = texture_sheet;

}










