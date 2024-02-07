#include "stdafx.h"
#include "InventoryComponent.h"



void InventoryComponent::InitFonts()
{
}

void InventoryComponent::InitTextures()
{
	if (!this->textures[ITEMS::FLASHLIGHT].loadFromFile("resources/models/flashlightIcon.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::GLOCK].loadFromFile("resources/models/pistol_icon.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::HERB].loadFromFile("resources/models/herb.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::MAGAZINE].loadFromFile("resources/models/magazine.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::KEY].loadFromFile("resources/models/key.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::SPECIAL_KEY].loadFromFile("resources/models/special_key.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::CRYSTAL].loadFromFile("resources/models/crystal.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::MED_KIT].loadFromFile("resources/models/med_kit.png"))
		cout << "Error loading Icons\n";

	if (!this->textures[ITEMS::UPGRADE_KIT].loadFromFile("resources/models/toolbox.png"))
		cout << "Error loading Icons\n";
}

	

InventoryComponent::InventoryComponent()
{
	this->ItemId = 0;
	this->items[ITEMS::FLASHLIGHT] = nullptr;
	this->InitTextures();
}

void InventoryComponent::addItem(const short itemId, Texture* texture, Sprite* sprite)
{
	if (itemId == ITEMS::GLOCK)
	{
		if(this->items.find(ITEMS::GLOCK) == this->items.end())
			this->items[itemId] = new Glock(*texture, *sprite, false, 15, 35.f);
	}
	else if (itemId == ITEMS::HERB)
	{
		if (this->items.find(ITEMS::HERB) == this->items.end())
			this->items[itemId] = new Herb(1);
		else
		{
			this->items[itemId]->increase();
		}
	}
	else if (itemId == ITEMS::MAGAZINE)
	{
		if (this->items.find(ITEMS::MAGAZINE) == this->items.end())
			this->items[itemId] = new Magazine(1);
		else
		{
			this->items[itemId]->increase(new int(15));
		}
	}
	else if (itemId == ITEMS::KEY)
	{
		if (this->items.find(ITEMS::KEY) == this->items.end())
			this->items[itemId] = new Key(1);
		else
		{
			this->items[itemId]->increase();
		}
	}
	else if (itemId == ITEMS::SPECIAL_KEY)
	{
		if (this->items.find(ITEMS::SPECIAL_KEY) == this->items.end())
		{
			this->items[itemId] = new SpecialKey(1);
		}
		else
		{
			this->items[itemId]->increase();
		}
	}
	else if (itemId == ITEMS::CRYSTAL)
	{
		if (this->items.find(ITEMS::CRYSTAL) == this->items.end())
		{
			this->items[itemId] = new Crystal(1);
		}
		else
		{
			this->items[itemId]->increase();
		}
	}
	else if (itemId == ITEMS::MED_KIT)
	{
		if (this->items.find(ITEMS::MED_KIT) == this->items.end())
		{
			this->items[itemId] = new MedKit(1);
		}
		else
		{
			this->items[itemId]->increase();
		}
	}
	else if (itemId == ITEMS::UPGRADE_KIT)
	{
		if (this->items.find(ITEMS::UPGRADE_KIT) == this->items.end())
		{
			this->items[itemId] = new UpgradeKit(1);
		}
	}
}

void InventoryComponent::EquipItem(const short ItemId)
{
	if (ItemId == ITEMS::GLOCK)
	{
		this->ItemId = 1;
	}
	else if (ItemId == ITEMS::FLASHLIGHT)
	{
		this->ItemId = 0;
	}
	else if (ItemId == ITEMS::HERB)
	{
		this->ItemId = 2;
	}
	else if (ItemId == ITEMS::MAGAZINE)
	{
		this->ItemId = 3;
	}
	else if (ItemId == ITEMS::KEY)
	{
		this->ItemId = 4;
	}
	else if (ItemId == ITEMS::SPECIAL_KEY)
	{
		this->ItemId = ITEMS::SPECIAL_KEY;
	}
	else if (ItemId == ITEMS::CRYSTAL)
	{
		this->ItemId = CRYSTAL;
	}
	else if (ItemId == ITEMS::MED_KIT)
	{
		this->ItemId = MED_KIT;
	}
	else if (ItemId == ITEMS::UPGRADE_KIT)
	{
		this->ItemId = UPGRADE_KIT;
	}
}

const bool InventoryComponent::CurrentItemisInInventory() const
{
	auto it = this->items.find(this->ItemId);
	if (it != this->items.end())
	{
		return true;
	}
	return false;
}

const bool InventoryComponent::itemisInInventory(const short id) const
{
	auto it = this->items.find(id);
	if (it != this->items.end())
	{
		return true;
	}
	return false;
}

Item* InventoryComponent::CurrentItem()
{
	auto it = this->items.find(this->ItemId);
	if (it != this->items.end() && it->second != nullptr)
	{
		return it->second;
	}
	return nullptr;
}

Item* InventoryComponent::getItemInInventory(const short id) const
{
	auto it = this->items.find(id);
	if (it != this->items.end() && it->second != nullptr)
	{
		return it->second;
	}
	return nullptr;
}


Texture& InventoryComponent::getCurrentItemTexture()
{
	return this->textures[this->ItemId];
}

Texture& InventoryComponent::getItemTexture(const short id)
{
	return this->textures[id];
}

const short InventoryComponent::CurrentEquippedItemID()
{
	return this->ItemId;
}
