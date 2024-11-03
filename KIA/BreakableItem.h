#pragma once

#include "Item.h"

class BreakableItem : public Item
{
public:
    BreakableItem(float x, float y, Game* game);
    string getSprite();
    void onCollision() override;  // Sobrescribe el método onCollision
};

