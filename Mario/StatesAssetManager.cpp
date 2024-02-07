#include "stdafx.h"
#include "StatesAssetManager.h"

StatesAssetManager::StatesAssetManager(map<string, Texture>* textures, map<string, Font>* Fonts)
{
	this->textures = textures;
	this->Fonts = Fonts;
}


