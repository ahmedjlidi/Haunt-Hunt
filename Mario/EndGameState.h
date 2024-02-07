#pragma once
#include "StatesAssetManager.h"
#include "State.h"
#include "GameState.h"


class State;
class StatesAssetManager;

class EndGameState : public State, StatesAssetManager
{
private:
	AudioSystem& audio_system;
	
	void InitTextures();
	void InitSounds();
	void InitFont();
	void InitKeybinds()override;
	void InitText();
	void InitButtons();

	map<string, Text*> texts;
	map<string, Button*>buttons;


public:
	EndGameState(stateData* state_data, map<string, Texture>* textures, map<string, Font>* Fonts,
		GfxSettings& gfx_settings, AudioSystem& audio_system);
	virtual ~EndGameState();
	void UpdateKeys(const float& dt) override;

	void update(const float &dt);
	void render(RenderWindow* target = NULL)override;

};

