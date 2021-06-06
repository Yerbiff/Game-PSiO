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


	this->menu[0].setFont(font);
	this->menu[0].setFillColor(sf::Color::White);
	this->menu[0].setString("Continue");
	this->menu[0].setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f, window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1.f) * 1);

	this->menu[1].setFont(font);
	this->menu[1].setFillColor(sf::Color(128, 128, 128, 200));
	this->menu[1].setString("Quit");
	this->menu[1].setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f, window.getSize().y / (MAX_NUMBER_OF_ITEMS + 1.f) * 2);

	selectedItemIndex_ = 0;
}

PauseMenu::~PauseMenu()
{
}
void PauseMenu::MoveUp()
{
	if (selectedItemIndex_ - 1 >= 0)
	{
		menu[selectedItemIndex_].setFillColor(sf::Color(128, 128, 128, 200));
		selectedItemIndex_--;
		menu[selectedItemIndex_].setFillColor(sf::Color::White);
	}
}
void PauseMenu::MoveDown()
{
	if (selectedItemIndex_ + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex_].setFillColor(sf::Color(128, 128, 128, 200));
		selectedItemIndex_++;
		menu[selectedItemIndex_].setFillColor(sf::Color::White);
	}
}
const bool PauseMenu::isItemPressed(const int num)
{
	return num == this->GetPressedItem();
}
int PauseMenu::GetPressedItem()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		return selectedItemIndex_;
}
void PauseMenu::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		this->MoveUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		this->MoveDown();
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->backgroud);
	target.draw(this->container);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		target.draw(this->menu[i]);
	}
	target.draw(this->pauseText);
}
