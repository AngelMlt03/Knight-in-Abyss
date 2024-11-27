#pragma once

#include "Attack.h"
#include "Animation.h"

class Spell : public Attack
{
public:
	Spell(float x, float y, Game* game, int orientation);
	void update() override;
	bool canBeDeleted() override;
	void onCollision() override;
	void draw(float scrollX = 0, float scrollY = 0) override;

	int orientation;
	Animation* animation;
	Animation* shootRight;
	Animation* shootLeft;
	Animation* explode;
	int deleteTime = 30;
};

