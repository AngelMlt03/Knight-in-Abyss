#include "Item.h"

Item::Item(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 40, game) {
	vy = -8;
}