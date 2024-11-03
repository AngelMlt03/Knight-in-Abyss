#pragma once

#include "Actor.h"
#include "Audio.h"

class Item : public Actor
{
public:
	Item(string filename, float x, float y, float width, float height, Game* game);

	virtual void onCollision() {}; // Lo que ocurre al colisionar con el item
	Audio* audioOnCollision;
};

