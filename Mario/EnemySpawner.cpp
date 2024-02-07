#include "stdafx.h"
#include "EnemySpawner.h"

void EnemySpawner::InitTextures()
{
	
	this->texture_sheets["cyclops"].loadFromFile("resources/enitties/enemy_sheet.png");
	this->texture_sheets["ghost"].loadFromFile("resources/enitties/ghost.png");

	this->texture_sheets["giant"].loadFromFile("resources/enitties/boss.png");
	this->texture_sheets["boss"].loadFromFile("resources/enitties/final_boss.png");


	this->sounds["ghost_patrol"].loadFromFile("resources/audio/ghost.wav");
	this->sounds["ghost_chase"].loadFromFile("resources/audio/ghost_chase.wav");
	this->sounds["cyclops_patrol"].loadFromFile("resources/audio/cyclops.wav");
	this->sounds["cyclops_chase"].loadFromFile("resources/audio/cyclops_chase.wav");
	this->sounds["giant_patrol"].loadFromFile("resources/audio/giant.wav");
	this->sounds["giant_chase"].loadFromFile("resources/audio/giant_chase.wav");
	this->sounds["boss_sound"].loadFromFile("resources/audio/boss_sound.wav");

	this->enemySounds["ghost_sounds"]["patrol"].setBuffer(this->sounds["ghost_patrol"]);
	this->enemySounds["ghost_sounds"]["chase"].setBuffer(this->sounds["ghost_chase"]);

	this->enemySounds["cyclops_sounds"]["patrol"].setBuffer(this->sounds["cyclops_patrol"]);
	this->enemySounds["cyclops_sounds"]["chase"].setBuffer(this->sounds["cyclops_chase"]);

	this->enemySounds["giant_sound"]["patrol"].setBuffer(this->sounds["giant_patrol"]);
	this->enemySounds["giant_sound"]["chase"].setBuffer(this->sounds["giant_chase"]);

	this->enemySounds["boss_sounds"]["patrol"].setBuffer(this->sounds["boss_sound"]);
	this->enemySounds["boss_sounds"]["chase"].setBuffer(this->sounds["boss_sound"]);
	
}

int EnemySpawner::getRandomNumber(float min, float max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> dis(min, max);
	return dis(gen);

}

int EnemySpawner::getRandomInt(int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

EnemySpawner::EnemySpawner(vector<Vector2f>& Position, Vector2f range, float timeToSpawn)
	:Position(Position), timeToSpawn(timeToSpawn)
{
	this->InitTextures();
	Range.setSize(range);
}

vector<Enemy*>* EnemySpawner::CurrentEnemies() noexcept
{
	return &this->enemies;
}



void EnemySpawner::updateEnemiesSpawn(Entity& playerEntity)
{
	const Vector2f PlayerPos = playerEntity.getPosition();

	this->Range.setPosition(PlayerPos.x - (this->Range.getSize().x / 2.f), PlayerPos.y - (this->Range.getSize().y / 2.f));
	static Clock delay;
	if (this->Range.getGlobalBounds().contains(PlayerPos))
	{
		if (delay.getElapsedTime().asSeconds() >= timeToSpawn)
		{

			for (auto& e : this->Position)
			{
				int propablity = this->getRandomInt(0, 7);
				if (this->Range.getGlobalBounds().contains(e))
				{
					const FloatRect updateRange = this->Range.getGlobalBounds();

					 if (playerEntity.CurrentRoom() == 1)
					{
						this->enemies.emplace_back(new ghost(e.x, e.y, this->getRandomNumber(200.f, 350.f), this->texture_sheets["ghost"]
							, true, Vector2f(e.x - this->getRandomNumber(400, 600), e.y), Vector2f(e.x, e.y), 200.f, Vector2f(800.f, 800.f)
							, 50, ENEMYTYPE::GHOST, this->enemySounds["ghost_sounds"], updateRange));
					}

					 else if (playerEntity.CurrentRoom() == 4)
					{
						this->enemies.emplace_back(new Giant(e.x, e.y, this->getRandomNumber(200.f, 250.f), this->texture_sheets["giant"]
							, true, Vector2f(e.x - this->getRandomNumber(200.f, 350.f), e.y), Vector2f(e.x, e.y), 400.f, Vector2f(800.f, 800.f)
							, 75.f, ENEMYTYPE::GIANT, this->enemySounds["giant_sound"], updateRange));
					}
					 else if (playerEntity.CurrentRoom() == 5)
					{
						this->enemies.emplace_back(new Boss(e.x, e.y, this->getRandomNumber(200.f, 220.f), this->texture_sheets["boss"]
							, true, Vector2f(e.x - this->getRandomNumber(200.f, 350.f), e.y), Vector2f(e.x, e.y), 400.f, Vector2f(1500.f, 1500.f)
							, 80.f, ENEMYTYPE::BOSS, this->enemySounds["boss_sounds"], updateRange));
					}
					
					else
					{
						if (propablity >= 0 && propablity <=3)
						{
							this->enemies.emplace_back(new ghost(e.x, e.y, this->getRandomNumber(200.f, 350.f), this->texture_sheets["ghost"]
								, true, Vector2f(e.x - this->getRandomNumber(400, 600), e.y), Vector2f(e.x, e.y), 200.f, Vector2f(800.f, 800.f)
								, 50, ENEMYTYPE::GHOST, this->enemySounds["ghost_sounds"], updateRange));

						}
						else if (propablity >= 4 && propablity <= 7)
						{
							this->enemies.emplace_back(new cyclops(e.x, e.y, this->getRandomNumber(250.f, 400.f), this->texture_sheets["cyclops"]
								, true, Vector2f(e.x - this->getRandomNumber(500.f, 700.f), e.y), Vector2f(e.x, e.y), 200.f, Vector2f(600.f, 600.f)
								, 20, ENEMYTYPE::CYCLOPS, this->enemySounds["cyclops_sounds"], updateRange));

						}
					}
					this->Position.erase(remove(this->Position.begin(), this->Position.end(), e), this->Position.end());
				}
			}
		}
	}
	else
		delay.restart();
}

void EnemySpawner::renderEnemies(RenderTarget& target)
{
	target.draw(this->Range);
}

