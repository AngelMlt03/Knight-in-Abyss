#pragma once

#include "Enemy.h"

class Jumper : public Enemy
{
public:
	Jumper(float x, float y, Game* game);
	void doMove() override;  // Sobrescribe el metodo

	int jumpColdDown = 100;

	Animation* aJumping;
	Animation* aRunningRight;

};
