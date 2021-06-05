#pragma once

#include "MovmentComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;

	MovmentComponent* movmentComponent;
	AnimationComponent* animationComponent;
public:
	Entity();
	virtual ~Entity();

	//
	void setTexture(sf::Texture& texture);
	void creatMovmentComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void creatAnimationComponent(sf::Texture& texture_sheet);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float& dt);
	virtual void scale(sf::Vector2f scale);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* terget);
};

