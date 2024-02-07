#pragma once
#include "gui.h"


using namespace GUI;

class PauseMenu
{
private:
	RectangleShape Backround;
	RectangleShape container;
	shared_ptr<Font> font;
	Texture& texture;
	map<string, Button*>  buttons;

	void InitButton(RenderWindow& window, shared_ptr<Font> font, Texture& texture, bool showResume = true);
	void InitBackround(RenderWindow& window);
	void InitContainer(RenderWindow& window);


public:
	PauseMenu(RenderWindow& window, shared_ptr<Font> font, Texture& texture);
	bool Quit();
	bool GetResumeStatus();
	const bool GoToMenu();

	void AddButton(RenderWindow& window, shared_ptr<Font> font, Texture& texture,
		float width, float height,float pos_y, unsigned char_size, const string button_name,
		const string button_text);

	Button *GetButton(const string button_name);

	void update(const Vector2f MousePos);
	void render(RenderTarget* target);
};

