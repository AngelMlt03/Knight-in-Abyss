#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int h, int w, Game* game)
	: Actor(filename, x, y, h, w, game) {

	vx = vxIntelligence;
	state = game->stateMoving;
}

void Enemy::update() {

	if (animation == nullptr) {
		animation = aMovingLeft;
	}

	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	doMove();

	if (state == game->stateDying) {
		animation = aDying;
	}
}

void Enemy::doMove() {

	animation = (vx < 0) ? aMovingLeft : aMovingRight;

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}
		if (outRight) {
			// mover hacia la izquierda vx tiene que ser negativa
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
		if (outLeft) {
			// mover hacia la derecha vx tiene que ser positiva
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
	}
	else {
		vx = 0;
	}
}

void Enemy::draw(float scrollX, float scrollY) {
	if (animation != nullptr) {
		animation->draw(x - scrollX, y - scrollY);
	}
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}
