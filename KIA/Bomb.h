#pragma once

#include "Attack.h"
#include "Animation.h"

class Bomb : public Attack
{
public:
	Bomb(float x, float y, Game* game);
	void update() override;
	bool canBeDeleted() override;
	void onCollision() override;
	void draw(float scrollX = 0, float scrollY = 0) override;

	Animation* animation;
	Animation* explode;
	Animation* bomb;
	int explodeTime = 60;
	int lifeTime = 100;
};

