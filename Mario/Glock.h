#pragma once
#include "Item.h"

class Item;

class Glock : public Item
{
	Sprite sprite;
	Texture texture;
	RectangleShape shape;
	stack<Sprite*> bullets;
	void InitSprite();

	unsigned magazine_size;
	unsigned magazine_size_Max;

	float damage;
	
public:
	Glock(Texture& texture, Sprite& sprite, const bool isEquipped, unsigned magazine_size, float damage);


	const int getMagazineSize() const override;
	void reload(unsigned& magazineQuantity) override;
	void reduceAmmo(const int* amount = nullptr)override;
	void updateBulletPosition(const Vector2f& GunPosition);
	void updateUseAnimation(const float & dt,unsigned int Status, const Vector2f& GunPos) override;
	void updateMovementAnimation(const short MovementStatus, const float& dt) override;
	const float getDamage()const override;
	virtual void setDamage(const float damage)override;
	void renderShooting(RenderTarget &target);
	
};

