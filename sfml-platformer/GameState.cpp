#include "stdafx.h"
#include "GameState.h"


void GameState::intiView()
{
	this->view.setSize(sf::Vector2f(960,500));
	this->view.setCenter(sf::Vector2f(1920 / 2.f, 1080 / 2.f));
}

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
	this->player->scale(sf::Vector2f(1.8, 1.8));
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(32,100,100,"Resources/Images/Tiles/tilesheet1.png");
	this->tileMap->loadFromFile("text.slmp");
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->intiView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
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

void GameState::updatePausedItems()
{
	if (this->pmenu->isItemPressed(1))
	{
		this->endState();
	}
	else if (this->pmenu->isItemPressed(0))
	{
		this->unpauseState();
	}
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player, dt);
}

void GameState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateKeytime(dt);

	if (!this->paused)//unpaused
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt);
	}
	else 
	{
		this->pmenu->update();
		this->updatePausedItems();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);

	this->tileMap->render(*target, this->player);

	this->player->render(*target);

	if (this->paused)//Pause menu
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
}
