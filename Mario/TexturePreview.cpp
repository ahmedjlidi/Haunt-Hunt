#include "stdafx.h"
#include "TexturePreview.h"


void TexturePreview::InitTexture()
{
	this->backround_texture.loadFromFile("resources/models/preview.jpg");

}
void TexturePreview::PrevieWindow(const RenderWindow& window,
	float grid_size, float pos_x, float pos_y, float width, float height)
{
	this->background.setPosition(pos_x, pos_y);
	this->background.setSize(Vector2f(width, height));
	this->background.setFillColor(Color::Red);

	if (this->font.loadFromFile("resources/Fonts/Montserrat-Regular.ttf"))
	{
		text.setFont(this->font);
		text.setCharacterSize(25.f);
		text.setFillColor(Color::White);
		text.setOutlineThickness(2);
		text.setOutlineColor(Color::Black);
		text.setString("Texture Preview");
	}
	else
	{
		cout << "Error loading Fonts:::TexturePreview.cpp" << endl;
	}
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);

	float centerX = this->background.getPosition().x + this->background.getSize().x / 2.f;
	float centerY = this->background.getPosition().y + this->background.getSize().y / 7.f;

	this->text.setPosition(centerX, centerY);

	this->texture_preview.setSize(Vector2f(grid_size, grid_size));
	this->texture_preview.setPosition(centerX - grid_size / 2.f
		, this->background.getPosition().y + this->background.getSize().y / 2.5f);

	this->frame.setSize(Vector2f(grid_size, grid_size));
	this->frame.setPosition(centerX - grid_size / 2.f
		, this->background.getPosition().y + this->background.getSize().y / 2.5f);
	this->frame.setFillColor(Color::Transparent);
	this->frame.setOutlineThickness(-2.f);
	this->frame.setOutlineColor(Color(8, 141, 6));


}



TexturePreview::TexturePreview(RenderWindow& window, Texture& texture,
	const IntRect& texture_rect, unsigned grid_size,
	float pos_x, float pos_y, float width, float height)
	:texture(texture) ,TextureRect(texture_rect)
{
	this->InitTexture();
	this->PrevieWindow(window, grid_size, pos_x, pos_y, width, height);
	this->texture_preview.setTexture(&this->texture);
	this->texture_preview.setTextureRect(this->TextureRect);
	this->show = true;

	this->background.setTexture(&this->backround_texture);

}

void TexturePreview::updateVisibilty(unsigned key, const bool keytime, bool& hideButton)
{
	
	if (Keyboard::isKeyPressed(Keyboard::Key(key)) && keytime)
	{
		
		if (this->show == false)
		{
			this->show = true;
			hideButton = false;
		}
		else
		{
			this->show = false;
			hideButton = true;
		}
	}
}

void TexturePreview::update(const IntRect& texture_rect)
{
	this->TextureRect = texture_rect;
	this->texture_preview.setTextureRect(this->TextureRect);
}

void TexturePreview::setTexture(Sprite &sprite)
{
	this->CustomSpritePreview = sprite;
	this->CustomSpritePreview.setPosition(this->texture_preview.getPosition());
}

const RectangleShape& TexturePreview::GetPreviewScreenPos() const
{
	return this->background;
}



void TexturePreview::render(RenderTarget& target, bool renderSpritePreviw)
{

	if (this->show)
	{
		target.draw(this->background);
		target.draw(this->text);
		target.draw(this->frame);
		if (!renderSpritePreviw)
		{
			target.draw(this->texture_preview);
		}
		else
			target.draw(this->CustomSpritePreview);
	}

}
