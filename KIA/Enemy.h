#pragma once

#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int w, int h, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update();
	virtual void doMove();
	void impacted(); // Recibe impacto y pone animación de morir
	float vxIntelligence;
	int state;
	Animation* aDying;
	Animation* aMovingLeft;
	Animation* aMovingRight;
	Animation* animation; // Referencia a la animación mostrada
};

