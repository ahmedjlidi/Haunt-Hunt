#pragma once
#include "GLock.h"
#include "Herb.h"
#include "Magazine.h"
#include "Key.h"
#include "SpecialKey.h"
#include "Crystal.h"
#include "MedKit.h"
#include "UpgradeKit.h"

enum ITEMS
{
	FLASHLIGHT = 0,
	GLOCK,
	HERB,
	MAGAZINE,
	KEY,
	SPECIAL_KEY,
	CRYSTAL,
	MED_KIT,
	UPGRADE_KIT


};



class InventoryComponent
{
private:
	map<const short , Texture>textures;
	map<string, Sprite*>sprites;
	map<const short, Item*> items;

	short ItemId = 0;
	void InitFonts();
	void InitTextures();


public:

	InventoryComponent();
	void addItem(const short itemId, Texture* texture = nullptr, Sprite* sprite = nullptr);
	void EquipItem(const short ItemId);
	const bool CurrentItemisInInventory() const;
	const bool itemisInInventory(const short id) const;
	Item* CurrentItem();
	Item* getItemInInventory(const short id) const;
	Texture& getCurrentItemTexture();
	Texture& getItemTexture(const short id);
	const short CurrentEquippedItemID();
};

