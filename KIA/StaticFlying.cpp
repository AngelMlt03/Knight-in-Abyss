#include "StaticFlying.h"

StaticFlying::StaticFlying(float x, float y, Game* game)
	: Enemy("res/alien.png", x, y, 36, 40, game) {

	aDying = new Animation("res/gameRes/enemies/goomba_morir.png", width, height,
		39, 17, 6, 2, false, game);

	aMovingLeft = new Animation("res/gameRes/enemies/goomba_movimiento_izquierda.png", width, height,
		211, 17, 6, 11, true, game);

	aMovingRight= new Animation("res/gameRes/enemies/goomba_movimiento_derecha.png", width, height,
		211, 17, 6, 11, true, game);

	vxIntelligence = 0;
}

void StaticFlying::doMove() {

	
}