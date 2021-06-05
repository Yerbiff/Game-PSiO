#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
}

void Player::initComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();

	this->setPosition(x, y);

	this->creatMovmentComponent(300.f, 15.f, 5.f);
	this->creatAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 12, 0, 32, 32);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 1 , 7, 1 , 32, 32);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 2, 7, 2, 32, 32);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	this->movmentComponent->update(dt);

	if (this->movmentComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if(this->movmentComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("WALK_RIGHT", dt);
	else if (this->movmentComponent->getState(MOVING_LEFT))
		this->animationComponent->play("WALK_LEFT", dt);
	
}
