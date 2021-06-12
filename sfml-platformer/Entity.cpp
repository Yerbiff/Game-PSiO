#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->movmentComponent = NULL;
	this->hp = 100;
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
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();
	else
		return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPosition(const unsigned gridSizeU) const
{
	if (this->hitboxComponent)
		return sf::Vector2u(static_cast<unsigned>(this->hitboxComponent->getPosition().x) / gridSizeU, static_cast<unsigned>(this->hitboxComponent->getPosition().y) / gridSizeU);
	else
		return sf::Vector2u(static_cast<unsigned>(this->sprite.getPosition().x) / gridSizeU, static_cast<unsigned>(this->sprite.getPosition().y) / gridSizeU);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movmentComponent)
		return this->hitboxComponent->getNextPosition(this->movmentComponent->getVelocity() * dt);

	return sf::FloatRect();
}

void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		return this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movmentComponent)
		this->movmentComponent->move(dir_x, dir_y, dt); //sets velocity
}

void Entity::scale(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

void Entity::stopVelocity()
{
	if (this->movmentComponent)
		this->movmentComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movmentComponent)
		this->movmentComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movmentComponent)
		this->movmentComponent->stopVelocityY();
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget& target)
{

}
