#pragma once

#include "Enemy.h"

class StaticFlying : public Enemy
{
public:
	StaticFlying(float x, float y, Game* game);
	void doMove() override;
};


