#pragma once
#include "stdafx.h"

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

	bool Intersects(const sf::FloatRect& frect);
public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y,float width, float height);
	virtual ~HitboxComponent();

	//Getters
	const sf::Vector2f& getPosition()const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Setters
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);



	void update();
	void render(sf::RenderTarget& target);
};

