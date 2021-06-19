#include "stdafx.h"
#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
void TileMap::clear()
{
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				for (int k = 0; k < this->map[x][y][z].size(); k++)
				{
					delete this->map[x][y][z][k];
					this->map[x][y][z][k] = nullptr;
				}
				this->map[x][y][z].clear();
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;
	this->damaging = false;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
	this->a = 15;
	this->b = 20;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector < std::vector<Tile*>>());
			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector <Tile*>() );
			}
		}
	}
	if (!this->tileSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
	{
		std::cout << "eror no tile";
	}
	//this->collisionBox.setSize(sf::Vector2f(gridSize,gridSize));
	//this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	//this->collisionBox.setOutlineColor(sf::Color::Red);
	//this->collisionBox.setOutlineThickness(1.f);

}

TileMap::~TileMap()
{
	this->clear();
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->map.size())
	{
		if (y >= 0 && y < this->map[x].size())
		{
			if (layer >= 0 && layer < this->map[x][y].size())
			{
				return this->map[x][y][layer].size();
			}
		}
	}
	return -1;
}

void TileMap::update()
{
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collison = false;
		short type = 0;

		//Basic
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x) * gridSize;
		this->maxSizeWorldF.y = static_cast<float>(size.y) * gridSize;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector < std::vector<Tile*>>());
				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector < Tile*>());
				}
			}
		}
		if (!this->tileSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
		{
			std::cout << "eror no tile";
		}

		//Load all tiles
		//int j = 0;
		while (in_file >> x >> y >> z >> trX >> trY >> collison >> type)
		{
			//this->texture_x_y[j] = std::to_string(trX);
			this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), collison, type));
			
			//j++;
		}
	}
	else
	{
		std::cout << "TileMap could not load form file";
	}

	in_file.close();
}

//void TileMap::updateNight()
//{
//	for (int x = this->fromX; x < this->toX; x++)
//	{
//		for (int y = this->fromY; y < this->toY; y++)
//		{
//			for (int k = 0; k < map[x][y][this->layer].size(); k++)
//			{
//				
//				this->map[x][y][this->layer][k]->getShape().setFillColor(sf::Color(255,255,255,50));
//					
//			}
//
//		}
//	}
//}

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	//World bounds

	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();

	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//Tilles
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - this->a;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + this->b;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - this->a;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + this->b;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y - 1;

	

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for(int k = 0; k < map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (map[x][y][this->layer][k]->getCollision() && map[x][y][this->layer][k]->intersects(nextPositionBounds))
				{
					//bottom collison
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}
					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}
					//Right collison
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - wallBounds.width, playerBounds.top);
					}
					//left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height> wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}

		}
	}
}

void TileMap::updateDamaging(Entity* entity)
{
	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds;
				if(this->map[x][y][this->layer][k]->getType() == TileTypes::DAMAGING)
					wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				//sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (playerBounds.intersects(wallBounds))
				{
					entity->hp -= 10;;
				}
			}

		}
	}
}
int TileMap::updatePicking(Entity* entity)
{
	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (int k = 0; k < map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds;
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::PICKABLE)
					wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				//sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (playerBounds.intersects(wallBounds) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
				{
				
					this->map[x][y][this->layer][k]->deleteTile();
					switch (this->map[x][y][this->layer][k]->getTextureRect().left)
					{
					case MARCHEWKAX:
						if (this->map[x][y][this->layer][k]->getTextureRect().top == MARCHEWKAY)
						{
										
							return 3;
						}
						break;
					case ZIEMNIAKX:
						if (this->map[x][y][this->layer][k]->getTextureRect().top == ZIEMNIAKY)
						{
										
							return 4;
						}
						break;
					case PATYKX:
						if (this->map[x][y][this->layer][k]->getTextureRect().top == PATYKY)
						{
										
							return 1;
						}
						break;
					case KAMIENX:
						if (this->map[x][y][this->layer][k]->getTextureRect().top == KAMIENY)
						{
										
							return 2;
						}
						break;
					}
					

				}
			}
		}
	}
	return 0;
}



void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	if (entity)
	{
		this->layer = 0;

		this->fromX = entity->getGridPosition(this->gridSizeI).x - this->a;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeWorldGrid.x)
			this->fromX = this->maxSizeWorldGrid.x;

		this->toX = entity->getGridPosition(this->gridSizeI).x + this->b;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeWorldGrid.x)
			this->toX = this->maxSizeWorldGrid.x;

		this->fromY = entity->getGridPosition(this->gridSizeI).y - this->a;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeWorldGrid.y)
			this->fromY = this->maxSizeWorldGrid.y;

		this->toY = entity->getGridPosition(this->gridSizeI).y + this->b;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeWorldGrid.y)
			this->toY = this->maxSizeWorldGrid.y;


		for (int x = this->fromX; x < this->toX; x++)
		{
			for (int y = this->fromY; y < this->toY; y++)
			{
				for (int k = 0; k < map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType() == TileTypes::DOODAD)
					{
						this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
						//this->damaging = false;
					}
					else
					{
						this->map[x][y][this->layer][k]->render(target);
						//this->damaging = false;
					}
					if (map[x][y][this->layer][k]->getCollision())
					{
						this->collisionBox.setPosition(map[x][y][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
	else 
	{
		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto &z : y)
				{
					for (auto *k : z)
					{
						k->render(target);
						if (k->getCollision()) 
						{
							this->collisionBox.setPosition(k->getPosition());
							target.draw(this->collisionBox);
						}
					}
				}
			}
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target)
{
	while (!this->deferredRenderStack.empty())
	{
		deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}
