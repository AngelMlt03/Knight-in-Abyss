#include "Boss1.h"

Boss1::Boss1(float x, float y, Game* game, GameLayer* gl)
	: Enemy("res/gameRes/enemies/boss_idle.png", x, y, 253, 296, game) {

	aDying = new Animation("res/gameRes/enemies/goomba_morir.png", width, height,
		39, 17, 6, 2, false, game);

	aMovingLeft = new Animation("res/gameRes/enemies/boss_idle.png", width, height,
		1012, 296, 6, 4, true, game);

	aMovingRight = aMovingLeft;

	vxIntelligence = 0;
	gameL = gl;
	currentHP = maxHP;
	damage = 20;
}

void Boss1::shoot() {

	if (shootTime == 0) {
		shootTime = shootCadence;
		Bomb* bomb = new Bomb(gameL->player->x, gameL->player->y, game);
		//gameL->space->addDynamicActor(bomb);
		gameL->enemyBombs.push_back(bomb);
	}
	else {
		shootTime--;
	}
}

void Boss1::doMove() {

	float xPlayer = gameL->player->x;
	float xDiff = abs(xPlayer - x);

	if (xDiff < 900) {
		shoot();
	}
}

void Boss1::takeDamage(int damage) {
	currentHP = currentHP - damage;
}