#pragma once
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "StatesAssetManager.h"
#include "TileMap.h"
#include "GfxSettings.h"
#include "EnemySpawner.h"
#include "EndGameState.h"

class State;
class Player;
class PauseMenu;
class StatesAssetManager;
class TileMap;
class GfxSettings;
class EndGameState;

enum DIALOGUE
{
	INTRO =0,
	ENEMY_ENCOUNTER,
	AFTER_SEEING_ENEMY,
	GUN_FOUND,
	BOSS_MEET,
	KILLED_BOSS,
	REALAIZE
};

class GameState : public State, StatesAssetManager
{

private:
	

	//graphics===========================
	View view;
	Vector2i viewGridPosition;
	RenderTexture renderTexture;
	Sprite renderSprite;
	Shader core_shader;
	RectangleShape AmbientLighting;
	/*=======================================*/

	/*actors======================================*/
	Player *player;
	EnemySpawner* enemySpawner;
	/*==========================================*/

	/*Map==========================================*/
	TileMap* tile_map;
	/*==========================================*/

	/*Gui=============================================*/
	PauseMenu *pausemenu;
	playerGui::HpBar* hp_bar;
	unordered_map<string, PopUpWinodw*>popup_windows;
	playerGui::ItemPreview* itempreview;
	Sprite blood_overlay;
	unordered_map<string,stack<DialogueWindow*>>dialogue_windows;
	stack<DialogueWindow*>* CurrentDialogue;
	unordered_map<string, vector<string>> dialogues;
	shared_ptr<PopUpText> popuptext ;
	short dialogueIndex = 0;
	short DialogueNum = 0;


	map<string, bool> Objectives;
	float time_left = 120.f;
	Clock timer;


	/*=============================================*/

	/*resources*/
	std::shared_ptr<Font> fontt;
	Text test;
	AudioSystem& audio_system;

	/*graphics=================================*/
	void InitLight(GfxSettings& gfx_settings);
	void InitView(GfxSettings &gfx_settings);
	void InitRenderArea(GfxSettings& gfx_settings);
	void InitShader();
	/*=========================================*/

	/*resources=============================*/
	void InitTextures();
	void InitFont();
	void InitKeybinds();
	void InitSounds();
	void loadDialogueText();
	/*=======================================*/

	/*map ========================================*/
	void InitMap();
	/*=========================================*/

	/*actors========================================*/
	void InitPlayer();
	void InitEnemySpawner();
	/*===========================================*/

	/*GUI============================================*/
	void InitPauseMenu();
	void InitPopUpText();
	void InitHpBar();
	void InitItemPreview();
	void InitGui();
	void InitDialogueWindow();
	void InitObjectives();
	/*===============================================*/
	
public:
	GameState(stateData* state_data, map<string, Texture>* textures, map<string, Font>* Fonts,
		GfxSettings &gfx_settings, AudioSystem& audio_system);
	virtual ~GameState();
	void GamePlayEvents();

	void UpdatePopupWindowEvents();
	void UpdateKeys(const float& dt);
	void updateView();
	void updateMouseCursor();
	void updatePlayerState();
	void updateAudioEvents();
	void updateWorld(const float& dt);
	void updateEnemySpawn(const float& dt);
	void updateDialogueWindow(const float& dt);
	void updateGui(const float& dt);
	void updateGameplay(const float &dt);
	void update(const float& dt) override;
	


	void renderPopUpWindow(RenderTarget& target);
	void RenderGui(RenderTarget& target);
	void renderActors(RenderTexture& renderTexture);
	void render(RenderWindow* target = nullptr) override;
	void EndState();
	
	
};

