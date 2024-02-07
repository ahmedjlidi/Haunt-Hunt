#pragma once


class StatesAssetManager
{
private:

	
	vector<string> texturePath;
	
protected:
	map<string, Texture>* textures;
	map<string, Font>* Fonts;

	map<string, Texture> TextureManager;
	map<string, Font> FontManager;

	

public:
	StatesAssetManager(map<string, Texture>* textures, map<string, Font>* Fonts);
};



