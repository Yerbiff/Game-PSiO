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
	void creatMovmentComponent(const float maxVelocity);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt,const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* terget);
};

