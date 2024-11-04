#pragma once

#include "Trap.h"

class Spike : public Trap
{
public:
	Spike(float x, float y, Game* game);
	int damageTaken() override;
};

