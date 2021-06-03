#pragma once
class MenuItem
{
private:
	//Variables
	const static int MAX_NUMBER_OF_ITEMS = 0;
	int selectedItemIndex_;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
public:
	MenuItem(sf::RenderWindow* window, const static int MAX_NUMBER_OF_ITEMS,std::string string, int el,sf::Font font);
	virtual ~MenuItem();

	
	//Functions
	int GetPressedItem() { return selectedItemIndex_; }
	void MoveUp();
	void MoveDown();

};

