#include "StaticFlying.h"

StaticFlying::StaticFlying(float x, float y, Game* game, GameLayer* gl)
	: Enemy("res/alien.png", x, y, 50, 50, game) {

	aDying = new Animation("res/gameRes/enemies/goomba_morir.png", width, height,
		39, 17, 6, 2, false, game);

	aMovingLeft = new Animation("res/gameRes/enemies/staticFlyingEnemy.png", width, height,
		100, 100, 6, 1, true, game);

	aMovingRight = aMovingLeft;

	vxIntelligence = 0;

	gameL = gl;
}

void StaticFlying::shoot() {

	if (shootTime == 0) {
		shootTime = shootCadence;
		EnemyProjectile* shoot1 = new EnemyProjectile(x, y, game, 0);
		gameL->space->addDynamicActor(shoot1);
		gameL->enemyAttacks.push_back(shoot1);
		EnemyProjectile* shoot2 = new EnemyProjectile(x, y, game, 1);
		gameL->space->addDynamicActor(shoot2);
		gameL->enemyAttacks.push_back(shoot2);
		EnemyProjectile* shoot3 = new EnemyProjectile(x, y, game, 2);
		gameL->space->addDynamicActor(shoot3);
		gameL->enemyAttacks.push_back(shoot3);
		EnemyProjectile* shoot4 = new EnemyProjectile(x, y, game, 3);
		gameL->space->addDynamicActor(shoot4);
		gameL->enemyAttacks.push_back(shoot4);
	}
	else {
		shootTime--;
	}
}

void StaticFlying::doMove() {

	shoot();
}