#include "ShopLayer.h"

ShopLayer::ShopLayer(Game* game)
	: Layer(game) {
	init();	
}

void ShopLayer::init() {

	background = new Background("res/fondo_tienda.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	backButton = new Actor("res/boton_atras.png", WIDTH * 0.1, HEIGHT * 0.10, 60, 60, game);
}

void ShopLayer::draw() {
	background->draw();
	backButton->draw();
	SDL_RenderPresent(game->renderer);
}

void ShopLayer::processControls() {

	//procesar controles
	if (controlBack) {
		// Cambia la capa
		game->layer = game->menuLayer;
		controlBack = false;
	}
}