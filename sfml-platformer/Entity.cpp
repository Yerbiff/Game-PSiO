#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->movmentSpeed = 100.f;
}

Entity::~Entity()
{
}

void Entity::move(const float& dt,const float dir_x, const float dir_y)
{
	this->shape.move(dir_x * this->movmentSpeed * dt, dir_y * this->movmentSpeed * dt);
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
