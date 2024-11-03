#pragma once

#include "Item.h"

class BreakableItem : public Item
{
public:
    BreakableItem(float x, float y, Game* game, int r);
    string getSprite(int random);
    int getWidth(int random);
    int getHeight(int random);
    void onCollision() override;  // Sobrescribe el método onCollision
    int random;
};

