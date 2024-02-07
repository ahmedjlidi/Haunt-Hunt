#include "stdafx.h"
#include "Tile.h"




Tile::Tile(unsigned x, unsigned y, const float GridSize, Texture &texture,
	const IntRect& texture_rect, bool collision, short type): texture(texture)
{
	
	this->shape.setPosition(static_cast<float>(x) * GridSize, static_cast<float>(y) * GridSize);
	this->shape.setTexture(this->texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;

}

Tile::~Tile()
{

}

const string Tile::GetAsString()
{
	stringstream iss;

	iss << this->shape.getTextureRect().left << " "
		<< this->shape.getTextureRect().top << " "
		<< this->collision <<
		" " << this->type;


	return iss.str();
}

const short Tile::GetTypes()
{
	return type;
}

const Vector2f Tile::GetPosition() const
{
	return this->shape.getPosition();
}

const bool Tile::getCollision() const
{
	return this->collision;
}

const bool Tile::Intersects(FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

const FloatRect& Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Tile::setType(const short type)
{
	this->type = type;
}



void Tile::update()
{
}

void Tile::render(RenderTarget& target, Shader* shader, Vector2f Position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", Position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);

	

}

