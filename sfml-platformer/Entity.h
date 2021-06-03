#pragma once

#include "MovmentComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;

	MovmentComponent* movmentComponent;

public:
	Entity();
	virtual ~Entity();

	//
	void setTexture(sf::Texture& texture);
	void creatMovmentComponent(const float maxVelocity, const float acceleration, const float deceleration);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* terget);
};

