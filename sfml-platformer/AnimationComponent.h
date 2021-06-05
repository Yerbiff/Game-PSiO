#pragma once
#include "stdafx.h"
#include <map>


class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		bool done;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect crrRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet ,float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			:sprite(sprite),textureSheet(texture_sheet),timer(0.f), done(false), animationTimer(animation_timer), width(width), height(height)
		{
			this->timer = 0.f;
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->crrRect = this->startRect;
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		const bool& isDone() const 
		{
			return this->done;
		}

		//Functions
		const bool& play(const float& dt)
		{
			//Update
			this->done = false;
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//Reset
				this->timer = 0.f;

				//Animate
				if (this->crrRect != this->endRect)
				{
					this->crrRect.left += this->width;
				}
				else //Reset
				{
					this->crrRect.left = this->startRect.left;
					this->done = true; 
				}

				this->sprite.setTextureRect(this->crrRect);
			}
			return this->done;
		}
		void reset()
		{
			this->timer = 0.f;
			this->crrRect = this->startRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	const bool& isDone(const std::string key);

	//Functions
	void addAnimation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);


	const bool& play(const std::string key, const float& dt, const bool priority = false);
};

