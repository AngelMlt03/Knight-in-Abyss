#pragma once

#include "Enemy.h"
#include "Bomb.h"
#include "GameLayer.h"

class Boss1 : public Enemy
{
public:
	Boss1(float x, float y, Game* game, GameLayer* gameLayer);
	void doMove() override;
	void takeDamage();

	int maxHP = 200;
	int currentHP;

	GameLayer* gameL;
	void shoot();
	int shootCadence = 80;
	int shootTime = 0;
};

