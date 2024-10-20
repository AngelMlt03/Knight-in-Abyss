#pragma once

#include "Actor.h"
#include "Spell.h"
#include "Sword.h"
#include "Animation.h" // incluir animacion

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Spell* castSpell();
	Sword* swordAttack();
	void update();
	void jump();
	void moveX(float axis);
	void moveY(float axis);

	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void takeDamage(int damage);
	int initHealth = 100;
	int healthPoints = initHealth;
	int invulnerableTime = 0;
	int mana = 4;
	bool onAir;
	bool onLadder;
	int orientation;
	int state;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aJumpingRight;
	Animation* aJumpingLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aShootingRight;
	Animation* aShootingLeft;
	Animation* animation; // Referencia a la animación mostrada

	int spellCadence = 50;
	int spellTime = 0;

	int swordCadence = 15;
	int swordTime = 0;
};


