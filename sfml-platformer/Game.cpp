#include "stdafx.h"
#include "Game.h"
//#include "Menu.h"


//Initialization

void Game::initWindow()
{
	//creates a sfml window from window.ini file

	std::ifstream ifs("config/window.ini");
	
	std::string title = "None";
	sf::VideoMode window_bounds(800, 600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);


}

void Game::initKeys()
{
	std::ifstream ifs("config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}
	
	ifs.close();

}

void Game::initStates()
{ 
	
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
	
}



//Constructors/Destructors

Game::Game() {
	this->initWindow();
	this->initKeys();
	this->initStates();
	
	//this->initMenu();
}

Game::~Game() {
	//delete this->menu;
	delete this->window;
	while (this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
void Game::endAplication()
{

}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window->close();
		//close on escape 
		//else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			//this->window->close();
		//this->updateMenu();

	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty() && this->window->hasFocus())
	{
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Aplication end
	else
	{
		this->endAplication();
		this->window->close();
	}

}

void Game::updateDt()
{
	//Updates the dt variable with time it take to update and render one frame 

	this->dt = this->dtClock.restart().asSeconds();
}

void Game::render()
{
	this->window->clear(sf::Color(21,108,153,255));

	//Render Game here
	if (!this->states.empty())
		this->states.top()->render(this->window);

	// ===

	this->window->display();
}

void Game::run() 
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();

	}
}
