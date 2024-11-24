#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(float x, float y, Game* game, int direction) :
	Attack("res/gameRes/enemies/enemyProjectile3.png", x, y, getAWidth(direction), getAHeight(direction), game) {

	this->direction = direction;
	damage = 10;
	vy = -1;
	setAnimation();
}

void EnemyProjectile::setAnimation() {
	switch (direction)
	{
		// Proyectil hacia arriba
		case 0: {
			shoot = new Animation("res/gameRes/enemies/enemyProjectile0.png",
				width, height, 90, 52, 6, 3, true, game);
			break;
		}
		// Proyectil hacia la derecha
		case 1: {
			shoot = new Animation("res/gameRes/enemies/enemyProjectile1.png",
				width, height, 156, 30, 6, 3, true, game);
			break;
		}
		// Proyectil hacia abajo
		case 2: {
			shoot = new Animation("res/gameRes/enemies/enemyProjectile2.png",
				width, height, 90, 52, 6, 3, true, game);
			break;
		}
		// Proyectil hacia la izquierda
		case 3: {
			shoot = new Animation("res/gameRes/enemies/enemyProjectile3.png",
				width, height, 156, 30, 6, 3, true, game);
			break;
		}
	}
	animation = shoot;
}

int EnemyProjectile::getAWidth(int direction) {
	switch (direction)
	{
		// Proyectiles arriba y abajo
		case 0:
		case 2: {
			return 30;
		}
		// Proyectiles derecha e inzquierda
		case 1:
		case 3: {
			return 52;
		}
	}
}

int EnemyProjectile::getAHeight(int direction) {
	switch (direction)
	{
		// Proyectiles arriba y abajo
		case 0:
		case 2: {
			return 52;
		}
		// Proyectiles derecha e inzquierda
		case 1:
		case 3: {
			return 30;
		}
	}
}

void EnemyProjectile::update() {

	if (vx == 0 && vy == 0) {
		return;
	}

	animation->update();

	switch (direction)
	{
		// Proyectil hacia arriba
		case 0: {
			vy = -4;
			break;
		}
		// Proyectil hacia la derecha
		case 1: {
			vy = -1;
			vx = 3;
			break;
		}
		// Proyectil hacia abajo
		case 2: {
			vy = 2;
			break;
		}
		// Proyectil hacia la izquierda
		case 3: {
			vy = -1;
			vx = -3;
			break;
		}
	}

	if (lifeTime > 0) {
		lifeTime--;
	}
}

bool EnemyProjectile::canBeDeleted() {
	return (vx == 0 && vy == 0) || lifeTime == 0;
}

void EnemyProjectile::onCollision() {
	vx = 0;
	vy = 0;
}

void EnemyProjectile::draw(float scrollX, float scrollY) {

	animation->draw(x - scrollX, y - scrollY);
}