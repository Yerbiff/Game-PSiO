#include "stdafx.h"
#include "DeathMenu.h"

void DeathMenu::initDeathMenu(sf::RenderWindow& window)
{
	this->backgroud.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	this->backgroud.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, static_cast<float>(window.getSize().y) - 100.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 30.f);


	this->endText.setFont(font);
	this->endText.setFillColor(sf::Color(255, 255, 255, 200));
	this->endText.setString("THE END");
	this->endText.setCharacterSize(60);
	this->endText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->endText.getGlobalBounds().width / 2.f, this->container.getPosition().y + 20.f);


	this->menu[0].setFont(font);
	this->menu[0].setFillColor(sf::Color(255, 255, 255, 200));
	this->menu[0].setString("You have lived for "+ std::to_string(this->days)+" days");
	this->menu[0].setCharacterSize(40);
	this->menu[0].setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->endText.getGlobalBounds().width / 2.f - 80.f, (window.getSize().y)/3);
	
	this->menu[1].setFont(font);
	this->menu[1].setFillColor(sf::Color::White);
	this->menu[1].setString("Exit");
	this->menu[1].setCharacterSize(40);
	this->menu[1].setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->endText.getGlobalBounds().width / 2.f, (window.getSize().y)/2);


}

DeathMenu::DeathMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	initDeathMenu(window);
	this->days = 0;

}

DeathMenu::~DeathMenu()
{
}

void DeathMenu::setDays(int days)
{
	this->days = days;
	if(this->days > 1)
		this->menu[0].setString("You have survived " + std::to_string(this->days) + " days");
	else
		this->menu[0].setString("You have survived " + std::to_string(this->days) + " day");
}

void DeathMenu::update()
{

}

void DeathMenu::render(sf::RenderTarget& target)
{
	target.draw(this->endText);
	target.draw(this->backgroud);
	target.draw(this->container);

	for(auto& i :menu)
		target.draw(i);

}
