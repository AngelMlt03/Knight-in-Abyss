#pragma once

#include "Actor.h"

class HealthBar : public Actor
{
public:
	HealthBar(Game* game);

	void updateHealth(float currentHealth, float maxHealth);
	float healthPercentage;
};

