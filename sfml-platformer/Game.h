#pragma once

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event event;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initWindow();
	void initKeys();
	void initStates();

	//Functions
	void endAplication();

	//Update
	void updateSFMLEvents();
	void update();
	void updateDt();

	//Render
	void render();
public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	void run();
};

