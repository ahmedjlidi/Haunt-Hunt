#pragma once
#include "MainMenuState.h"
#include "StatesAssetManager.h"




class Game
{
private:

	
	//Inisialisers
	void InitStateData();
	void InitGfxSettings();
	void InitWindow();
	void InitVariables();
	void InitStates();
	void InitKeys();
	void InitTextures();

	

	//objects from other classes


	//window variables
	RenderWindow* window;

	vector<VideoMode>videomodes;

	Event ev;

	
	//resources
	stack<State*>states;
	stateData statedata;
	Sprite BackGround;
	map<string, int> supportedKeys;
	map<string, Texture> textures;
	map<string, Font> fonts;
	std::vector<std::string> texturePath;

	GfxSettings *gfx_settings;
	//vars
	Clock dtClock;
	float dt;
	

	float GridSize;

public:

	//constructors destructors
	Game();
	virtual ~Game();
	
	
	//main updatrin function
	void updateDt();
	void pollevent();
	const bool IsRunning();
	void update();

	void render();
	void run();

};

