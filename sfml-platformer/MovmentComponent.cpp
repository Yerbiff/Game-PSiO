#include "stdafx.h"
#include "MovmentComponent.h"

MovmentComponent::MovmentComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), accelaretion(acceleration), deceleration(deceleration)
{
}

MovmentComponent::~MovmentComponent()
{
}

const sf::Vector2f& MovmentComponent::getVelocity() const
{
	return this->velocity;
}

void MovmentComponent::move(const float dir_x, const float dir_y, const float& dt)//const float& dt
{
	//acceleration
	this->velocity.x += this->accelaretion* dir_x;

	if (this->velocity.x > 0.f) //check right
	{
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
	}
	else if (this->velocity.x < 0.f) //check left
	{
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
	}
	this->velocity.y += this->accelaretion * dir_y;

	
}

void MovmentComponent::update(const float& dt)
{
	//Decelaration
	if (this->velocity.x > 0.f)
	{
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)
	{
		this->velocity.x += deceleration;
		if(this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
		

	//Final move
	this->sprite.move(this->velocity * dt); //use velocity
}
