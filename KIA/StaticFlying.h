#pragma once

#include "Enemy.h"
#include "EnemyProjectile.h"
#include "GameLayer.h"
class GameLayer;

class StaticFlying : public Enemy
{
public:
	StaticFlying(float x, float y, Game* game, GameLayer* gl);
	void doMove() override;

	GameLayer* gameL;
	void shoot();
	int shootCadence = 80;
	int shootTime = 0;
};


