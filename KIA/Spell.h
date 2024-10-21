#pragma once

#include "Attack.h"

class Spell : public Attack
{
public:
	Spell(float x, float y, Game* game);
	void update() override;
	bool canBeDeleted() override;
};

