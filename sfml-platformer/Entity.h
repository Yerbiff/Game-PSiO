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

	int hp;
	int hunger;

	virtual void setTexture(sf::Texture& texture);
	virtual void createMovmentComponent(const float maxVelocity, const float acceleration, const float deceleration);
	virtual void createAnimationComponent(sf::Texture& texture_sheet);
	virtual void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
public:
	Entity();
	virtual ~Entity();

	//Getters
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2u getGridPosition(const unsigned gridSizeU) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect& getNextPositionBounds(const float& dt) const;
	virtual const int getHp() const;
	virtual const int getHunger() const;

	//Setters
	virtual void setPosition(const float x, const float y);
	virtual void setHp(int hp);
	virtual void setHunger(int hunger);

	//Functions
	virtual void move(const float x, const float y, const float& dt);
	virtual void scale(sf::Vector2f scale);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& terget) = 0;
};

