#include "stdafx.h"
#include "GameState.h"


void GameState::intiView()
{
	//set view on the charecter
	this->view.setSize(sf::Vector2f(675,450));
	this->view.setCenter(sf::Vector2f(1920 / 2.f, 1080 / 2.f));
}

void GameState::initKeybinds()
{
	//Taking keys from file

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

void GameState::initDeathMenu()
{
	this->dmenu = new DeathMenu(*this->window, this->font);
}

void GameState::initPlayers()
{
	this->player = new Player(rand()% 999, rand() % 999, this->textures["PLAYER_SHEET"]);
	this->player->scale(sf::Vector2f(1.8, 1.8));
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(32,100,100,"Resources/Images/Tiles/tilesheet1.png");
	this->tileMap->loadFromFile("text.slmp");
}

void GameState::initEq()
{
	this->eq = new Inventory(*this->window,this->font);
	//load items from file

	//
}

void GameState::initStatus()
{
	this->clock.setPosition(1660, 25);
	this->clock.setFillColor(sf::Color::Yellow);
	this->clock.setRadius(50);
	this->clock.setOutlineColor(sf::Color::Black);
	this->clock.setOutlineThickness(1.f);

	this->health.setPosition(1440, 25);
	this->health.setRadius(50);
	this->health.setOutlineColor(sf::Color::Black);
	this->health.setOutlineThickness(1.f);

	this->hunger.setPosition(1550, 25);
	this->hunger.setFillColor(sf::Color::Magenta);
	this->hunger.setRadius(50);
	this->hunger.setOutlineColor(sf::Color::Black);
	this->hunger.setOutlineThickness(1.f);

	this->day.setFont(font);
	this->day.setFillColor(sf::Color(255, 255, 255, 200));
	this->day.setPosition(1810, 55);

	this->hp.setFont(font);
	this->hp.setFillColor(sf::Color(255, 255, 255, 200));
	this->hp.setString(std::to_string(this->player->getHp()));
	this->hp.setPosition(1470, 55);

	this->hunger_lv.setFont(font);
	this->hunger_lv.setFillColor(sf::Color(255, 255, 255, 200));
	this->hunger_lv.setString(std::to_string(this->player->getHunger()));
	this->hunger_lv.setPosition(1580, 55);

}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->intiView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initDeathMenu();

	this->temp_t = 0;
	this->temp_t2 = 0;
	this->temp_t3 = 0;
	this->days = 1;

	this->initPlayers();
	this->initTileMap();
	this->initEq();
	this->initStatus();

}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->dmenu;
	delete this->player;
	delete this->tileMap;
	delete this->eq;
	
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::updateInput(const float& dt)
{
	//update if pasue manue 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
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
	if (this->player->getHp() == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
	{
		this->endState();
	}
			
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

	//update damaging if on the damaging square(lava)
	if (temp_t == 0)
		temp_t = this->time;
	if (abs(temp_t - this->time) >= 1)
	{
		this->tileMap->updateDamaging(this->player);
		temp_t = 0;
	}
	//if X is clicked and hasnt been clicked in some time pick item from the ground
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && this->getKeytime())
	{
		this->eq->addItem(this->tileMap->updatePicking(this->player));
	}
	
}

void GameState::updateStatus(const float& dt)
{
	//Switching color of circles (hp and day) depends of value
	if (this->player->getHp() <= 0)
		this->player->setHp(0);
	switch (this->player->getHp())
	{
	case 0:
		this->health.setFillColor(sf::Color::Black);
		break;
	case 10:
		this->health.setFillColor(sf::Color(128, 0, 0, 255));
		break;
	case 20:
		this->health.setFillColor(sf::Color(139, 0, 0, 255));
		break;
	case 30:
		this->health.setFillColor(sf::Color(178, 34, 34, 255));
		break;
	case 40:
		this->health.setFillColor(sf::Color(205, 92, 92, 255));
		break;
	case 50:
		this->health.setFillColor(sf::Color(205, 92, 92, 255));
		break;
	case 60:
		this->health.setFillColor(sf::Color(240, 128, 128, 255));
		break;
	case 70:
		this->health.setFillColor(sf::Color(240, 128, 128, 255));
		break;
	case 80:
		this->health.setFillColor(sf::Color(220, 20, 60, 255));
		break;
	case 90:
		this->health.setFillColor(sf::Color(220, 20, 60, 255));
		break;
	case 100:
		this->health.setFillColor(sf::Color(255, 0, 0, 255));
		break;
	}
	switch (static_cast<int>((this->time/4)))
	{
	case 0:
		this->clock.setFillColor(sf::Color(255, 255, 0));
		break;
	case 1:
		this->clock.setFillColor(sf::Color(255, 255, 0));
		break;
	case 2:
		this->clock.setFillColor(sf::Color(255, 255, 0));
		break;
	case 3:
		this->clock.setFillColor(sf::Color(255, 255, 0));
		break;
	case 4:
		this->clock.setFillColor(sf::Color(255, 165, 0));
		break;
	case 5:
		this->clock.setFillColor(sf::Color(255, 165, 0));
		break;
	case 6:
		this->clock.setFillColor(sf::Color(255, 165, 0));
		break;
	case 7:
		this->clock.setFillColor(sf::Color(255, 140, 0));
		break;
	case 8:
		this->clock.setFillColor(sf::Color(255, 140, 0));
		break;
	case 9:
		this->clock.setFillColor(sf::Color(204, 112, 0));
		break;
	}

	this->day.setString("Day " + std::to_string(this->days));

	//updating hunger
	this->hp.setString(std::to_string(this->player->getHp()));
	if (this->player->getHunger() <= 0)
		this->player->setHunger(0);
	if (this->player->getHunger() == 0)
	{
		if (temp_t2 == 0)
			temp_t2 = this->time2;
		if (abs(temp_t2 - this->time2) >= 5)
		{
			this->player->setHp(this->player->getHp() - 5);
			temp_t2 = 0;
		}
	}
	else
	{
		if (this->time2 / 4 >= 2)
		{
			this->player->setHunger(this->player->getHunger() - 10);
			this->time2 = 0;
		}
	}
	this->hunger_lv.setString(std::to_string(this->player->getHunger()));
}

void GameState::updateDay_Night()
{
	//updating day and night
	if (static_cast<int>(this->time) / 4 == 12)
	{
		this->time = 0;
		days++;
		this->temp_t3 = 0;
	}
	if (this->time / 4 <= 9)
	{
		temp_t3 -= time / 60;
		tileMap->setA(3 - temp_t3);
		tileMap->setB(6 - temp_t3);
		if (tileMap->getA() >= 17)
		{
			tileMap->setA(17);
		}
		if (tileMap->getB() >= 20)
		{
			tileMap->setB(20);
		}
	}
	if (this->time / 4 >= 9.0001 && this->time / 4 <= 9.1)
	{
		this->temp_t3 = 0;
	}
	if (this->time / 4 >= 9)
	{
		temp_t3 -= time / 600;


		tileMap->setA(17 + temp_t3);
		tileMap->setB(20 + temp_t3);
		if (tileMap->getA() <= 3)
		{
			tileMap->setA(3);
		}
		if (tileMap->getB() <= 6)
		{
			tileMap->setB(6);
		}
		this->clock.setFillColor(sf::Color(8, 37, 103));;
	}
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

		if (this->getKeytime1())
		{
			this->eq->update(dt);
			this->eq->updateUsing(dt,*this->player);
		}
		
		this->eq->updatePicking(*this->window);
		
		this->updateStatus(dt);

		this->timeCounter(dt);
		 
		this->updateDay_Night();
		
	}
	else 
	{
		this->pmenu->update();
		this->updatePausedItems();

	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (this->player->getHp() != 0)
	{
		if (!target)
			target = this->window;

		target->setView(this->view);

		this->tileMap->render(*target, this->player);

		this->player->render(*target);

		this->tileMap->renderDeferred(*target);

		target->setView(this->window->getDefaultView());//XD

		this->eq->render(*target);

		//rendering status
		target->draw(clock);
		target->draw(health);
		target->draw(hunger);

		target->draw(day);
		target->draw(hp);
		target->draw(hunger_lv);

		target->setView(this->view);

		if (this->paused)//Pause menu
		{
			target->setView(this->window->getDefaultView());
			this->pmenu->render(*target);
		}
		
	}
	else
	{
		//if you died 
		this->dmenu->setDays(this->days);
		target->setView(this->window->getDefaultView());
		this->dmenu->render(*target);
		
	}

}

