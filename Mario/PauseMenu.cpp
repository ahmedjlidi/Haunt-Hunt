#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::InitButton(RenderWindow& window, shared_ptr<Font> font, Texture &texture, bool showResume)
{
	Vector2f buttonSize = { 300, 100 };
	const float centerX = window.getSize().x / static_cast<float>(2) - (buttonSize.x / 2);
	int defaultY = 100;

	font = make_shared<Font>();
	Color Idle = Color(255, 255, 255);

	this->buttons["Resume"] = new Button(centerX, defaultY, buttonSize.x, buttonSize.y, this->font, "Resume",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->texture, 50.f);

	this->buttons["Quit_To_Menu"] = new Button(centerX, defaultY + 600.f, buttonSize.x, buttonSize.y, this->font, "Quit",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->texture, 50.f);

	this->buttons["Quit"] = new Button(centerX, defaultY + 750.f, buttonSize.x, buttonSize.y, this->font, "Quit to desktop",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->texture, 50.f);
}

void PauseMenu::InitBackround(RenderWindow &window)
{
	this->Backround.setSize(Vector2f(static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().x)));
	this->Backround.setFillColor(Color(Color(169, 91, 73)));

}

void PauseMenu::InitContainer(RenderWindow& window)
{
	this->container.setSize(Vector2f(500,
		static_cast<float>(window.getSize().x)));
	this->container.setFillColor(Color(50, 50, 50, 100));
	this->container.setOutlineThickness(1);
	this->container.setOutlineColor(Color::White);
	this->container.setPosition(window.getSize().x / 2.f - this->container.getSize().x / 2.f, 0.f);

}

PauseMenu::PauseMenu(RenderWindow& window, shared_ptr<Font> font, Texture& texture)
	:font(font), texture(texture)
{
	this->InitButton(window,this->font, this->texture);
	this->InitBackround(window);
	this->InitContainer(window);

}

bool PauseMenu::Quit() 
{
	if (this->buttons["Quit"]->IsPressed())
	{
		return true;
	}
	return false;
}

bool PauseMenu::GetResumeStatus()
{
	if (this->buttons["Resume"]->IsPressed())
	{
		return true;
	}

	return false;
}

const bool PauseMenu::GoToMenu()
{
	if (this->buttons["Quit_To_Menu"]->IsPressed())
	{
		return true;
	}

	return false;
}

void PauseMenu::AddButton(RenderWindow& window, shared_ptr<Font> font, Texture& texture,
	float width, float height, float pos_y,
	unsigned char_size, const string button_name,
	const string button_text)
{
	Vector2f buttonSize = { width, height };
	const float centerX = window.getSize().x / static_cast<float>(2) - (buttonSize.x / 2);
	int PosY = pos_y;

	font = make_shared<Font>();
	Color Idle = Color(255, 255, 255);

	this->buttons[button_name] = new Button(centerX, PosY, buttonSize.x, buttonSize.y, this->font, button_text,
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->texture, char_size);
}

Button* PauseMenu::GetButton(const string button_name)
{
	return this->buttons[button_name];
}



void PauseMenu::update(const Vector2f MousePos)
{
	for (const auto& e : this->buttons)
	{
		e.second->update(MousePos);
	}

}

void PauseMenu::render(RenderTarget* target)
{
	target->draw(this->container);

	for (const auto& e : this->buttons)
	{
		e.second->render(target);
	}
}
