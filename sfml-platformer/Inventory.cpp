#include "stdafx.h"
#include "Inventory.h"
#include <iostream>
#include <sstream>



void Inventory::initTextures()
{
	for (int i = 1; i < MAX_NUMBER_OF_TEXTURES; i++)
	{
		if (!this->items_textures[i].loadFromFile("Resources/Images/Sprites/Items/"+std::to_string(i)+".png"))
		{
			throw("Item texture could not load");
		}
		
	}

}

void Inventory::initSprites()
{
	for (int i = 1; i < MAX_NUMBER_OF_TEXTURES; i++)
	{
		
		this->items_sprites[i].setTexture(this->items_textures[i]);
	}
}

void Inventory::initBar(sf::RenderWindow& window)
{
	this->bar.setFillColor(sf::Color(139, 69, 19));
	this->bar.setSize(sf::Vector2f(1300, 100));
	this->bar.setPosition(sf::Vector2f(window.getSize().x / 5.f, window.getSize().y - 150.f));

	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		this->eq_square[i].setFillColor(sf::Color(222, 184, 135));
		this->eq_square[i].setSize(sf::Vector2f(100.f, 80.f));
		this->eq_square[i].setPosition(((window.getSize().x / 15.f) * i) + 400.f, window.getSize().y - 140.f);
	}

	//item in hand square
	eq_square[MAX_NUMBER_OF_ITEM - 1].setFillColor(sf::Color(205, 133, 63));
}

void Inventory::initAmount(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEM - 1; i++)
	{
		this->amount[i].setFont(font);
		this->amount_value.push_back(0);
		this->amount[i].setPosition((((window.getSize().x / 15.f)) * i) + 480.f, window.getSize().y - 140.f);
		this->amount[i].setCharacterSize(15);
		this->amount[i].setFillColor(sf::Color::Black);
		this->amount[i].setString(std::to_string(amount_value[i]));
	}
}

void Inventory::initItems(sf::RenderWindow& window)
{
	//inicialization of items standard all 0's
	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		this->items_eq[i] = 0;
		this->items[i] = items_sprites[items_eq[i]];
	}

	//inicialization of the sword
	this->items_sprites[5].setPosition(((window.getSize().x / 15.f) * 9) + 400.f, window.getSize().y - 140.f);
	this->items_sprites[5].setScale(2.5, 2.5);

}

Inventory::Inventory(sf::RenderWindow& window, sf::Font& font) 
	: font(font)
{
	initTextures();
	initSprites();
	initBar(window);
	initItems(window);
	initAmount(window);
	
	this->selectedItemIndex_ = 0;
}

Inventory::~Inventory()
{
}

void Inventory::addItem(int id)
{
	//Ading item to eq if picking item is not 0
	if (id != 0)
	{
		for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
		{
			//add new item
			if (amount_value[i] == 0)
			{
				amount_value[i] += 1;
				this->amount[i].setString(std::to_string(amount_value[i]));
				this->items_eq[i] = id;
				break;
			}
			//add another item if exist
			else if (amount_value[i] != 0 && this->items_eq[i] == id)
			{
				amount_value[i] += 1;
				this->amount[i].setString(std::to_string(amount_value[i]));
				break;
			}
		}
	}
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

const int Inventory::GetPressedItem() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		return selectedItemIndex_;
}

void Inventory::updatePicking(sf::RenderWindow& window)
{
	//if item is in eq put picture in eq
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

bool Inventory::checkEatable(int id)
{
	if (id == 3 || id == 4)
	{
		return true;
	}
	return false;
}

void Inventory::updateUsing(const float dt, Entity& entity)
{
	//update using item "eating"
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
	{
		switch (this->GetPressedItem())
		{
		case 0:
			if (checkEatable(items_eq[0]))
			{
				this->amount_value[0] -= 1;
				if (this->amount_value[0] <= 0)
					this->amount_value[0] = 0;
				entity.setHp(entity.getHp()+10);
				entity.setHunger(entity.getHunger() + 10);
			
				this->amount[0].setString(std::to_string(amount_value[0]));
			}
			break;
		case 1:
			if (checkEatable(items_eq[1]))
			{
				this->amount_value[1] -= 1;
				if (this->amount_value[1] <= 0)
					this->amount_value[1] = 0;
				entity.setHp(entity.getHp() + 10);
				entity.setHunger(entity.getHunger() + 10);

				this->amount[1].setString(std::to_string(amount_value[1]));
			}
			break;
		case 2:
			if (checkEatable(items_eq[2]))
			{
				this->amount_value[2] -= 1;
				if (this->amount_value[2] <= 0)
					this->amount_value[2] = 0;
			
				entity.setHp(entity.getHp() + 10);
				entity.setHunger(entity.getHunger() + 10);
				this->amount[2].setString(std::to_string(amount_value[2]));
			}
			
			break;
		case 3:
			if (checkEatable(items_eq[3]))
			{
				this->amount_value[3] -= 1;
				if (this->amount_value[3] <= 0)
					this->amount_value[3] = 0;
			
				entity.setHp(entity.getHp() + 10);
				entity.setHunger(entity.getHunger() + 10);
				this->amount[3].setString(std::to_string(amount_value[3]));
			}
			
			break;

		}
		//has to be changed
		if (entity.getHp() >= 100)
			entity.setHp(100);
		if (entity.getHunger() >= 100)
			entity.setHunger(100);
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
{	//drawing bar
	target.draw(this->bar);

	//drawing eq squares
	for(auto& i : eq_square)
		target.draw(i);

	//drawing if this item is in eq
	for (int i = 0; i < MAX_NUMBER_OF_ITEM; i++)
	{
		if (this->amount_value[i] != 0)
		{
			target.draw(items[i]);
		}
	}
	//drawing sword in hand
	target.draw(items_sprites[5]);

	//drawing amount of the items in eq
	for (auto& i : amount)
	{
		target.draw(i);
	}

}
