#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& texture_sheet)
	:texturesheet(texture_sheet), sprite(sprite)
{
	this->texturesheet = texture_sheet;
	this->sprite = sprite;


}

AnimationComponent::~AnimationComponent()
{
	for (auto& e : this->animations)
	{
		delete e.second;
	}
}

void AnimationComponent::AddAnimation(
	const string key,float animationTimer,
	int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height)
{
	this->animations[key] = new animation(
		this->sprite, this->texturesheet,
		animationTimer,
		start_frame_x, start_frame_y, frame_x, frame_y, width, height
	);
}



void AnimationComponent::Play(const string key, const float& dt)
{

	if (this->lastanimation != this->animations[key])
	{
		if (this->lastanimation == NULL)
			this->lastanimation = this->animations[key];
		else
		{
			this->lastanimation->reset();
			this->lastanimation = this->animations[key];
		}
		
	}
	this->animations[key]->play(dt);
}

