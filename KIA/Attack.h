#pragma once

#include "Actor.h"

class Attack : public Actor
{
public:
	Attack(string filename, float x, float y, int width, int height, Game* game);
	virtual void update() = 0;
	virtual bool canBeDeleted() = 0;
};

