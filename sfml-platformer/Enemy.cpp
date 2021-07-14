#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	this->atacking = false;
}

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	initVariables();

	this->setPosition(x, y);

	//this->createMovmentComponent(175.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, 12.f, 10.f, 50.f, 60.f);

	this->animationComponent->addAnimation("IDLE", 16.f, 0, 0, 9, 0, 80, 80);
	this->animationComponent->addAnimation("WALK", 8.f, 0, 2, 5, 2, 80, 80);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 4, 8, 4, 32, 31);
	this->animationComponent->addAnimation("DEATH", 16.f, 0, 1, 9, 1, 80, 80);
}

Enemy::~Enemy()
{
}

void Enemy::updateAnimation(const float& dt)
{
	this->animationComponent->play("DEATH", dt);

}

void Enemy::update(const float& dt)
{

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
