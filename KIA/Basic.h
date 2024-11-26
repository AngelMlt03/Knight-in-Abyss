#pragma once

#include "Enemy.h"

class Basic : public Enemy
{
public:
	Basic(float x, float y, Game* game);
	void doMove() override;

	Animation* auxDieLeft;
	Animation* auxDieRight;
};

