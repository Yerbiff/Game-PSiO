#pragma once

#include "State.h"
#include "Entity.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "Inventory.h"
#include "DeathMenu.h"

class PauseMenu;
class Player;
class TileMap;
class Inventory;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
	public State
{
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	std::vector<sf::CircleShape> status;
	sf::CircleShape clock;
	sf::CircleShape health;
	sf::CircleShape hunger;
	std::vector<sf::Text> status_text;
	sf::Text hp;
	sf::Text hunger_lv;
	sf::Text day;

	int temp_t;
	int temp_t2;
	float temp_t3;
	int days;

	sf::Font font;
	PauseMenu* pmenu;
	Player* player;
	Inventory* eq;
	DeathMenu* dmenu;

	TileMap* tileMap;
	//sf::Texture texture;

	//Functions
	void intiView();
	void initStatus();
	void initEq();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();
	void initDeathMenu();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePausedItems();
	void updateTileMap(const float& dt);
	void updateStatus(const float& dt);
	void updateDay_Night();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

