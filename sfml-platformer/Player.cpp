#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	atacking = false;
}

void Player::initComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();

	this->setPosition(x, y);

	this->createMovmentComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, 12.f, 16.f, 32.f, 50.f);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 12, 0, 32, 32);
	this->animationComponent->addAnimation("WALK", 8.f, 0, 1 , 7, 1 , 32, 32);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 4, 8, 4, 32, 32);
}

Player::~Player()
{
}

void Player::updateAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		this->atacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->atacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->atacking = false;
	}
	if (this->movmentComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}

	else if (this->movmentComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(2.f, 2.f);
		}
		this->animationComponent->play("WALK", dt);
	}
	else if (this->movmentComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(29.f, 0.f);
			this->sprite.setScale(-2.f, 2.f);
		}
		this->animationComponent->play("WALK", dt);
	}
}

void Player::update(const float& dt)
{

	this->movmentComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);
	
	this->hitboxComponent->update();
}
