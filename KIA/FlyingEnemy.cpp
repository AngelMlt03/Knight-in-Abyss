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

	float xPlayer = gameLayer->player->x;
	float xDiff = abs(xPlayer - x);
	float yPlayer = gameLayer->player->y;
	float yDiff = abs(yPlayer - y);

	if (xDiff < 600 ) {

		if (x < xPlayer - 5) {
			vx = 3;
		}
		else if (x > xPlayer + 5) {
			vx = -3;
		}

		if (yDiff < 300) {
			if (y < yPlayer - 5) {
				vy = 1;
			}
			else if (y > yPlayer + 5) {
				vy = -2;
			}
		}
	}
	else {
		vy = -1;
		vx = 0;
	}
}