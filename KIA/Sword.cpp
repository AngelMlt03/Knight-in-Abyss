#include "Sword.h"

Sword::Sword(float x, float y, Game* game) :
	Attack("res/disparo_jugador2.png", x, y, 20, 90, game) {
	vx = 0;
	vy = -1; // La gravedad inicial es 1
}

void Sword::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla
	vx = 0;
}

bool Sword::canBeDeleted() {
	
	if (currentLifeTime <= 0) {
		currentLifeTime = lifeTime;
		return true;
	}
	currentLifeTime--;
	return false;
}