#pragma once
#include "Entity.h"

enum PlayerState 
{
	Inactive = 0,
	RUNNING,
	HOLDING_GUN,
	SHOOTING,
	RELOADING
};


class Player : public Entity
{
private:
	int state;
	int currentRoom = 0;
	void InitVariables();
	void InitComponent(Texture &texture_sheet);
	void InitKeyTime() override;

public:
	Player(float x, float y,  Texture& texture_sheet);
	virtual ~Player();

	//inventory
	//====================================
	void addItem(const short ItemId);
	void EquipItem(const short ItemId);
	const short CurrentEquippedITemID();
	Texture& getCurrentItemTexture();
	Texture& getItemTexture(const short id)const ;
	Item* CurrentItem();
	Item* getItemInInventory(const short id) const;
	const bool CurrentitemIsInInventory();
	const bool itemIsInInventory(const short id);
	//==================================
	const FloatRect updateRange();
	const int CurrentRoom()const override;
	void setRoom(const short room);
	const int getState()const;
	void ChangepawnPosition(Vector2f position);
	void update(const float& dt, const Vector2f& PlayerPos, const Vector2f& MousePos,const bool busy);

	void render(RenderTarget* target, Shader* shader = nullptr, Vector2f position = Vector2f(),
		const bool busy = false, const bool showHitBox = false);

};

