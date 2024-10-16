#pragma once

#include "Enemy.h"

class Goomba : public Enemy
{
public:
	Goomba(float x, float y, Game* game);
	bool isTopOverlap(Actor* actor) override;
};


