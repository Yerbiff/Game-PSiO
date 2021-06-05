#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) 
	: font(font)
{

	this->backgroud.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	this->backgroud.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, static_cast<float>(window.getSize().y) - 100.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) /2.f - this->container.getSize().x / 2.f, 30.f);

	this->pauseText.setFont(font);
	this->pauseText.setFillColor(sf::Color(255, 255, 255, 200));
	this->pauseText.setString("PAUSED");
	this->pauseText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f, this->container.getPosition().y + 20.f);

}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::update()
{

}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->backgroud);
	target.draw(this->container);

	/*for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		target.draw(this->menu[i]);
	}*/
	target.draw(this->pauseText);
}
