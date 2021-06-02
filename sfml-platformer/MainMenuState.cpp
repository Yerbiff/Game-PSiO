#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/arial.ttf"))
	{
		throw("ERROR::Could not load font");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("config/mainmenu_keybinds.ini");

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

void MainMenuState::initMenuitems()
{
	this->menu[0].setFont(font);
	this->menu[0].setFillColor(sf::Color::Red);
	this->menu[0].setString("New Game");
	this->menu[0].setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / (MAX_NUMBER_OF_ITEMS + 1.f) * 1));

	this->menu[1].setFont(font);
	this->menu[1].setFillColor(sf::Color::White);
	this->menu[1].setString("Exit");
	this->menu[1].setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / (MAX_NUMBER_OF_ITEMS + 1.f) * 2));

	selectedItemIndex_ = 0;
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initFonts();
	this->initMenuitems();
	

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::MoveUp()
{
	if (selectedItemIndex_ - 1 >= 0)
	{
		menu[selectedItemIndex_].setFillColor(sf::Color::White);
		selectedItemIndex_--;
		menu[selectedItemIndex_].setFillColor(sf::Color::Red);
	}
}
void MainMenuState::MoveDown()
{
	if (selectedItemIndex_ + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex_].setFillColor(sf::Color::White);
		selectedItemIndex_++;
		menu[selectedItemIndex_].setFillColor(sf::Color::Red);
	}
}

void MainMenuState::endState()
{
	std::cout << "ending Mainmanustate";
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkforQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->MoveUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->MoveDown();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ENTER"))))
		switch (this->GetPressedItem())
		{
		case 0:

			//Przejscie do menu z wyborem poziomu trudności
			this->states->push(new GameState(this->window, this->supportedKeys, this->states));
			break;
		case 1:
			this->quit = true; //wyłaczenie aplikacji z menu
			break;
		}



}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		target->draw(this->menu[i]);
	}

}
