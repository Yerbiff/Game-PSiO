#pragma once

#include "stdafx.h"
#include "Menu.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	Menu* menu;

	void initWindow();
	void initMenu();

public:

	Game();
	virtual ~Game();


	void updateMenu();
	void renderMenu();



	//Functions
	void update();
	void render();
	const sf::RenderWindow& getWindow() const;

};

