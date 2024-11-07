#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(float x, float y, Game* game, GameLayer* gl)
	: Enemy("res/alien.png", x, y, 40, 29, game) {

	aDying = new Animation("res/gameRes/enemies/sapo_morir.png", width, height,
		33, 25, 6, 1, false, game);

	aMovingLeft = new Animation("res/gameRes/enemies/sapo_quieto_izquierda.png", width, height,
		37, 27, 6, 1, true, game);

	aMovingRight = new Animation("res/gameRes/enemies/sapo_quieto_izquierda.png", width, height,
		37, 27, 6, 1, true, game);

	animation = aMovingLeft;

	gameLayer = gl;

}

void FlyingEnemy::doMove() {

	vy = -1;
	vx = 0;
	float xPlayer = gameLayer->player->x;
	float xDiff = abs(xPlayer - x);

	if (x < xPlayer-5 && xDiff < 600) {
		vx = 5;
	}
	else if (x > xPlayer+5 && xDiff < 600) {
		vx = -5;
	}

	shoot();
}

void FlyingEnemy::shoot() {

	if (shootTime == 0) {
		shootTime = shootCadence;
		EnemyProjectile* shoot = new EnemyProjectile(x, y, game, 2);
		gameLayer->space->addDynamicActor(shoot);
		gameLayer->enemyProjectiles.push_back(shoot);
	}
	else {
		shootTime--;
	}
}