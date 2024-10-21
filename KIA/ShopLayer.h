#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"

class ShopLayer : public Layer
{
public:
	ShopLayer(Game* game);
	void init() override;
	void draw() override;
	void processControls() override;

	bool controlBack;
	Background* background;
	Actor* backButton;
};

