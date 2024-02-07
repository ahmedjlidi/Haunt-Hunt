#pragma once


enum TileTypes 
{
	DEFAULT =0,
	DAMAGING,
	OverLap,
	Chest,
	PlayerSpawn,
	ENEMYSPAWN,
	DOOR,
	LIGHT,
	KEY_CONTAINER,
	LETTER
};




class Tile
{

protected:
	Sprite shape;
	Texture &texture;
	bool collision;
	short type;


	

	
	
public:
	
	Tile(unsigned x, unsigned y, const float GridSize, Texture &texture,
		const IntRect& texture_rect, bool collision = false, short type= TileTypes::DEFAULT);
	virtual ~Tile();

	const string GetAsString();
	const short GetTypes();
	const Vector2f GetPosition() const;
	const bool getCollision() const;
	const bool Intersects(FloatRect bounds ) const;
	const FloatRect& getGlobalBounds() const;
	void setType(const short type);


	void update();
	void render(RenderTarget& target, Shader* shader = nullptr, Vector2f Position = Vector2f());
};

