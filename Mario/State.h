#pragma once
#include "gui.h"
#include "GfxSettings.h"
#include "AudioSystem.h"


using namespace GUI;

class gui;
class State;

class stateData
{
public:
	stateData() {};

	//Variables
	float gridSize;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedkeys;
	std::stack<State*>* states;
	
};

class State 
{

protected:
	map<string, int>* supportedkeys;
	map<string, int> keybinds;


	stack<State*>* states;
	stateData* stateDataPtr;

	RenderWindow* window;
	
	map<string, Texture> Gtextures;
	
	Vector2i MosPosScreen;
	Vector2i MosPosWindow;
	Vector2f MosPosView;

	Vector2u MousePosGrid;

	Sprite MouseCursor;

	GfxSettings *gfx_settings;


	bool quit;
	bool pause;

	float keytime;
	float keytimeMax;
	float gridSize;

	Text fpsText;
	

	virtual void InitKeybinds() = 0;
	virtual void InitfpsText(Font& font);
	virtual void InitMouseCursor(Texture &texture);
	virtual const Vector2f GetMouseCursorPos()const;
	virtual void renderMouseCursor(RenderTarget* target);
	virtual void updateMouseCursor();
	virtual void ShowMouseCursor(bool show);
public:
	State(stateData *state_data);
	virtual ~State();
	
	const bool& getQuitStatus();
	bool getKeyTime();
	

	void PauseState();
	void UnPauseState();

	void SetFullScreen();

	bool AllowMouse(const string mouseButton);
	bool AllowKeyboardPress(unsigned key);


	static Vector2f Mouse_pos(const RenderWindow &window) ;

	virtual const int RandIntBetween(const int x, const int y);
	virtual void updateKeytime(const float &dt);
	virtual void calcFps(const float& dt);
	virtual void renderFpsText(RenderTarget &target);
	virtual void setMouseCursorTexture(const Texture& texture);
	virtual void UpdateMosePos(View* view = nullptr);
	virtual void UpdateKeys(const float& dt) = 0;
	virtual void EndState();
	
	virtual void update(const float &dt) = 0;
	virtual void render(RenderWindow* target = NULL) = 0;

};

