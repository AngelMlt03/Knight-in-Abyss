#pragma once

#include "Attack.h"
#include "Animation.h"

class Spell : public Attack
{
public:
	Spell(float x, float y, Game* game);
	void update() override;
	bool canBeDeleted() override;
	void onCollision() override;
	void draw(float scrollX = 0, float scrollY = 0) override;

	Animation* animation;
	Animation* shoot;
	Animation* explode;
	int deleteTime = 30;
};

