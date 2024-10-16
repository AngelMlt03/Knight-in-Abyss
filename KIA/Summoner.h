#pragma once

#include "Enemy.h"
#include "GameLayer.h"

class Summoner : public Enemy
{
public:
	Summoner(float x, float y, Game* game);
	void doMove() override;

	int summonColdDown = 100;

	Animation* auxDieLeft;
	Animation* auxDieRight;
};
