#pragma once

#include "Actor.h"

class HealthBar : public Actor
{
public:
	HealthBar(string filename, float x, float y, int width, int height, Game* game);

	void draw(float scrollX, float scrollY) override;

	void updateHealth(float currentHealth, float maxHealth);
	float healthPercentage;
	int barWidth;
};

