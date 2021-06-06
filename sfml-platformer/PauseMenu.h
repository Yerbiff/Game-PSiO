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
	int selectedItemIndex_;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	//std::map<std::string, Button*> buttons;


public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Function
	void MoveUp();
	void MoveDown();
	const bool isItemPressed(const int num);
	int GetPressedItem();

	void update();
	void render(sf::RenderTarget& target);
};

