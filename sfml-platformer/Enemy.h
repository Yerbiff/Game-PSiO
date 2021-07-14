#pragma once
#include "Entity.h"

class Enemy :
    public Entity
{
private:
    bool atacking;

    void initVariables();
public:
    Enemy(float x, float y, sf::Texture& texture_sheet);
    virtual ~Enemy();

    //Variables

    //Function
    void updateAnimation(const float& dt);

    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

