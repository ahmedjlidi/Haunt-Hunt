#pragma once
#include "Entity.h"
#include "_3dAudio.h"

enum ENEMYSTATES 
{
	PATROL = 0,
	CHASE,
	ATTACK,
	ENEMY_DIE,
	BEING_HIT
	
};

class Enemy : public Entity
{
private:
	
	Clock delay;
	Clock Collisiondelay; 
	Clock hpBarDisplayTime;
	bool die;
	bool reachPatrolEnd;
	bool reachedPlayer;
	float damage;

	RectangleShape range;
	FloatRect updateRange;
	Vector2f interestRange;

	short type;
	
public:

	virtual void InitVariables() = 0;
	virtual void InitComponent(Texture& texture_sheet) = 0;

	Vector2f PatrolPositionEnd;
	Vector2f PatrolPositionStart;

	map<string, Sound> sounds;

	_3dAudio audio;

	bool patrol;
	int state;
	float hp;
	float CurrentHP;
	
	int CollisionCounter = 0;

	Enemy(float x, float y, Texture& texture_sheet, const bool patrol,
		const Vector2f PatrolPositionEnd, const Vector2f PatrolPositionStart, float hp,
		Vector2f interestRange ,float damage,short type, const map<string, Sound>& sounds, const FloatRect& update_range);


	virtual void PlayAnimation(const string name, const float& dt);
	virtual void deductHp(const float damage);
	virtual void setState(ENEMYSTATES state);
	virtual void ChangePatrolDirection();
	virtual const bool HasDied() const noexcept;
	const int getHp() const;
	virtual const float getDamage()const ;
	virtual const int getState();
	virtual const int getType() const;
	virtual void updatePatrolState(const float& dt, Entity& playerEntitty);
	virtual void updateChaseState(const float& dt, Entity& playerEntitty);
	virtual void updateDeathState(const float& dt);
	virtual void renderHPBar(RenderTarget& target) override;
	
	virtual void updateState(const Vector2f playerPos);
	virtual void update(const float& dt, Entity& playerEntitty);
	virtual void render(RenderTarget& target, Shader* shader, Vector2f position,const bool showHitBox);


	virtual void playSound(const string name, const Vector2f& playerPos);
	/*virtual void playChaseSound(const string name, const Vector2f& playerPos);*/
	virtual void stopSound(const string name);
	void renderSoundRange(const string name, RenderTarget& target);
	

};

