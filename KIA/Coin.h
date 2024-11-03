#pragma once

#include "Item.h"
#include "GameLayer.h"

class Coin : public Item
{
public:
    Coin(float x, float y, Game* game, GameLayer* gl);
    void onCollision() override;  // Sobrescribe el método onCollision
    GameLayer* gameLayer;
};
