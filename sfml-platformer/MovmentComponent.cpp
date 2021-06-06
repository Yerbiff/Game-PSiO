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

const bool MovmentComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	}
	return false;
}

void MovmentComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}
void MovmentComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}
void MovmentComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

void MovmentComponent::move(const float dir_x, const float dir_y, const float& dt)//const float& dt
{
	//acceleration
	this->velocity.x += this->accelaretion* dir_x;

	this->velocity.y += this->accelaretion * dir_y;

	
}

void MovmentComponent::update(const float& dt)
{
	//Decelaration
	if (this->velocity.x > 0.f)//Check for positive x
	{
		//Max velocity check positve
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration x positive
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	else if (this->velocity.x < 0.f)//Check for negative x
	{
		//Max velocity check negative
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration x negative
		this->velocity.x += deceleration;
		if(this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	if (this->velocity.y > 0.f)//Check for positive y
	{
		//Max velocity check positve
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration y positive
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	else if (this->velocity.y < 0.f)//Check for negative y
	{
		//Max velocity check negative
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration y negative
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->sprite.move(this->velocity * dt); //use velocity
}
