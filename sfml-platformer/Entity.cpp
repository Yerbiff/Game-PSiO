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
}

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::creatMovmentComponent(const float maxVelocity)
{
	this->movmentComponent = new MovmentComponent(this->sprite, maxVelocity);
}


void Entity::setPosition(const float x, const float y)
{

		this->sprite.setPosition(x, y);

}

void Entity::move(const float& dt,const float dir_x, const float dir_y)
{
	if (this->movmentComponent)
	{
		this->movmentComponent->move(dir_x, dir_y, dt); //sets velocity
		
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{

	target->draw(this->sprite);

}
