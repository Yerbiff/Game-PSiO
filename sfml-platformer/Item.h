#pragma once

enum item_type {
	CRAFTABLE = 0,
	GIVE_HUNGER,
	GIVE_HP,
	TAKE_HUNGER,
	TAKE_HP,
};

class Item
{
private:
	int id;
	sf::Texture texture;
	sf::Sprite sprite;
	short  property;
public:
	Item();
	virtual ~Item();
};

