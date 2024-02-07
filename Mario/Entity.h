
#pragma once
#include "MoveMentComponent.h"
#include "AnimationComponent.h"
#include "HitBoxComponent.h"
#include "AttributeComponent.h"
#include "InventoryComponent.h"
#include "HealthComponent.h"


class Entity
{
private:
	
	void InitVariables();
	
	

protected:
	Sprite sprite;
	Texture textureSheet;
	MoveMentComponent* movementcomponent;
	AnimationComponent *animationcomponent;
	HitBoxComponent *hitboxcomponent;
	AttributeComponent* attributecomponent;
	InventoryComponent* invertorycomponent;
	HealthComponent* healthcomponent;
	
	float keytime;
	float keytimeMax;

	virtual void InitKeyTime();
	virtual bool getKeyTime();
	virtual void updateKeytime(const float& dt);


	void CreateSprite(Texture &texture);
	void LoadTextures();
	void createMovement(const float MaxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(Texture &texture_sheet);
	void createHitBoxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createAttributeComponent(const unsigned level);
	void createInventoryComponent();
	void createHealthComponent(float hp, Vector2f size, Vector2f position);

	map<string, Texture>TextureLoader;
	
	
	
public:
	Entity();
	virtual ~Entity();

	
	//const Vector2f get

	
	virtual const Vector2f& getPosition();
	virtual const Vector2f getCenter()const noexcept;
	virtual const Vector2u getGridPosition(const unsigned grid_size)const;
	virtual const FloatRect getGlobalbounds() const;
	virtual const FloatRect getNextPositionBounds(const float& dt) const;
	virtual const Vector2f& getVelocity() const;
	virtual const bool HP_is_0()const;
	virtual float& getHp();

	virtual void SetSpawnPosition(const float x, const float y);
	virtual void InitComponent(Texture &texture_sheet) = 0;
	virtual void updateHP(const float damage);
	virtual void restorHp();
	virtual const int CurrentRoom()const;
	virtual void renderHPBar(RenderTarget& target);
	virtual void stopVelocity(const short stop_velocity);
	virtual void slowVelocity(const float offset);
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void update(const float &dt);
	virtual void render(RenderTarget* target);

	
};

