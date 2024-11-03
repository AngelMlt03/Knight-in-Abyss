#pragma once

#include "Item.h"
#include "Player.h"

class HealthItem : public Item
{
public:
    HealthItem(float x, float y, Game* game, Player* p);
    void onCollision() override;  // Sobrescribe el método onCollision
    Player* player;
};
