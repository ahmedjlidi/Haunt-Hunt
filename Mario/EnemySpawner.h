#pragma once
#include "Enemy.h"
#include "cyclops.h"
#include "ghost.h"
#include "Giant.h"
#include "Boss.h"

enum ENEMYTYPE 
{
	CYCLOPS = 0,
	GHOST,
	GIANT,
	BOSS
};

class Enemy;
class cyclops;

class EnemySpawner
{
private:

	vector<Enemy*> enemies;
	int maxEnemies;
	float timeToSpawn;
	

	vector<Vector2f>& Position;

	RectangleShape Range;
	map<string, Texture>texture_sheets;


	void InitTextures();
	int getRandomNumber(float min, float max);
	int getRandomInt(int min, int max);


	map<string, SoundBuffer> sounds;
	
	map<string,map<string , Sound>> enemySounds;
	//map<string, Sound> cyclopsSounds;
public:


	EnemySpawner(vector<Vector2f>&Position, Vector2f range, float timeToSpawn);
	vector<Enemy*>* CurrentEnemies()noexcept;
	void updateEnemiesSpawn(Entity& playerEntity);
	void renderEnemies(RenderTarget& target);

};

