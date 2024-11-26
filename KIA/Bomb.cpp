#include "Bomb.h"

Bomb::Bomb(float x, float y, Game* game) :
	Attack("res/gameRes/enemies/bossBomb.png", x, y, 48, 62, game) {

	explode = new Animation("res/gameRes/player/impactoSpell.png",
		156, 150, 1096, 150, 6, 7, false, game);

	bomb = new Animation("res/gameRes/enemies/bossBomb.png",
		width, height, 478, 314, 6, 2, true, game);

	animation = bomb;
	damage = 10;

	vy = 0;
}

void Bomb::update() {

	explodeTime--;
	lifeTime--;
	if (explodeTime == 0) {
		onCollision();
	}
	animation->update();
}

bool Bomb::canBeDeleted() {
	return lifeTime <= 0;
}

void Bomb::onCollision() {
	width = 156; // Área de impacto
	height = 150;
	animation = explode;
}

void Bomb::draw(float scrollX, float scrollY) {

	animation->draw(x - scrollX, y - scrollY);
}