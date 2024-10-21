#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"
#include "Text.h"

class ShopLayer : public Layer
{
public:
	ShopLayer(Game* game);
	void init() override;
	void draw() override;
	void update() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);

	Text* textGold;

	bool controlBack;
	Background* background;
	Actor* backButton;

	// Botones visibles
	Actor* maxHealthButton;
	Actor* moreDamageButton;
	Actor* doubleJumpButton;

	// Límite compras
	bool maxHealth;
	bool maxDamage;
	bool maxJump;
};

