#pragma once


class SplashScreen 
{
private:
	RectangleShape Cover;
	Sprite logo;
	Texture &texture;
	Color color;
	float fps;
	bool quit = false;

	void Initlogo(Texture &texture,RenderWindow &window);
	void InitCover(RenderWindow &window);
public:

	SplashScreen(Texture &texture, RenderWindow & window, float fps);
	void Fade(const float &dt);
	const bool Quit() const;
	void update(const float& dt);
	void render(RenderTarget& target);

};

