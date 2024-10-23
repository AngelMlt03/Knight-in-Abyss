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

	aSpellingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aSpellingLeft = new Animation("res/jugador_disparando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);

	aSwordingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aSwordingLeft = new Animation("res/jugador_disparando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);

	aShieldingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, true, game);
	aShieldingLeft = new Animation("res/jugador_disparando_izquierda.png",
		width, height, 160, 40, 6, 4, true, game);

	aDashingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aDashingLeft = new Animation("res/jugador_disparando_izquierda.png",
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

	healthPoints = game->maxHealth;
	damagePoints = game->damage;
}

void Player::update() {

	if (onLadder) {
		state = game->stateLadder;
	}

	if (usingShield) {
		state = game->stateUsingShield;
	}

	if (dashTime > 0) {
        dashTime--;
        if (dashTime == 0) {
			dashing = false;
            vx = 0;  // Detén el dash
        }
    }

	if (!onAir) {
		jumpCount = 0;
	}

	// En el aire y moviéndose, PASA a estar saltando
	if (onAir && state == game->stateMoving) {
		state = game->stateJumping;
	}
	// No está en el aire y estaba saltando o en escalera, PASA a moverse
	if (!onAir && (state == game->stateJumping || state == game->stateLadder 
		|| (state == game->stateUsingShield  && !usingShield))) {
		state = game->stateMoving;
	}

	if (state == game->stateUsingShield && !usingShield) {
		state = game->stateMoving;
	}

	if (state == game->stateDashing && !dashing) {
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

	if (state == game->stateCastSpelling) {
		if (orientation == game->orientationRight) {
			animation = aSpellingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aSpellingLeft;
		}
	}

	if (state == game->stateSwordAttacking) {
		if (orientation == game->orientationRight) {
			animation = aSwordingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aSwordingLeft;
		}
	}

	if (state == game->stateUsingShield) {
		if (orientation == game->orientationRight) {
			animation = aShieldingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aShieldingLeft;
		}
	}

	if (state == game->stateDashing) {
		if (orientation == game->orientationRight) {
			animation = aDashingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aDashingLeft;
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

	if (dashCooldown > 0) {
		dashCooldown--;
	}
}

void Player::moveX(float axis) {

	if (!dashing) {
		vx = (usingShield) ? axis * 2 : axis * 8;
	}
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

void Player::jump() {

	if (!onAir) {
		vy = (usingShield) ? -5 : - 14;
		onAir = true;
		jumpCount++;
		canDoubleJump = false;
	}
	else if (onAir && jumpCount < maxJumps && canDoubleJump && game->doubleJump) {
		vy = -14;
		jumpCount++;
		canDoubleJump = false;
	}
	else if (onLadder) {
		vy = -5;
		onLadder = true;
	}
}

Spell* Player::castSpell() {

	if (spellTime == 0 && mana > 0 && canCastSpell) {
		state = game->stateCastSpelling;
		spellTime = spellCadence;
		aSpellingLeft->currentFrame = 0; //"Rebobinar" animación
		aSpellingRight->currentFrame = 0; //"Rebobinar" animación
		Spell* spell = new Spell(x, y, game);
		if (orientation == game->orientationLeft) {
			spell->vx = spell->vx * -1; // Invertir
		}
		mana--;
		canCastSpell = false;
		return spell;
	}
	else {
		return NULL;
	}

}

Sword* Player::swordAttack() {

	if (swordTime == 0 && canSwordAttack) {
		state = game->stateSwordAttacking;
		swordTime = swordCadence;
		aSwordingLeft->currentFrame = 0; //"Rebobinar" animación
		aSwordingRight->currentFrame = 0; //"Rebobinar" animación
		float newx = 60;
		if (orientation == game->orientationLeft) {
			newx = newx * -1;
		}
		Sword* swordA = new Sword(x + newx, y, game);
		canSwordAttack = false;
		return swordA;
	}
	else {
		return NULL;
	}
}

void Player::takeDamage(int damage) {
	
	if (invulnerableTime <= 0) {

		invulnerableTime = 50;
		healthPoints -= (usingShield) ? damage * 0.2 : damage;
		if (healthPoints < 0) {
			healthPoints = 0;
		}
	}
}

void Player::dash() {

	if (dashCooldown == 0 && dashTime == 0 && !usingShield && canDash) {
		dashTime = dashDuration;
		dashCooldown = dashCooldownTime;
		state = game->stateDashing; // Cambia al estado de dash
		if (orientation == game->orientationRight) {
			vx = dashSpeed; // Dash hacia la derecha
		}
		else {
			vx = -dashSpeed; // Dash hacia la izquierda
		}
		dashing = true;
		canDash = false;
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
