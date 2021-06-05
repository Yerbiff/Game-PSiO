#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:


    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Function
    virtual void update(const float& dt);
};

