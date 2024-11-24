#include "Sword.h"

Sword::Sword(float x, float y, Game* game) :
	Attack("res/gameRes/player/disparo_jugador2.png", x, y, 160, 150, game) {
	vx = 0;
	vy = -1; // La gravedad inicial es 1
	damage = 50;
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

void Sword::onCollision() {

}