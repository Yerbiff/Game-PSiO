#pragma once
#include "stdafx.h"


class DeathMenu
{
private:
	sf::RectangleShape backgroud;
	sf::RectangleShape container;

	sf::Font& font;
	sf::Text endText;
	sf::RectangleShape background;
	int days;
	sf::Text menu[2];

	void initDeathMenu(sf::RenderWindow& window);
public:
	DeathMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~DeathMenu();

	void setDays(int days);

	void update();
	void render(sf::RenderTarget& target);
};

