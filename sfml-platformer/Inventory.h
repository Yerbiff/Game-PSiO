#pragma once
#include "stdafx.h"
#include <vector>
#include "Entity.h"

#define MAX_NUMBER_OF_ITEM 10
#define MAX_NUMBER_OF_TEXTURES 6

class Inventory : public Entity
{
private:
	sf::RectangleShape bar;
	sf::RectangleShape eq_square[MAX_NUMBER_OF_ITEM];
	sf::Sprite items_sprites[MAX_NUMBER_OF_TEXTURES];
	sf::Texture items_textures[MAX_NUMBER_OF_TEXTURES];
	sf::Font& font;

	std::map < int , int> items_eq;
	std::map < int, sf::Sprite> items;
	sf::Text amount[MAX_NUMBER_OF_ITEM];

	std::vector<int> amount_value;
	int selectedItemIndex_;

	void initTextures();
	void initSprites();
	void initBar(sf::RenderWindow& window);
	void initAmount(sf::RenderWindow& window);
	void initItems(sf::RenderWindow& window);

public:
	Inventory(sf::RenderWindow& window, sf::Font& font);//add player later to load items
	virtual ~Inventory();

	void addItem(int id);
	void moveLeft();
	void moveRight();

	int GetPressedItem();

	void updatePicking(sf::RenderWindow& window);
	void updateUsing(const float dt, Entity& entity);
	bool checkEatable(int id);

	void update(const float& dt);
	void render(sf::RenderTarget& target);


};
