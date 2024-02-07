#include "stdafx.h"
#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(Sprite &sprite, float offset_x, float offset_y, float width, float height)
	:sprite(sprite), offsetX(offset_x),offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x,
		this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(Vector2f(height, width));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(Color::Green);


	this->NextPosition.left = 0.f;
	this->NextPosition.top = 0.f;
	this->NextPosition.width = height;
	this->NextPosition.height = width;


}

bool HitBoxComponent::CheckInterset(const FloatRect &frect )
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

const Vector2f& HitBoxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const FloatRect HitBoxComponent::GlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const FloatRect& HitBoxComponent::getNextPosition(const Vector2f& velocity, const float &dt)
{
	this->NextPosition.left = this->hitbox.getPosition().x + velocity.x *dt;
	this->NextPosition.top = this->hitbox.getPosition().y + velocity.y *dt;

	return this->NextPosition;
}

void HitBoxComponent::setPosition(const Vector2f& Position)
{
	this->hitbox.setPosition(Position);
	this->sprite.setPosition(Position.x - offsetX, Position.y - offsetY);
}


void HitBoxComponent::update(const float& dt)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y+ offsetY);
}

void HitBoxComponent::render(RenderTarget* target)
{
	target->draw(this->hitbox);
}
