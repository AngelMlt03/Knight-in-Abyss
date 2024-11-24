#include "Spike.h"

Spike::Spike(float x, float y, Game* game)
	: Trap("res/gameRes/spikes.png", x, y, 55, 33, game) {

	damage = 10;
}