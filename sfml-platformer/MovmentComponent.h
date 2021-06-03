#pragma once

class MovmentComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;

	sf::Vector2f velocity;
	sf::Vector2f accelaretion;
	sf::Vector2f deceleration;

public:
	MovmentComponent(sf::Sprite& sprite, float maxVelocity);
	virtual ~MovmentComponent();

	const sf::Vector2f& getVelocity() const;

	void move(const float x, const float y,const float& dt);
	void update(const float& dt);
};

