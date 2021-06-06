#pragma once

#include "MovmentComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;

	MovmentComponent* movmentComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
public:
	Entity();
	virtual ~Entity();

	//
	void setTexture(sf::Texture& texture);
	void createMovmentComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);


	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;

	virtual void setPosition(const float x, const float y);
	//Functions
	
	virtual void move(const float x, const float y, const float& dt);
	virtual void scale(sf::Vector2f scale);

	virtual void update(const float& dt = 0);
	virtual void render(sf::RenderTarget& terget) = 0;
};

