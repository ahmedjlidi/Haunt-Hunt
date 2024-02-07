#pragma once 
#include "State.h"
#include "StatesAssetManager.h"
#include "GfxSettings.h"



class SettingsState : public State, StatesAssetManager
{
private:
	GfxSettings gfxsettings;

	shared_ptr<Font> font;
	Texture& texture;
	RectangleShape Backround;

	map<string, Button*>  buttons;
	map<string, DropDownList*>  dropdownlists;
	map<string, Label*> labels;
	stack<PopUpWinodw*>popup_windows;
	PopUpWinodw* popup_window;

	vector<VideoMode>videomodes;
	vector<string>fpslist;
	vector<string> isFullscreen;
	vector<string>verticalSync;
	
	void InitVariables();
	void InitButton(RenderWindow& window, shared_ptr<Font> font, Texture& texture);
	void InitBackround(RenderWindow& window, Texture& texture);
	void InitTextures();

	Texture temp;



	//void InitFonts();
	void InitKeybinds();


	
public:
	SettingsState(stateData* state_data
	,shared_ptr<Font>font, Texture &texture, map<string, Texture>* textures, map<string, Font>* Fonts, GfxSettings& gfx_settings);
	virtual ~SettingsState();

	void UpdateKeys(const float& dt);
	

	void updateButtons(const float &dt);
	void update(const float &dt);
	void render(RenderWindow* target = nullptr) override;

};
