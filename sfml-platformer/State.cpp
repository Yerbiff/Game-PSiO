#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->death = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytime1 = 0.f;
	this->keytimeMax = 50.f;
	this->time = 0;
	this->time2 = 0;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const bool State::getKeytime1()
{
	if (this->keytime1 >= this->keytimeMax)
	{
		this->keytime1 = 0.f;
		return true;
	}
	return false;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::DeathState()
{
	this->death = true;
}

void State::timeCounter(const float& dt)
{
	this->time2 += 1.f * dt;
	this->time += 1.f * dt;
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
	{
		this->keytime += 100.f * dt;
	}
	if (this->keytime1 < this->keytimeMax)
	{
		this->keytime1 += 100.f * dt;
	}
}

