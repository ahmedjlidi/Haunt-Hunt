#pragma once


class HitBoxComponent
{
private:
	Sprite& sprite;
	float offsetX;
	float offsetY;
	RectangleShape hitbox;
	FloatRect NextPosition;
public:
	HitBoxComponent(Sprite &sprite, float offset_x, float offset_y,float width, float height );

	bool CheckInterset(const FloatRect& frect);
	const Vector2f& getPosition() const;
	const FloatRect GlobalBounds() const;
	const FloatRect& getNextPosition(const Vector2f& velocity, const float& dt);


	void setPosition(const Vector2f& Position);


	void update(const float& dt);
	void render(RenderTarget* target);
};

