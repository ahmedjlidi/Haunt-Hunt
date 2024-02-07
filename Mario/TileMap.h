#pragma once
#include "Tile.h"
#include "Entity.h"
#include "Effects.h"

class Entity;
class StatesAssetManager;

enum PLAYERSPAWNPOS 
{
	START_ROOM,
	ROOM_WITH_STATUE
};

struct Door
{
	FloatRect bounds;
	short type;
};

struct EnemyPositions
{
	FloatRect bounds;
	short type;
};

enum DoorType :short
{
	NORMAL = 0,
	LOCKED,
	SPECIAL,
	ENEMY_DEPEND
};

enum ROOMS :short
{
	ROOM1 = 0,
	ROOM2,
	ROOM3,
	ROOM4,
	ROOM5,
	ROOM6
};



class TileMap 
{
private:
	void clear();

	float GridSizef;
	unsigned GridSize;
	unsigned layers;
	Vector2i Maxsize;
	Vector2f WorldMaxSize;
	vector<vector<vector<vector<Tile*>>>> Map;
	RectangleShape collisionbox;
	Effects* effect = new Effects();
	Texture& texture;
	Text text;
	Font font;

	const string texture_file_directory;
	short Type;

	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	stack<Tile*> overlappingTiles;

	//variables related to events
	bool DamagingTile = false;
	vector<Vector2f> EnemySpawns;
	
	map<short, Vector2f>PlayerSpwanPosistions;
	bool openChest = false;

	short door_type;
	short chest_type;

	/*in game objects (chests, doors, ladders...*/
	///////////////////////////////////////////////
	vector<FloatRect*>Chests;
	vector<FloatRect*>key_containers;
	vector<FloatRect*>Letters;
	vector<Vector2f>lightPositions;
	map<short, Door>doors;
	/// /////////////////////////////////////////////////
	
	
public:


	
	
	
	



	
	
	
	TileMap(float Grid_Size, unsigned width, unsigned height ,
			Texture &texture);
	virtual ~TileMap();

	void addTile(const unsigned x, const unsigned y, const unsigned z,
	const IntRect& texture_rect, bool collision, short type);

	const Vector2f getPlayerSpawnPosition(const short id);
	vector<Vector2f>& getEnemySpawnPosition();
	vector<FloatRect*>& ChestsPosition();
	vector<FloatRect*>&LettersPosition();
	vector<FloatRect*>&key_containersPosition();
	vector<Vector2f>&LightPositions();

	map<short, Door>& DoorPositions();

	const bool empty(const unsigned x, const unsigned y, const unsigned z) const;
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void CheckCollision(Entity &entity, Vector2f& MousePos, const float& dt);

	void DeleteMap();
	void addSpawnPosition(Vector2f pos);
	void deleteSpawnPosition(Vector2f position);

	void addDoor(const Vector2f& pos, short type);
	void DeleteDoor(Vector2f position);



	void setDoorType(const int index, const short type);


	const Texture& getTextureSheet() const ;
	const short GetTileTypes() const ;
	void UpdateChests(const Vector2f MousePos)noexcept;
	const bool hasOpenChest() const noexcept;
	vector<FloatRect*>*ChestTiles();

	bool isDamageTile() const noexcept;

	void saveMap(const string file_name);
	void LoadMap(const string file_name);
	
	void update();
	void render(RenderTarget& target, Vector2i *PlayerGridPos = nullptr,
		bool debug_mode = false, Shader* shader = nullptr, Vector2f Position = Vector2f());
	void renderOverlappingTiles(RenderTarget &target, Shader* shader = nullptr, Vector2f Position = Vector2f());


};
