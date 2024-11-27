#pragma once

#include "Attack.h"
#include "Animation.h"

class Sword : public Attack
{
public:
	Sword(float x, float y, Game* game, int orientation);
	void update() override;
	bool canBeDeleted() override;
	void onCollision() override;
	void draw(float scrollX = 0, float scrollY = 0) override;

	int orientation;
	float lifeTime = 5;
	float currentLifeTime = lifeTime;
	Animation* attack;
	Animation* attackRight;
	Animation* attackLeft;
};

