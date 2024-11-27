#include "Sword.h"

Sword::Sword(float x, float y, Game* game, int orientation) :
	Attack("res/gameRes/player/espada_derecha.png", x, y, 118, 40, game) {
	vx = 0;
	vy = -1; // La gravedad inicial es 1
	damage = 50;
	this->orientation = orientation;

	attackRight = new Animation("res/gameRes/player/espada_derecha.png", width, height,
		118, 40, 4, 1, false, game);

	attackLeft= new Animation("res/gameRes/player/espada_izquierda.png", width, height,
		118, 40, 4, 1, false, game);

	attack = attackRight;
}

void Sword::update() {

	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla
	vx = 0;

	if (orientation == game->orientationLeft) {
		attack = attackLeft;
	}
	if (orientation == game->orientationRight) {
		attack = attackRight;
	}

	attack->update();
}

bool Sword::canBeDeleted() {
	
	if (currentLifeTime <= 0) {
		currentLifeTime = lifeTime;
		return true;
	}
	currentLifeTime--;
	return false;
}

void Sword::onCollision() {}

void Sword::draw(float scrollX, float scrollY) {

	attack->draw(x - scrollX, y - scrollY);
}