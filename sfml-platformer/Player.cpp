#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	atacking = false;
	picking = false;
	this->hunger = 100;
}

void Player::initComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();

	this->setPosition(x, y);

	this->createMovmentComponent(175.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, 12.f, 16.f, 32.f, 40.f);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 12, 0, 32, 32);
	this->animationComponent->addAnimation("WALK", 8.f, 0, 1 , 7, 1 , 32, 32);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 4, 8, 4, 32, 31);
	this->animationComponent->addAnimation("PICK", 10.f, 0, 7, 4, 7, 32, 32);
	this->animationComponent->addAnimation("DYING", 10.f, 0, 7, 7, 7, 32, 32);
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

void Player::updatePick()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		this->picking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if ((this->hp != 0))
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

		if (this->picking)
		{
			if (this->animationComponent->play("PICK", dt, true))
				this->picking = false;
		}

		else if (this->movmentComponent->getState(MOVING_RIGHT))
		{
			if (this->sprite.getScale().x < 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
				this->sprite.setScale(1.8, 1.8);
			}
			this->animationComponent->play("WALK", dt);
		}
		else if (this->movmentComponent->getState(MOVING_LEFT))
		{
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(29.f, 0.f);
				this->sprite.setScale(-1.8, 1.8);
			}
			this->animationComponent->play("WALK", dt);
		}
		else if (this->movmentComponent->getState(MOVING_UP))
		{
			this->animationComponent->play("WALK", dt);
		}
		else if (this->movmentComponent->getState(MOVING_DOWN))
		{
			this->animationComponent->play("WALK", dt);
		}
	}
	else 
	{
		this->animationComponent->play("DYING", dt, true);
	}
}

void Player::update(const float& dt)
{

	this->movmentComponent->update(dt);

	this->updateAttack();
	this->updatePick();

	this->updateAnimation(dt);
	
	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
