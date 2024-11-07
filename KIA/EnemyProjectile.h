#pragma once

#include "Attack.h"
#include "Animation.h"

class EnemyProjectile : public Attack
{
public:
	EnemyProjectile(float x, float y, Game* game, int direction);
	void update() override;
	bool canBeDeleted() override;
	void onCollision() override;
	void draw(float scrollX = 0, float scrollY = 0) override;

	void setAnimation();
	int getAWidth(int direction);
	int getAHeight(int direction);

	int direction;
	Animation* animation;
	Animation* shoot;

	int lifeTime = 180;
};

