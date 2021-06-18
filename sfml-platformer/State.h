#pragma 

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include "Player.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytime1;
	float keytimeMax;
	float time;
	float time2;

	//Resorces
	std::map<std::string,sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();
	const bool getKeytime1();
	//virtual void endStateUpdate() = 0;

	//Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void timeCounter(const float& dt);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

