#pragma once

#include "Enemy.h"
#include "GameLayer.h"
class GameLayer;

class FlyingEnemy : public Enemy
{
public:
	FlyingEnemy(float x, float y, Game* game, GameLayer* gl);
	void doMove() override;  // Sobrescribe el metodo

	GameLayer* gameLayer;
	void shoot();
	int shootCadence = 60;
	int shootTime = 0;
};
