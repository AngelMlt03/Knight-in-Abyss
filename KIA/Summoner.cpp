#include "Summoner.h"

Summoner::Summoner(float x, float y, Game* game)
	: Enemy("res/alien.png", x, y, 37, 50, game) {

	aMovingLeft = new Animation("res/summoner_movimiento_izquierda.png", width, height,
		915, 168, 6, 8, true, game);
	aMovingRight = new Animation("res/summoner_movimiento_derecha.png", width, height,
		915, 168, 6, 8, true, game);

	auxDieLeft = new Animation("res/summoner_morir_izquierda.png", width, height,
		372, 168, 6, 3, false, game);
	auxDieRight = new Animation("res/summoner_morir_derecha.png", width, height,
		373, 168, 6, 3, false, game);
	aDying = auxDieLeft;

	vxIntelligence = -1;
}

void Summoner::doMove() {

	animation = (vx < 0) ? aMovingLeft : aMovingRight; // Se establece la animación al morir
	if (vx < 0) { aDying = auxDieLeft; }
	if (vx > 0) { aDying = auxDieRight; }

	GameLayer* gameLayer = dynamic_cast<GameLayer*>(game->gameLayer);

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}

		if (summonColdDown == 0) {
			gameLayer->summonNewEnemy(x, y); // Invoca a un nuevo enemigo
			summonColdDown = 100; // Ciclos hasta una nueva invocación
		}
		summonColdDown--;
	}
	else {
		vx = 0;
	}
}