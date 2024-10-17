#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "HealthBar.h"
#include "Alien.h"
#include "Goomba.h"
#include "Jumper.h"
#include "Summoner.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Pad.h"
#include "Space.h" // importar
#include "Audio.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>
#include <algorithm>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();

	Audio* audioBackground;
	Audio* audioHit;

	Actor* message;
	bool pause;

	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonJump;
	Actor* buttonShoot;
	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;
	float scrollY;
	int mapWidth;
	int mapHeight;
	list<Tile*> tiles;

	Text* textPoints;
	int points;

	int newEnemyTime = 0;

	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* healthFrame;
	Actor* heart;
	HealthBar* healthbar;
	
	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	int deletedEnemies = 0;

	void summonNewEnemy(int x, int y);

	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<Tile*> ladders;
};
