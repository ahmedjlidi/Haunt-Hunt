#include "stdafx.h"
#include "MoveMentComponent.h"





int MoveMentComponent::GetMovementStatus()
{
	if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		return IDLE;
	else if (this->velocity.x > 0.f)
		return MOVING_RIGHT;
	else if (this->velocity.x < 0.f)
		return MOVING_LEFT;
	else if (this->velocity.y > 0.f)
		return MOVING_DOWN;
	else 
		return MOVING_UP;

}

int MoveMentComponent::getShootingStatus(const Vector2f& PlayerPos, const Vector2f& MousePos)
{
	if (this->velocity.x == 0 && this->velocity.y == 0)
	{
		if (PlayerPos.x > MousePos.x && abs(MousePos.x - PlayerPos.x) > abs(MousePos.y - PlayerPos.y))
			return shooting::LEFT;
		else if(PlayerPos.x < MousePos.x &&  abs(MousePos.x - PlayerPos.x) > abs(MousePos.y - PlayerPos.y))
			return shooting::RIGHT;

		else if (PlayerPos.y > MousePos.y)
			return shooting::UP;
		else if(PlayerPos.y < MousePos.y)
			return shooting::DOWN;

	}
	else
		return -1;
}


const bool MoveMentComponent::IsIdle() const
{
	return this->velocity.x == 0.f && this->velocity.y ==0.f ? 1 : 0;
}

const float& MoveMentComponent::getMaxVelocity() const
{
	return this->MaxVelocity;
}

const Vector2f& MoveMentComponent::getVelocity() const
{
	return this->velocity;
}

MoveMentComponent::MoveMentComponent(Sprite &sprite, float MaxVelocity, float accelration,
	float deceleration)
	:sprite(sprite),MaxVelocity(MaxVelocity), accelration(accelration), deceleration(deceleration)
{

}

void MoveMentComponent::stopVelocity(const short stop_veolcity)
{
	if (stop_veolcity == StopVelocity::STOP_VELOCITY)
	{
		this->velocity.x = 0.f;
		this->velocity.y = 0.f;

	}
	else if (stop_veolcity == StopVelocity::STOP_VELOCITY_X)
	{
		this->velocity.x = 0.f;

	}
	else if (stop_veolcity == StopVelocity::STOP_VELOCITY_Y)
	{
		this->velocity.y = 0.f;

	}


}

void MoveMentComponent::slowVelocity(const float offset)
{
	this->velocity.x *= offset;
	this->velocity.y *= offset;

}

void MoveMentComponent::move(const float dir_x, const float dir_y,const float &dt)
{
	this->velocity.x += this->accelration * dir_x * dt;
	this->velocity.y += this->accelration * dir_y * dt;
	
	
}

void MoveMentComponent::update(const float& dt)
{
	/*
	Decelerates the sprite and controls the maximum velocity.
	Moves the sprite.
	*/

	if (this->velocity.x > 0.f) //Check for positive x
	{
		//Max velocity check
		if (this->velocity.x > this->MaxVelocity)
			this->velocity.x = this->MaxVelocity;

		//Deceleration
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if(this->velocity.x < 0.f) //Check for negative x
	{
		//Max velocity check
		if (this->velocity.x < -this->MaxVelocity)
			this->velocity.x = -this->MaxVelocity;

		//Deceleration
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	
	if (this->velocity.y > 0.f) //Check for positive y
	{
		//Max velocity check
		if (this->velocity.y > this->MaxVelocity)
			this->velocity.y = this->MaxVelocity;

		//Deceleration
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) //Check for negative y
	{
		//Max velocity check
		if (this->velocity.y < -this->MaxVelocity)
			this->velocity.y = -this->MaxVelocity;

		//Deceleration
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->sprite.move(this->velocity * dt); //Uses velocity
	
	
}




