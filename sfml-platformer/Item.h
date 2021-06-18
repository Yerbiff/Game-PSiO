#pragma once
class Item
{
	enum item_type {
		CRAFTABLE = 0,
		GIVE_HUNGER,
		GIVE_HP,
		TAKE_HUNGER,
		TAKE_HP,
	};

private:
	int id;
	sf::Texture texture;
	sf::Sprite sprite;
	short  property;



public:
	Item();
	virtual ~Item();
};

