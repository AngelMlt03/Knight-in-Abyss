#include "Player.h"
#include "GameLayer.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 70, 90, game) {

	onAir = false;
	onLadder = false;

	orientation = game->orientationRight;
	state = game->stateMoving;

	aJumpingRight = new Animation("res/jugador_saltando_derecha.png",
		width, height, 160, 40, 6, 4, true, game);
	aJumpingLeft = new Animation("res/jugador_saltando_izquierda.png",
		width, height, 160, 40, 6, 4, true, game);

	aShootingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);

	aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
		320, 40, 6, 8, true, game);
	aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
		320, 40, 6, 8, true, game);
	animation = aIdleRight;
}

void Player::update() {

	if (onLadder) {
		state = game->stateLadder;
	}

	// En el aire y moviéndose, PASA a estar saltando
	if (onAir && state == game->stateMoving) {
		state = game->stateJumping;
	}
	// No está en el aire y estaba saltando o en escalera, PASA a moverse
	if (!onAir && (state == game->stateJumping || state == game->stateLadder )) {
		state = game->stateMoving;
	}


	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimation = animation->update();

	onAir = !collisionDown;

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba casteando un hechizo o atacando
		if (state == game->stateCastSpelling || state == game->stateSwordAttacking) {
			state = game->stateMoving;
		}
	}

	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}

	// Selección de animación basada en estados
	if (state == game->stateJumping || state == game->stateLadder) {
		if (orientation == game->orientationRight) {
			animation = aJumpingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aJumpingLeft;
		}
	}

	if (state == game->stateCastSpelling || state == game->stateSwordAttacking) {
		if (orientation == game->orientationRight) {
			animation = aShootingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aShootingLeft;
		}
	}
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}

	if (spellTime > 0) {
		spellTime--;
	}

	if (swordTime > 0) {
		swordTime--;
	}
}

void Player::moveX(float axis) {
	vx = axis * 8;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

void Player::jump() {

	if (!onAir) {
		vy = -14;
		onAir = true;
	}
	else if (onLadder) {
		vy = -5;
		onLadder = true;
	}
}

Spell* Player::castSpell() {

	if (spellTime == 0 && mana > 0) {
		state = game->stateCastSpelling;
		spellTime = spellCadence;
		aShootingLeft->currentFrame = 0; //"Rebobinar" animación
		aShootingRight->currentFrame = 0; //"Rebobinar" animación
		Spell* spell = new Spell(x, y, game);
		if (orientation == game->orientationLeft) {
			spell->vx = spell->vx * -1; // Invertir
		}
		mana--;
		return spell;
	}
	else {
		return NULL;
	}

}

Sword* Player::swordAttack() {

	if (swordTime == 0) {
		state = game->stateSwordAttacking;
		swordTime = swordCadence;
		aShootingLeft->currentFrame = 0; //"Rebobinar" animación
		aShootingRight->currentFrame = 0; //"Rebobinar" animación
		float newx = 60;
		if (orientation == game->orientationLeft) {
			newx = newx * -1;
		}
		Sword* swordA = new Sword(x + newx, y, game);
		return swordA;
	}
	else {
		return NULL;
	}
}

void Player::takeDamage(int damage) {
	
	if (invulnerableTime <= 0) {

		invulnerableTime = 50;
		healthPoints -= damage;
		if (healthPoints < 0) {
			healthPoints = 0;
		}
	}
}

void Player::draw(float scrollX, float scrollY) {
	if (invulnerableTime == 0) {
		animation->draw(x - scrollX, y - scrollY);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x - scrollX, y - scrollY);
		}
	}
}
