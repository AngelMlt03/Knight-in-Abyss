#include "Jumper.h"

Jumper::Jumper(float x, float y, Game* game)
	: Enemy("res/alien.png", x, y, 40, 29, game) {

	aDying = new Animation("res/sapo_morir.png", width, height,
		33, 25, 6, 1, false, game);

	aMovingLeft = new Animation("res/sapo_quieto_izquierda.png", width, height,
		37, 27, 6, 1, true, game);

	aJumping = new Animation("res/sapo_saltando_izquierda.png", width, height,
		45, 27, 6, 1, true, game);

	animation = aMovingLeft;

}

void Jumper::doMove() {

	// Establecer velocidad
	if (state != game->stateDying) {

		if (jumpColdDown == 0) {
			vx = -6;
			vy = -14;
			jumpColdDown = 100;
		}
		else if (collisionDown){
			vx = 0;
			animation = aMovingLeft;
		}
		else {
			animation = aJumping;
		}
		jumpColdDown--;
	}
}