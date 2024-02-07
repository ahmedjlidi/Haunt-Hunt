#pragma once

#include "State.h"
#include "GameState.h"
#include "SettingsState.h"
#include "SplashScreen.h"
#include "GfxSettings.h"
#include "EditorState.h"




class MainMenuState : public State, public StatesAssetManager
{
private:
	GfxSettings& gfxsettings;
	AudioSystem* audioSystem;
	//Font font;
	
	map<string, Button*>  buttons;
	Label* label;

	Sprite BackGround;
	Sprite Logo;
	Sprite MouseCursor;
	RectangleShape BackroundImageBounds;

	Text title;

	SplashScreen *splashscreen;


	void InitFonts();
	void InitKeybinds();
	void InitButtons();
	void InitAudio();
	
	void InitTextures();
	void InitText();
public:
	MainMenuState(stateData *state_data,
		map<string, Texture>* textures, map<string, Font>* Fonts, GfxSettings& gfx_settings);
	virtual ~MainMenuState();

	void UpdateKeys(const float& dt);
	void EndState() override;
	
	void update(const float& dt) override;
	void render(RenderWindow* target = nullptr) override;
	

};

