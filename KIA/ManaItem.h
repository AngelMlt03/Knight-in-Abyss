#pragma once

#include "Item.h"
#include "Player.h"

class ManaItem : public Item
{
public:
    ManaItem(float x, float y, Game* game, Player* p);
    void onCollision() override;  // Sobrescribe el método onCollision
    Player* player;
};
