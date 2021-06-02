#pragma once
#include "stdafx.h"

#define MAX_NUMBER_OF_ITEMS 2

class Menu
{
private:
	int selectedItemIndex_;
	sf::Font font;

	sf::Text menu[MAX_NUMBER_OF_ITEMS];

public:
	Menu(float width, float height);
	~Menu();

	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex_; }

	void update();
	void render(sf::RenderWindow& window);

};

