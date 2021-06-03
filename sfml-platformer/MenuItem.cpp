#include "stdafx.h"
#include "MenuItem.h"

MenuItem::MenuItem(sf::RenderWindow* window, const static int MAX_NUMBER_OF_ITEMS,std::string string,int el, sf::Font font)
{
	for (int i = 0; i < el; i++)
	{
		sf::Color kolor;
		if (i == 0)
			kolor = sf::Color::Red;
		else
			kolor = sf::Color::White;
		this->menu[i].setFont(font);
		this->menu[i].setScale(2, 2);
		this->menu[i].setFillColor(kolor);
		this->menu[i].setString(string);
		this->menu[i].setPosition(sf::Vector2f(window->getSize().x / 10.f, window->getSize().y / (MAX_NUMBER_OF_ITEMS + 1.f) * i+1));
	}
	selectedItemIndex_ = 0;
}

MenuItem::~MenuItem()
{
}

void MenuItem::MoveUp()
{
	if (selectedItemIndex_ - 1 >= 0)
	{
		menu[selectedItemIndex_].setFillColor(sf::Color::White);
		selectedItemIndex_--;
		menu[selectedItemIndex_].setFillColor(sf::Color::Red);
	}
}
void MenuItem::MoveDown()
{
	if (selectedItemIndex_ + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex_].setFillColor(sf::Color::White);
		selectedItemIndex_++;
		menu[selectedItemIndex_].setFillColor(sf::Color::Red);
	}
}