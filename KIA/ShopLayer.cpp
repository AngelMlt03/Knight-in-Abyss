#include <iomanip>
#include <sstream> 

#include "ShopLayer.h"

ShopLayer::ShopLayer(Game* game)
	: Layer(game) {
	init();

	gamePad = SDL_GameControllerOpen(0);

	maxHealthButton = new Actor("res/shopMenu/boton_maxvida.png", 440, HEIGHT * 0.64, 180, 60, game);
	moreDamageButton = new Actor("res/shopMenu/boton_masdanio.png", 640, HEIGHT * 0.64, 180, 60, game);
	doubleJumpButton = new Actor("res/shopMenu/boton_comprarsalto.png", 840, HEIGHT * 0.64, 180, 60, game);
	noMaxHealthButton = new Actor("res/shopMenu/boton_no_maxvida.png", 440, HEIGHT * 0.64, 180, 74, game);
	noMoreDamageButton = new Actor("res/shopMenu/boton_no_masdanio.png", 640, HEIGHT * 0.64, 184, 84, game);
	noDoubleJumpButton = new Actor("res/shopMenu/boton_no_comprarsalto.png", 840, HEIGHT * 0.64, 180, 66, game);

	maxHealth = false;
	maxDamage = false;
	maxJump = false;

	textGold = new Text("", 458, 212, game);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << game->gold;
	textGold->content = ss.str();
}

void ShopLayer::init() {

	background = new Background("res/shopMenu/fondo_tienda.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	backButton = new Actor("res/shopMenu/boton_atras.png", 100, HEIGHT * 0.10, 60, 60, game);
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
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputGamePad) { // gamePAD
			gamePadToControls(event);
		}
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
		controlBack = false;
		game->audioBackground = game->menuAudio;
		game->audioBackground->play();
		game->layer = game->menuLayer;
	}
}

void ShopLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			controlBack = false;
			game->audioBackground = game->menuAudio;
			game->audioBackground->play();
			game->layer = game->menuLayer;
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
			buyHealth();
		}
		if (moreDamageButton->containsPoint(motionX, motionY)) {
			buyDamage();
		}
		if (doubleJumpButton->containsPoint(motionX, motionY)) {
			buyDoubleJump();
		}
	}
}

void ShopLayer::buyHealth() {
	if (game->gold >= 100) {
		game->gold = (maxHealth) ? game->gold : game->gold - 100;
		maxHealth = game->buyHealth();
	}
}

void ShopLayer::buyDamage() {
	if (game->gold >= 100) {
		game->gold = (maxDamage) ? game->gold : game->gold - 100;
		maxDamage = game->buyDamage();
	}
}

void ShopLayer::buyDoubleJump() {
	if (game->gold >= 1000) {
		game->gold = (maxJump) ? game->gold : game->gold - 1000;
		game->doubleJump = true;
		maxJump = true;
	}
}

void ShopLayer::gamePadToControls(SDL_Event event) {
	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	if (buttonA) {
		buyHealth();
	}
	bool buttonX = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_X);
	if (buttonX) {
		buyDamage();
	}
	bool buttonY = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_Y);
	if (buttonY) {
		buyDoubleJump();
	}
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	if (buttonB) {
		controlBack = true;
	}
}

void ShopLayer::update() {
	
	if (maxHealth) {
		maxHealthButton = noMaxHealthButton;
	}
	if (maxDamage) {
		moreDamageButton = noMoreDamageButton;
	}
	if (maxJump) {
		doubleJumpButton = noDoubleJumpButton;
	}
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << game->gold;
	textGold->content = ss.str();
}