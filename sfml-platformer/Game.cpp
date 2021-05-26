#include "stdafx.h"
#include "Game.h"
#include "Menu.h"

void Game::initWindow()
{
	// or sf::VideoMode::getDektopMode
	this->window.create(sf::VideoMode(800, 600), "Game", sf::Style::Close | sf::Style::Titlebar);
	//

}

void Game::initMenu()
{
	this->menu = new Menu(window.getSize().x, window.getSize().y);
}

Game::Game() {
	this->initWindow();
	this->initMenu();

}

Game::~Game() {
	delete this->menu;
}

void Game::updateMenu()
{
	menu->update();
}

void Game::renderMenu()
{
	menu->render(this->window);
}

void Game::update()
{
	while (this->window.pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed)
			this->window.close();
		//close on escape 
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window.close();
		this->updateMenu();


	}
}

void Game::render()
{
	this->window.clear(sf::Color::Black);

	//Render Game here

	this->renderMenu();

	// ===

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
