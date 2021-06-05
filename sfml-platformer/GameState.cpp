#include "stdafx.h"
#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}
void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/arial.ttf"))
	{
		throw("ERROR::Could not load font");
	}
}
void GameState::initTextures()
{
	if(!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/sprite_sheet.png"))
	{
		throw("could not load player texture");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
	this->player->scale(sf::Vector2f(2, 2));
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))//
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);

}

void GameState::update(const float& dt)
{
	this->updateInput(dt);

	if (!this->paused)//unpaused
	{
		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else 
	{
		this->pmenu->update();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player->render(*target);

	if (this->paused)//Pause menu
	{
		this->pmenu->render(*target);
	}
}
