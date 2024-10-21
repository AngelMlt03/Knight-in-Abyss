#include "Spell.h"

Spell::Spell(float x, float y, Game* game) :
	Attack("res/disparo_jugador2.png", x, y, 20, 20, game) {
	vx = 9;
	vy = -1; // La gravedad inicial es 1
}

void Spell::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para 
}

bool Spell::canBeDeleted() {
	return vx == 0;
}