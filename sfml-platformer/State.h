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

	//Resorces
	std::map<std::string,sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	//virtual void endStateUpdate() = 0;

	void endState();

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

