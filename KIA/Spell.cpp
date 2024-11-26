#include "Spell.h"

Spell::Spell(float x, float y, Game* game) :
	Attack("res/gameRes/player/proyectilSpell.png", x, y, 20, 20, game) {

	vx = 20;
	vy = -1; // La gravedad inicial es 1

	explode = new Animation("res/gameRes/player/impactoSpell.png",
		156, 150, 1096, 150, 6, 7, false, game);

	shoot = new Animation("res/gameRes/player/proyectilSpell.png",
		width, height, 18, 6, 6, 1, true, game);
	
	damage = 10;

	animation = shoot;
}

void Spell::update() {
	vy = vy - 1;

	if (vx == 0) {
		onCollision();
		deleteTime--;
	}
	animation->update();
}

bool Spell::canBeDeleted() {
	return vx == 0 && deleteTime <= 0;
}

void Spell::onCollision() {
	vx = 0;
	width = 156; // Área de impacto
	height = 150;
	animation = explode;
}

void Spell::draw(float scrollX, float scrollY) {

	animation->draw(x - scrollX, y - scrollY);
}