#pragma once
#define MAX_NUMBER_OF_ITEMS 2
#include "GameState.h"


class MainMenuState :
    public State
{
private:
	//Variables
	sf::Font font;
	sf::RectangleShape background;
	int selectedItemIndex_;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

	//Functions
	void initFonts();
	void initKeybinds();
	void initMenuitems();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Variables
	int GetPressedItem() { return selectedItemIndex_; }

	//Functions
	void MoveUp();
	void MoveDown();

	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

