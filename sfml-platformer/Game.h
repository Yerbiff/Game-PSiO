#pragma once

#include "stdafx.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event event;
	void initWindow();


public:

	Game();


	virtual ~Game();

	//Functions
	void update();
	void render();
	const sf::RenderWindow& getWindow() const;

};

