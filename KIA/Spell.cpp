#include "Spell.h"

Spell::Spell(float x, float y, Game* game, int orientation) :
	Attack("res/gameRes/player/proyectilSpell.png", x, y, 48, 28, game) {

	vx = 25;
	vy = -1; // La gravedad inicial es 1

	explode = new Animation("res/gameRes/player/impactoSpell.png",
		156, 150, 1096, 150, 6, 7, false, game);

	shootRight = new Animation("res/gameRes/player/proyectilSpell_derecha.png",
		width, height, 48, 28, 6, 1, true, game);

	shootLeft = new Animation("res/gameRes/player/proyectilSpell_izquierda.png",
		width, height, 48, 28, 6, 1, true, game);
	
	damage = 10;

	animation = shootRight;

	this->orientation = orientation;
}

void Spell::update() {
	vy = vy - 1;

	if (vx == 0) {
		onCollision();
		deleteTime--;
	}
	else {
		if (orientation == game->orientationLeft) {
			animation = shootLeft;
		}
		if (orientation == game->orientationRight) {
			animation = shootRight;
		}
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