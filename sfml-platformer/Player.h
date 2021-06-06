#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    bool atacking;
    bool picking;

    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Function
    void updateAttack();
    void updatePick();
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);
};

