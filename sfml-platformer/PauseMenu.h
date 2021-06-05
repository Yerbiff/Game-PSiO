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

	//std::map<std::string, Button*> buttons;


public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Function
	void update();
	void render(sf::RenderTarget& target);
};

