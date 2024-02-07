#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::Initlogo(Texture& texture,RenderWindow  &window)
{
	this->logo.setTexture(texture);
	this->logo.setScale(0.2f, 0.2f);
	this->logo.setPosition(window.getSize().x / 2.f - this->logo.getGlobalBounds().width / 2.f,
		window.getSize().y / 2.f - this->logo.getGlobalBounds().height / 2.f);
	

}

void SplashScreen::InitCover(RenderWindow& window)
{
	color = Color::Black;
	this->Cover.setSize(Vector2f(window.getSize()));
	this->Cover.setFillColor(color);
}


SplashScreen::SplashScreen(Texture &texture, RenderWindow& window, float fps): texture(texture), fps(fps)
{
	this->Initlogo(this->texture, window);
	this->InitCover(window);
}

void SplashScreen::Fade(const float& dt)
{
	static float offset = 255;
	offset -= 30.f / ((static_cast<float>(this->fps) / 60.f));
	color.a = offset;
	this->Cover.setFillColor(color);
}

const bool SplashScreen::Quit() const
{
	static Clock SplashScreenTimer;
	if (color.a <= 0 || this->quit)
	{
		return true;
	}
	return false;
}

void SplashScreen::update(const float &dt)
{
	this->Fade(dt);
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->quit = true;
	}
}

void SplashScreen::render(RenderTarget& target)
{
	target.draw(this->logo);
	target.draw(this->Cover);
}
