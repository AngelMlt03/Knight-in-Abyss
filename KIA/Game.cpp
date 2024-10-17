#include "Game.h"
#include "GameLayer.h"
#include "MenuLayer.h"

Game::Game() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error SDL_Init" << SDL_GetError() << endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
		cout << "Error Window y Renderer" << SDL_GetError() << endl;
	}
	SDL_SetWindowTitle(window, "Juego de Naves");
	// Escalado de imágenes de calidad 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	menuLayer = new MenuLayer(this);
	gameLayer = new GameLayer(this);
	layer = menuLayer; // Pantalla INICIAL MENULAYER

	// fuentes
	TTF_Init();
	font = TTF_OpenFont("res/sans.ttf", 24);

	SDL_Surface* cursorImage = IMG_Load("res/cursor.png");

	SDL_Cursor* cursor = SDL_CreateColorCursor(cursorImage, 0, 0);

	// Aplica el cursor personalizado
	SDL_SetCursor(cursor);

	// Liberar la superficie
	SDL_FreeSurface(cursorImage);


	loopActive = true; // bucle activo
	loop();
}

void Game::loop() {

	int initTick; // ms de inicio loop
	int endTick; // ms de fin de loop
	int differenceTick; // fin - inicio

	while (loopActive) {
		initTick = SDL_GetTicks();

		// Controles
		layer->processControls();
		// Actualizar elementos
		layer->update();
		// Dibujar
		layer->draw();


		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		if (differenceTick < (1000 / 30)) {
			SDL_Delay((1000 / 30) - differenceTick);
		}
	}
}

void Game::scale() {
	scaledToMax = !scaledToMax;

	if (scaledToMax) {
		// Pasar la ventana a modo pantalla completa
		if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0) {
			// Manejar el error si ocurre
			SDL_Log("Error al intentar poner la ventana en fullscreen: %s", SDL_GetError());
		}
	}
	else {
		// Volver al modo de ventana normal
		if (SDL_SetWindowFullscreen(window, 0) != 0) {
			// Manejar el error si ocurre
			SDL_Log("Error al salir del modo fullscreen: %s", SDL_GetError());
		}
		// Restaurar el tamaño original de la ventana
		SDL_SetWindowSize(window, WIDTH, HEIGHT);
		// Restaurar la escala original del render
		SDL_RenderSetScale(renderer, 1, 1);
	}
}
