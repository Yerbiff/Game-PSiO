#pragma once

class MovmentComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float accelaretion;
	float deceleration;

	sf::Vector2f velocity;


public:
	MovmentComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovmentComponent();

	const sf::Vector2f& getVelocity() const;

	void move(const float x, const float y,const float& dt);
	void update(const float& dt);
};

