#include <iomanip>
#include <sstream> 

#include "ShopLayer.h"

ShopLayer::ShopLayer(Game* game)
	: Layer(game) {
	init();

	maxHealthButton = new Actor("res/boton_maxvida.png", 440, HEIGHT * 0.64, 180, 60, game);
	moreDamageButton = new Actor("res/boton_masdanio.png", 640, HEIGHT * 0.64, 180, 60, game);
	doubleJumpButton = new Actor("res/boton_comprarsalto.png", 840, HEIGHT * 0.64, 180, 60, game);

	maxHealth = false;
	maxDamage = false;
	maxJump = false;

	textGold = new Text("", 458, 212, game);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << game->gold;
	textGold->content = ss.str();
}

void ShopLayer::init() {

	background = new Background("res/fondo_tienda.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	backButton = new Actor("res/boton_atras.png", 100, HEIGHT * 0.10, 60, 60, game);
}

void ShopLayer::draw() {
	background->draw();
	backButton->draw();
	maxHealthButton->draw();
	moreDamageButton->draw();
	doubleJumpButton->draw();
	textGold->draw();
	SDL_RenderPresent(game->renderer);
}

void ShopLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}
	//procesar controles
	if (controlBack) {
		// Cambia la capa
		game->layer = game->menuLayer;
		controlBack = false;
	}
}

void ShopLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		}
	}
}

void ShopLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (backButton->containsPoint(motionX, motionY)) {
			controlBack = true;
		}
		if (maxHealthButton->containsPoint(motionX, motionY)) {

			if (game->gold >= 100) {
				game->gold = (maxHealth) ? game->gold : game->gold - 100;
				maxHealth = game->buyHealth();
			}
		}
		if (moreDamageButton->containsPoint(motionX, motionY)) {

			if (game->gold >= 100) {
				game->gold = (maxDamage) ? game->gold : game->gold - 100;
				maxDamage = game->buyDamage();
			}
		}
		if (doubleJumpButton->containsPoint(motionX, motionY)) {

			if (game->gold >= 1000) {
				game->gold = (maxJump) ? game->gold : game->gold - 1000;
				game->doubleJump = true;
				maxJump = true;
			}
		}
	}
}

void ShopLayer::update() {
	
	if (maxHealth) {
		maxHealthButton = new Actor("res/boton_no_maxvida.png", 440, HEIGHT * 0.64, 180, 74, game);
	}
	if (maxDamage) {
		moreDamageButton = new Actor("res/boton_no_masdanio.png", 640, HEIGHT * 0.64, 184, 84, game);
	}
	if (maxJump) {
		doubleJumpButton = new Actor("res/boton_no_comprarsalto.png", 840, HEIGHT * 0.64, 180, 66, game);
	}
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << game->gold;
	textGold->content = ss.str();
}