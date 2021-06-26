#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collison, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	/*this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);*/
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = collison;
	this->type = type;
}

Tile::~Tile()
{
}

const short& Tile::getType() const
{
	return this->type;
}

const bool &Tile::getCollision() const
{
	
	return this->collision;
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::IntRect Tile::getTextureRect() const
{
	return this->shape.getTextureRect();
}

const sf::RectangleShape Tile::getShape() const
{
	return this->shape;
	
}

void Tile::deleteTile()
{
	this->shape.move(10000000,1000000000);
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
