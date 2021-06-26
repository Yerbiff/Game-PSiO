#pragma once
#include "stdafx.h"
#define MAX_NUMBER_OF_ITEMS 2

class PauseMenu 
{
private:
	sf::RectangleShape backgroud;
	sf::RectangleShape container;
	sf::Font& font;
	sf::Text pauseText;
	sf::RectangleShape background;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

	int selectedItemIndex_;

	void initPasueMenu(sf::RenderWindow& window);

	const int GetPressedItem() const;
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Function
	void MoveUp();
	void MoveDown();

	const bool isItemPressed(const int num);

	void update();
	void render(sf::RenderTarget& target);
};

