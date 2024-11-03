#include "Item.h"

Item::Item(string filename, float x, float y, float width, float height, Game* game)
	: Actor(filename, x, y, width, height, game) {
	vy = -8;
}