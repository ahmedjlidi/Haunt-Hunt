#pragma once


class AnimationComponent
{
private:
	class animation
	{

	private:
		

	public:
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		bool done;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;


		animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
			float animation_timer,
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet),
			animationTimer(animation_timer), timer(0.f), done(false),
			width(width), height(height)
		{
			this->timer = 0;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setScale(2.f, 2.f);
			// Set initial texture rect for the sprite
			this->sprite.setTextureRect(this->startRect);
		}

		
		void play(const float& dt) 
		{
			
			this->timer += 100.f * dt; //declare delay between every animation aka animation speed
			if (this->timer >= animationTimer)
			{

				this->timer = 0.f; //reset timer

				/*if (this->currentRect.left == this->endRect.left &&
					this->currentRect.height != this->endRect.height)
				{
					this->currentRect.top += height;
				}*/
				if (this->currentRect != this->endRect)
				{
					//animate
					this->currentRect.left += width;
				}
				else
				{
					this->currentRect.left = this->startRect.left;
					//reset

				}


				this->sprite.setTextureRect(this->currentRect);

			}

		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		
		}
		

	};

	Sprite& sprite;
	Texture& texturesheet;
	map<string, animation*> animations;
	animation* lastanimation;
public:
	AnimationComponent(Sprite &sprite, Texture &texture_sheet);
	virtual ~AnimationComponent();
	void AddAnimation(const string key,float animationTimer,
		int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height);
	void Play(const string key,const float &dt);
	
	
};

