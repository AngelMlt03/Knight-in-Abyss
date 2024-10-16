#include "Goomba.h"

Goomba::Goomba(float x, float y, Game* game)
	: Enemy("res/alien.png", x, y, 36, 40, game) {

	aDying = new Animation("res/goomba_morir.png", width, height,
		39, 17, 6, 2, false, game);

	aMovingLeft = new Animation("res/goomba_movimiento_izquierda.png", width, height,
		211, 17, 6, 11, true, game);

	aMovingRight= new Animation("res/goomba_movimiento_derecha.png", width, height,
		211, 17, 6, 11, true, game);

	vxIntelligence = -3;
}

bool Goomba::isTopOverlap(Actor* actor) {

	bool overlap = false;
	if (actor->x - actor->width / 2 <= x + width / 2
		&& actor->x + actor->width / 2 >= x - width / 2
		&& actor->y + actor->height / 2 >= y - height / 2
		&& actor->y - actor->height / 2 <= y + height / 2
		&& actor->vy > 0) {

		overlap = true;
	}
	return overlap;
}