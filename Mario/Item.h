#pragma once
#include "AnimationComponent.h"



class Item 
{
	
protected:
	bool isEquipped;
	AnimationComponent* animationComponent;
	unsigned quantity;

public: 
	Item(Texture* texture = nullptr , Sprite* sprite = nullptr, const bool isEquipped = false);

	void addAnimation(const string name, float speed, unsigned start_x,
		unsigned start_y, unsigned end_x, unsigned end_y, unsigned width, unsigned height);

	virtual void reload(unsigned int& magazineQuantity);
	virtual const int  getMagazineSize() const ;
	virtual void reduceAmmo(const int* amount = nullptr);
	virtual void renderShooting(RenderTarget& target);

	virtual const float getDamage() const;
	virtual void Use(const bool decrement);
	virtual void increase(const int* value = nullptr);
	virtual unsigned int& getQuantity() ;
	virtual const bool isEmpty()const;
	virtual void setDamage(const float damage);


	virtual void updateUseAnimation(const float& dt, unsigned int Status, const Vector2f& GunPos);
	virtual void updateMovementAnimation(const short MovementStatus, const float& dt);
};

