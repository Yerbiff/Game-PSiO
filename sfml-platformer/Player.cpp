#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
}

void Player::initComponents()
{
	this->creatMovmentComponent(200.f);
}

Player::Player(float x, float y, sf::Texture& texture)
{
	initVariables();
	initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{
}
