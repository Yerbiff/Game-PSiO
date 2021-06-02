#pragma once
class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movmentSpeed;

public:
	Entity();
	virtual ~Entity();

	//Functions
	virtual void move(const float& dt,const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* terget);
};

