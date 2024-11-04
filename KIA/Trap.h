#pragma once

#include "Actor.h"

class Trap : public Actor
{
public:
	Trap(string filename, float x, float y, float width, float height, Game* game);
	virtual int damageTaken() = 0;
};

