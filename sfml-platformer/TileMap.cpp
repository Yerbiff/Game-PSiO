#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{

				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile*>>());
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}
	if (!this->tileSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
	{
		std::cout << "eror no tile";
	}
	this->collisionBox.setSize(sf::Vector2f(gridSize,gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);

}

TileMap::~TileMap()
{
	this->clear();
}

const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto *z : y)
			{
				if (z != nullptr)
				{
					z->render(target);
					if (z->getCollision()) 
					{
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}
void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file ="";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collison = false;
		short type = 0;

		//Basic
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<unsigned>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x) * gridSize;
		this->maxSizeWorldF.y = static_cast<float>(size.y) * gridSize;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x,std::vector<std::vector<Tile*>>());
		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}
		if (!this->tileSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
		{
			std::cout << "eror no tile";
		}

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collison >> type)
		{
			this->map[x][y][z] = new Tile(x ,y, this->gridSizeF, this->tileSheet, sf::IntRect(trX,trY,this->gridSizeU, this->gridSizeU), collison, type);
		}
	}
	else
	{
		std::cout << "TileMap could not load form file";
	}

	in_file.close();
}

void TileMap::updateCollision(Entity* entity)
{
	//World bounds

	if (entity->getPosition().x < 0.f)
		entity->setPosition(0.f, entity->getPosition().y);
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
	if (entity->getPosition().y < 0.f)
		entity->setPosition(entity->getPosition().x, 0.f);
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
}

