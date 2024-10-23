#pragma once

#include "Attack.h"

class Sword : public Attack
{
public:
	Sword(float x, float y, Game* game);
	void update() override;
	bool canBeDeleted() override;

	float lifeTime = 5;
	float currentLifeTime = lifeTime;
};

