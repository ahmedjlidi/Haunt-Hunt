#include "stdafx.h"
#include "_3dAudio.h"



_3dAudio::_3dAudio(Sound sound, float radius, float max_volume) : sound(sound), maxVolume(max_volume)
{
	/*this->buffer = *sound.getBuffer();
	this->sound.setBuffer(this->buffer);*/
	this->range.setRadius(radius);
	this->range.setOrigin(this->range.getRadius(), this->range.getRadius());
	this->range.setFillColor(Color(250, 0, 0, 100));
}

const float _3dAudio::getVolume()
{
	return this->sound.getVolume();
}

void _3dAudio::setSound(const Sound& sound)
{
	if (this->sound.getBuffer() != sound.getBuffer())
	{
		this->sound.setBuffer(*sound.getBuffer());
	}
}

const float _3dAudio::getOffset()
{
	
	return  (1 - (this->offset / this->range.getRadius())) * 100.f;
}

//const Vector2f _3dAudio::position()
//{
//	return this->SoundPos;
//}

void _3dAudio::update(Vector2f player_pos, Vector2f sound_pos)
{
	this->range.setPosition(sound_pos);

	if (this->range.getGlobalBounds().contains(player_pos))
	{
		this->offset = sqrt(pow(player_pos.x - this->range.getPosition().x, 2) +
			sqrt(pow(player_pos.y - this->range.getPosition().y, 2)));


		float volume = (1 - (this->offset / this->range.getRadius())) * maxVolume;


		if (volume <= 0)
			volume = 0.f;
		if (volume >= maxVolume)
			volume = maxVolume;

		this->sound.setVolume(volume);

	}
	else
	{
		this->sound.setVolume(0.f);
	}

		
	if (this->sound.getStatus() != sf::Sound::Playing)
	{
		this->sound.play();
	}
	
}

void _3dAudio::render(RenderTarget& target)
{
	target.draw(this->range);
}

void _3dAudio::setVolume(const float volume)
{
	this->sound.setVolume(volume);
}

void _3dAudio::stop()
{
	this->sound.stop();
}

