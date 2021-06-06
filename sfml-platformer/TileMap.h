#pragma once

#include "stdafx.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	void clear();
	float gridSizeF;
	int gridSizeI;
	int layers;
	std::string textureFile;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector<std::vector<std::vector<Tile*>>> map;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;
	
	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;
public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	const sf::Texture* getTileSheet() const;

	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& dt);

	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);

	
};

