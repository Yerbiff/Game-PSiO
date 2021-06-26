#pragma once

#include "stdafx.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Entity.h"
#include <stack>

class Tile;
class Entity;

enum Item {
	MARCHEWKAX = 320,
	MARCHEWKAY = 960,
	ZIEMNIAKX = 288,
	ZIEMNIAKY = 960,
	PATYKX = 416,
	PATYKY = 800,
	KAMIENX = 864,
	KAMIENY = 800
};

class TileMap
{
private:
	float gridSizeF;
	int gridSizeI;
	int layers;
	std::string textureFile;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	std::stack<Tile*> deferredRenderStack;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	int a;
	int b;
	bool damaging;
	
	//Functions
	void clear();

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;
public:

	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	//Getters
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int z) const;
	const int getA() const;
	const int getB() const;

	//Setters
	virtual void setA(int a);
	virtual void setB(int b);

	//Functions
	void loadFromFile(const std::string file_name);
	void updateCollision(Entity* entity, const float& dt);
	void updateDamaging(Entity* entity);
	int updatePicking(Entity* entity);

	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL);
	void renderDeferred(sf::RenderTarget& target);

	
};

