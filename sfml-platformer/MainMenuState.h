#pragma once
#define MAX_NUMBER_OF_ITEMS 2
#include "GameState.h"



class MainMenuState :
    public State
{
private:
	//Variables
	sf::Texture bgTexture;
	sf::Font font;
	sf::RectangleShape background;
	int selectedItemIndex_;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text result;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initMenuitems();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Variables
	

	//Functions
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

//Menu do porawy