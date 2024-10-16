#pragma once

#include "Actor.h"

class HealthBar : public Actor
{
public:
	HealthBar();

	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
};

