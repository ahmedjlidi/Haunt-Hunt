#pragma once


enum movement 
{
	IDLE = 0,
	MOVING_UP = 1,
	MOVING_DOWN = 2,
	MOVING_LEFT = 3,
	MOVING_RIGHT = 4
};

enum StopVelocity
{
	STOP_VELOCITY = 0,
	STOP_VELOCITY_X, 
	STOP_VELOCITY_Y
};
enum shooting 
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

class MoveMentComponent
{
private:
	Sprite &sprite;
protected:


	Vector2f velocity;

	float MaxVelocity;
	float accelration;
	float deceleration;


public:

	int GetMovementStatus();
	int getShootingStatus(const Vector2f& PlayerPos, const Vector2f& MousePos);
	const bool IsIdle()const;
	const float& getMaxVelocity() const;
	const Vector2f& getVelocity() const ;
	MoveMentComponent(Sprite &sprite, float MaxVelocity,float accelration, float deceleration);

	void stopVelocity(const short stop_veolcity);
	void slowVelocity(const float offset);
	


	void move(const float dir_x, const float dir_y,const float &dt);
	void update(const float& dt);
	
};

