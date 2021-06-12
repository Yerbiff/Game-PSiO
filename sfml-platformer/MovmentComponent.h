#pragma once

enum movment_states {
	IDLE = 0,
	MOVING,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UP,
	MOVING_DOWN
};

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

	const bool getState(const short unsigned state) const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	void move(const float x, const float y,const float& dt);
	void update(const float& dt);
};

