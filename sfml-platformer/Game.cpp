#include "stdafx.h"
#include "Game.h"
#include "Menu.h"

Menu menu(500, 700);
void Game::initWindow()
{
	// or sf::VideoMode::getDektopMode
	this->window.create(sf::VideoMode(800, 600), "Game", sf::Style::Close | sf::Style::Titlebar);
	//

}

Game::Game() {
	this->initWindow();
	
}

Game::~Game() {

}

void Game::update()
{
	while (this->window.pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window.close();
		//close on escape 
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window.close();
		else if (this->event.type == sf::Event::KeyPressed)
		{
			switch (this->event.key.code)
			{
			case sf::Keyboard::Up:
				menu.MoveUp();
				break;
			case sf::Keyboard::Down:
				menu.MoveDown();
				break;
			case sf::Keyboard::Return:
				switch (menu.GetPressedItem())
				{
				case 0:
					std::cout << "New" << std::endl;
					break;
				case 1:
					std::cout << "Exit" << std::endl;
					break;
				}
				break;
			}
		}

	}
}

void Game::render()
{
	this->window.clear(sf::Color::Black);

	//Render Game here
	
	menu.draw(this->window);

	// ===

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
