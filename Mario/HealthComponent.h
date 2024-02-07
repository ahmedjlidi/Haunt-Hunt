#pragma once

class HealthComponent
{
private:

	float hp;
	float MaxHp;
	float damage;
	Vector2f size;
	Vector2f MaxSize;
	Vector2f position;
	RectangleShape healthBar;
	

public:

	HealthComponent(const float hp,Vector2f size, Vector2f position);
	const bool HP_is_0()const ;
	float& getHp();
	void restoreHp();
	void updateHp(const float damage);
	void render(RenderTarget& target , Vector2f *position = nullptr);

};

