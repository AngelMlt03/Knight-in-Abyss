#include "Pad.h"

Pad::Pad(float x, float y, Game* game)
	: Actor("res/controlDisplay/pad.png", x, y, 120, 120, game) {
}

float Pad::getOrientationX(float clickX) {
	return clickX - x;
}