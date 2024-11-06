#include "Basic.h"

Basic::Basic(float x, float y, Game* game)
	: Enemy("res/alien.png", x, y, 36, 40, game) {

	aDying = new Animation("res/gameRes/enemies/enemigo_morir.png", width, height,
		280, 40, 6, 8, false, game);

	aMovingLeft = new Animation("res/gameRes/enemies/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, true, game);

	aMovingRight = new Animation("res/gameRes/enemies/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, true, game);

	vxIntelligence = -2;
}
