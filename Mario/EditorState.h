#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "TexturePreview.h"
#include "StatesAssetManager.h"
#include "GfxSettings.h"


class State;
class PauseMenu;
class TileMap;
class TexturePreview;

class EditorState :public State, public StatesAssetManager
{
private:

	View view;
	
	PauseMenu* pausemenu;
	TileMap* tile_map;
	map<string, Button*>  buttons;
	TexturePreview* texture_preview;
	

	shared_ptr<Font> font;
	Texture& texture;
	RectangleShape selector;
	vector<Sprite*> CustomSprites;
	
	
	IntRect TextureRect;

	GUI::TextureSelector *texture_selector;

	void InitView(GfxSettings& gfx_settings);
	void InitVariables();
	void InitTextures();
	void InitTextureRect();
	void InitKeybinds();

	
	void InitGui();
	void InitText();

	bool HideTexturePreview = false;
	bool SpriteSelectorIsActive = false;
	Text info;

	/*options================================*/
	bool Collision;
	bool hasReachedTheEndOfTheMap;
	short type;
	float CameraSpeed;
	bool lockTile;
	short doorType;
	/*=================================================*/


	AudioSystem& audio_system;




public:
	EditorState(stateData *state_data
	, shared_ptr<Font> font, Texture &texure, map<string, Texture>*textures,
		map<string, Font>* Fonts, GfxSettings& gfx_settings, AudioSystem &audio_system);
	virtual ~EditorState();


	void ChooseTexture(float Maxheight, float Maxwidth);
	void UpdateKeys(const float& dt);
	void updatePreviewScreen();

	void EndState() override;


	bool AllowEditing();
	void SaveTileMap();

	void updateGUI();
	void updateTextPosition();

	void update(const float& dt) override;
	void render(RenderWindow* target = nullptr) override;
	
};

