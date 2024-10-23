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
	int healthPoints;
	int damagePoints;
	int invulnerableTime = 0;
	int mana = 4;
	bool onAir;
	bool onLadder;
	bool usingShield;
	int orientation;
	int state;

	// Animations
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aJumpingRight;
	Animation* aJumpingLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aSpellingRight;
	Animation* aSpellingLeft;
	Animation* aSwordingRight;
	Animation* aSwordingLeft;
	Animation* aShieldingRight;
	Animation* aShieldingLeft;
	Animation* aDashingRight;
	Animation* aDashingLeft;

	Animation* animation; // Referencia a la animación mostrada

	int spellCadence = 50;
	int spellTime = 0;

	int swordCadence = 25;
	int swordTime = 0;
};


