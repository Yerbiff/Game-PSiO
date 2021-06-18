#include "stdafx.h"
#include "Inventory.h"
#include <iostream>
#include <sstream>



void Inventory::initTextures()
{
	for (int i = 1; i < MAX_NUMBER_OF_TEXTURES; i++)
	{
		if (!this->items_textures[i].loadFromFile("Resources/Images/Sprites/Items/"+std::to_string(i)+".png"))
		//if (!this->items_textures[i].loadFromFile("Resources/Images/Sprites/Items/0.png"))
		{
			throw("Item texture could not load");
		}
		
	}
	//this->items_textures[2].loadFromFile("Resources/Images/Sprites/Items/1.png");
	//this->items_textures[19].loadFromFile("Resources/Images/Sprites/Items/2.png");
}
void Inventory::initSprites()
{
	for (int i = 1; i < MAX_NUMBER_OF_TEXTURES; i++)
	{
		
		this->items_sprites[i].setTexture(this->items_textures[i]);
	}
}

Inventory::Inventory(sf::RenderWindow& window, sf::Font& font) 
	: font(font)
{
	initTextures();
	initSprites();

	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		this->items_eq[i] = 0;
		this->items[i] = items_sprites[items_eq[i]];
	}

	this->bar.setFillColor(sf::Color(139, 69, 19));
	this->bar.setSize(sf::Vector2f(1300,100));
	this->bar.setPosition(sf::Vector2f(window.getSize().x / 5.f, window.getSize().y - 150.f));

	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		//this->items_sprites[i].setPosition(sf::Vector2f(50 *(i+1), window.getSize().y - 150.f));
		this->eq_square[i].setFillColor(sf::Color(222, 184, 135));
		this->eq_square[i].setSize(sf::Vector2f(100.f,80.f));
		this->eq_square[i].setPosition(((window.getSize().x / 15.f)* i)+400.f, window.getSize().y - 140.f);
	}
	this->items_sprites[5].setPosition(((window.getSize().x / 15.f) * 9) + 400.f, window.getSize().y - 140.f);
	this->items_sprites[5].setScale(2.5, 2.5);
	for (int i = 0; i < MAX_NUMBER_OF_ITEM - 1; i++)
	{
		switch (this->items_eq[i])
		{
		case 1:
			this->items_sprites[1].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[1].setScale(2.5, 2.5);
			break;
		case 2:
			this->items_sprites[2].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[2].setScale(2.5, 2.5);
			break;
		case 3:
			this->items_sprites[3].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[3].setScale(2.5, 2.5);
			break;
		case 4:
			this->items_sprites[4].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[4].setScale(2.5, 2.5);
			break;
		case 5:
			this->items_sprites[5].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[5].setScale(2.5, 2.5);
			break;
		}
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEM-1; i++)
	{
		this->amount[i].setFont(font);
		this->amount_value.push_back(0);
		this->amount[i].setPosition((((window.getSize().x / 15.f)) * i) + 480.f, window.getSize().y - 140.f);
		this->amount[i].setCharacterSize(15);
		this->amount[i].setFillColor(sf::Color::Black);
		this->amount[i].setString(std::to_string(amount_value[i]));
	}

	eq_square[MAX_NUMBER_OF_ITEM-1].setFillColor(sf::Color(205, 133, 63));
	this->selectedItemIndex_ = 0;
}

Inventory::~Inventory()
{
}

void Inventory::addItem(int id)
{
	if (id != 0)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
		{

			if (amount_value[i] == 0)
			{
				amount_value[i] += 1;
				this->amount[i].setString(std::to_string(amount_value[i]));
				this->items_eq[i] = id;
				break;
			}
			else if (amount_value[i] != 0 && this->items_eq[i] == id)
			{
				amount_value[i] += 1;
				this->amount[i].setString(std::to_string(amount_value[i]));
				break;
				//this->items_eq[i] = id;
			}
		}
	}
}

void Inventory::use(int Key,int id_i , int id_eq)
{
	switch (Key)
	{
	case 19:
		std::cout << "throw out of eq";
		break;
	case 20:
		std::cout << "Use";
		break;
	default:
		break;
	}
	//this->items[id_eq] = 0;

}
void Inventory::open()
{
	this->open_ = true;
}
void Inventory::close()
{
	this->open_ = false;
}

void Inventory::moveLeft()
{
	if (selectedItemIndex_ - 1 >= 0)
	{
		this->eq_square[selectedItemIndex_].setFillColor(sf::Color(222, 184, 135));
		selectedItemIndex_--;
		this->eq_square[selectedItemIndex_].setFillColor(sf::Color(255, 255, 255, 50));
	}
}

void Inventory::moveRight()
{
	if (selectedItemIndex_ + 1 < MAX_NUMBER_OF_ITEM-1)
	{
		this->eq_square[selectedItemIndex_].setFillColor(sf::Color(222, 184, 135));
		selectedItemIndex_++;
		this->eq_square[selectedItemIndex_].setFillColor(sf::Color(255, 255, 255, 50));
	}
}
int Inventory::GetPressedItem()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		return selectedItemIndex_;
}
void Inventory::updatePicking(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEM - 1; i++)
	{
		this->items[i] = items_sprites[items_eq[i]];
		switch (this->items_eq[i])
		{
		case 1:
			
			this->items_sprites[1].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[1].setScale(2.5, 2.5);
			break;
		case 2:
			this->items_sprites[2].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[2].setScale(2.5, 2.5);
			break;
		case 3:
			this->items_sprites[3].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[3].setScale(2.5, 2.5);
			break;
		case 4:
			this->items_sprites[4].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[4].setScale(2.5, 2.5);	
			break;
		case 5:
			this->items_sprites[5].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
			this->items_sprites[5].setScale(2.5, 2.5);
			break;
		}
	}
}
void Inventory::updateUsing(const float dt, Entity& entity)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
	{
		switch (this->GetPressedItem())
		{
		case 0:
			this->amount_value[0] -= 1;
			if (this->amount_value[0] <= 0)
				this->amount_value[0] = 0;

			this->amount[0].setString(std::to_string(amount_value[0]));
			//this->items_eq[0];
			break;
		case 1:
			this->amount_value[1] -= 1;
			if (this->amount_value[1] <= 0)
				this->amount_value[1] = 0;

			this->amount[1].setString(std::to_string(amount_value[1]));
			//this->items_eq[0];
			break;
		case 2:
			this->amount_value[2] -= 1;
			if (this->amount_value[2] <= 0)
				this->amount_value[2] = 0;

			this->amount[2].setString(std::to_string(amount_value[2]));
			//this->items_eq[0];
			break;
		case 3:
			this->amount_value[3] -= 1;
			if (this->amount_value[3] <= 0)
				this->amount_value[3] = 0;

			this->amount[3].setString(std::to_string(amount_value[3]));
			//this->items_eq[0];
			break;

		}
		
		entity.hp += 10;
		entity.hunger += 10;
		if (entity.hp >= 100)
			entity.hp = 100;
		if (entity.hunger >= 100)
			entity.hunger = 100;
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEM - 1; i++)
	{
		if (this->amount_value[i] == 0)
		{
			this->items_eq[i] = 0;
			this->items[i] = items_sprites[this->items_eq[i]];
		}
	}
}

void Inventory::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->moveRight();
	

}

void Inventory::render(sf::RenderTarget& target)
{
	target.draw(this->bar);
	for(auto& i : eq_square)
		target.draw(i);
	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		if (this->amount_value[i] != 0)
		{
			target.draw(items[i]);
			/*for (auto& i : items_sprites)
			{
				target.draw(i);
			}*/
			//target.draw(items_sprites[i+1]);
		}
	}
	target.draw(items_sprites[5]);

	for (auto& i : amount)
	{
		target.draw(i);
	}

}
