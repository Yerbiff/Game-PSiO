#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->movmentComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movmentComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovmentComponent(const float maxVelocity , const float acceleration, const float deceleration)
{
	this->movmentComponent = new MovmentComponent(this->sprite, maxVelocity,acceleration,deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}


const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite.getPosition();
}

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movmentComponent)
	{
		this->movmentComponent->move(dir_x, dir_y, dt); //sets velocity
		
	}
}

void Entity::scale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget& target)
{

	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);

}
