#include "stdafx.h"
#include "MovmentComponent.h"

MovmentComponent::MovmentComponent(sf::Sprite& sprite, float maxVelocity): sprite(sprite), maxVelocity(maxVelocity)
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
	this->velocity.x = this->maxVelocity * dir_x;
	this->velocity.y = this->maxVelocity * dir_y;

	this->sprite.move(this->velocity * dt); //use velocity
}

void MovmentComponent::update(const float& dt)
{

}
