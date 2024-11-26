#include "Basic.h"

Basic::Basic(float x, float y, Game* game)
	: Enemy("res/gameRes/enemies/basic_movimiento_izquierda.png", x, y, 37, 50, game) {

	auxDieLeft = new Animation("res/gameRes/enemies/basic_morir_izquierda.png", width, height,
		372, 168, 2, 3, false, game);

	auxDieRight = new Animation("res/gameRes/enemies/basic_morir_derecha.png", width, height,
		372, 168, 2, 3, false, game);

	aMovingLeft = new Animation("res/gameRes/enemies/basic_movimiento_izquierda.png", width, height,
		915, 168, 6, 8, true, game);

	aMovingRight = new Animation("res/gameRes/enemies/basic_movimiento_derecha.png", width, height,
		915, 168, 6, 8, true, game);

	aDying = auxDieLeft;
	vxIntelligence = -2;
	damage = 20;
}

void Basic::doMove() {

	animation = (vx < 0) ? aMovingLeft : aMovingRight; // Se establece la animación al morir
	if (vx < 0) { aDying = auxDieLeft; }
	if (vx > 0) { aDying = auxDieRight; }

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
