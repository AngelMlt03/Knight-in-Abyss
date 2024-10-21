#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Valores generales
#define WIDTH 1280
#define HEIGHT 720

#include "Layer.h"
class Layer;

class Game
{
public:
	Game();
	void loop();
	void scale();
	TTF_Font* font;
	bool scaledToMax = false;
	float scaleLower = 1;
	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	Layer* layer;
	Layer* menuLayer;
	Layer* shopLayer;
	Layer* gameLayer;

	int currentLevel = 0;
	int levelRow = 0;
	int levelColumn = 0;
	int finalLevel = 2;

	// Soporte multiples entradas (Teclado y ratón)
	int input;
	int const inputKeyboard = 1;
	int const inputMouse = 2;
	int const inputGamePad = 3;

	int const stateMoving = 1;
	int const stateJumping = 2;
	int const stateDying = 3;
	int const stateDead = 4;
	int const stateCastSpelling = 5;
	int const stateSwordAttacking = 6;
	int const stateLadder = 7;

	int const orientationRight = 1;
	int const orientationLeft = 2;

	// Menu functions
	int maxHealth = 100;
	int damage = 10;
	bool doubleJump = false;
	int gold = 2345;
	bool buyHealth();
	bool buyDamage();
};

