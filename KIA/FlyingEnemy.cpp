#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(float x, float y, Game* game, GameLayer* gl)
	: Enemy("res/alien.png", x, y, 50, 50, game) {

	aDying = new Animation("res/gameRes/enemies/sapo_morir.png", width, height,
		33, 25, 6, 1, false, game);

	aMovingLeft = new Animation("res/gameRes/enemies/flyingEnemy_izquierda.png", width, height,
		204, 50, 6, 4, true, game);

	aMovingRight = new Animation("res/gameRes/enemies/flyingEnemy_derecha.png", width, height,
		204, 50, 6, 4, true, game);

	animation = aMovingLeft;
	orientation = game->orientationLeft;
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
			animation = aMovingRight;
		}
		else if (x > xPlayer + 5) {
			vx = -3;
			animation = aMovingLeft;
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