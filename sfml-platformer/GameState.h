#pragma once

#include "State.h"
#include "Entity.h"
#include "PauseMenu.h"

class GameState :
	public State
{
private:
	sf::Font font;
	PauseMenu* pmenu;
	Player* player;
	//sf::Texture texture;

	//Functions
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

