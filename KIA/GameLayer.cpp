#include <iomanip>
#include <sstream>
#include <random>

#include "GameLayer.h"

#include "HealthItem.h"
#include "ManaItem.h"
#include "Coin.h"
#include "Spike.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	endGame = false;
	pause = true;
	levelStartMessage = new Actor("res/messages/mensaje_nivel_" + to_string(game->currentLevel + 1) + ".png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	
	tutorialMessage1 = new Actor("res/messages/AD_message.png", 320, 300, 246, 104, game);
	tutorialMessage2 = new Actor("res/messages/rompe_message.png", 560, 400, 246, 104, game);
	tutorialMessage3 = new Actor("res/messages/W_message.png", 860, 350, 246, 104, game);
	tutorialMessage4 = new Actor("res/messages/K_message.png", 1420, 430, 246, 104, game);
	tutorialMessage5 = new Actor("res/messages/Barra_message.png", 1740, 350, 246, 104, game);
	tutorialMessage6 = new Actor("res/messages/L_message.png", 2250, 350, 246, 104, game);
	tutorialMessage7 = new Actor("res/messages/L-Shift_message.png", 3800, 350, 246, 104, game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}

void GameLayer::init() {
	audioBackground = Audio::createAudio("res/soundEffects/musica_ambiente_nivel_"+ to_string(game->currentLevel+1) +".mp3", true);
	game->audioBackground = audioBackground;
	game->audioBackground->play();

	audioVictory = Audio::createAudio("res/soundEffects/efecto_matar_boss.wav", false);

	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);
	buttonJump = new Actor("res/controlDisplay/boton_salto.png", WIDTH * 0.92, HEIGHT * 0.58, 100, 100, game);
	buttonShield = new Actor("res/controlDisplay/boton_escudo.png", WIDTH * 0.835, HEIGHT * 0.58, 100, 100, game);
	buttonSpell = new Actor("res/controlDisplay/boton_spell.png", WIDTH * 0.835, HEIGHT * 0.77, 100, 100, game);
	buttonAttack = new Actor("res/controlDisplay/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.77, 100, 100, game);
	buttonDash = new Actor("res/controlDisplay/boton_dash.png", WIDTH * 0.92, HEIGHT * 0.77, 100, 100, game);

	buttonPause = new Actor("res/controlDisplay/boton_pausa.png", WIDTH * 0.92, HEIGHT * 0.10, 100, 100, game);

	pauseBackground = new Actor("res/pausePanel/fondo_pausa.png", WIDTH * 0.5, HEIGHT * 0.5, 600, 411, game);
	buttonPlayPause = new Actor("res/pausePanel/boton_play_pause.png", WIDTH * 0.42, HEIGHT * 0.52, 140, 133, game);
	buttonHomePause = new Actor("res/pausePanel/boton_home_pause.png", WIDTH * 0.58, HEIGHT * 0.52, 140, 133, game);

	tiles.clear(); // Vaciar por si reiniciamos el juego
	ladders.clear(); // Vaciar por si reiniciamos el juego
	attacks.clear(); // Vaciar por si reiniciamos el juego
	enemyAttacks.clear();
	enemyBombs.clear();
	enemies.clear(); // Vaciar por si reiniciamos el juego
	breakableItems.clear(); // Vaciar por si reiniciamos el juego
	items.clear(); // Vaciar por si reiniciamos el juego
	traps.clear(); // Vaciar por si reiniciamos el juego

	space = new Space(1);
	bossAlive = true;

	levelRow = 0;
	levelColumn = 0;

	background = new Background("res/gameRes/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, game);

	coins = 0;
	textcoins = new Text("hola", 120, 132, game);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << coins;
	textcoins->content = ss.str();

	backgroundcoins = new Actor("res/gameRes/moneda.png", 42, 130, 36, 36, game);

	healthFrame = new Actor("res/gameRes/healthFrame.png", 150, 42, 259, 42, game);
	heart = new Actor("res/gameRes/corazon.png", 45, 42, 47, 42, game);
	healthbar = new HealthBar("res/gameRes/healthBar.png", 55, 21, 226, 42, game);

	bossHF = new Actor("res/gameRes/healthFrame_boss.png", WIDTH * 0.78, HEIGHT * 0.93, 500, 42, game);
	bossHB = new HealthBar("res/gameRes/healthBar_boss.png", WIDTH*0.59, HEIGHT*0.9, 500, 42, game);
	bossName = new Text("BomberBoy", WIDTH * 0.87, HEIGHT * 0.88, game);

	manabar0 = new Actor("res/gameRes/manaBar0.png", 90, 86, 139, 42, game);
	manabar1 = new Actor("res/gameRes/manaBar1.png", 90, 86, 139, 42, game);
	manabar2 = new Actor("res/gameRes/manaBar2.png", 90, 86, 139, 42, game);
	manabar3 = new Actor("res/gameRes/manaBar3.png", 90, 86, 139, 42, game);
	manabar4 = new Actor("res/gameRes/manaBar4.png", 90, 86, 139, 42, game);

	currentHP = game->maxHealth;
	currentMana = game->maxMana;

	loadMap("res/gameLevels/" + to_string(game->currentLevel) + "_" + to_string(levelRow)
			+ "_" + to_string(levelColumn) + ".txt");
	scrollX = 0;
	scrollY = 0;
}

void GameLayer::changeRoom(int direction) {

	audioBackground = Audio::createAudio("res/soundEffects/musica_ambiente_nivel_" + to_string(game->currentLevel + 1) + ".mp3", true);
	game->audioBackground = audioBackground;
	game->audioBackground->play();
	tiles.clear();
	ladders.clear();
	attacks.clear(); // Vaciar por si reiniciamos el
	enemyAttacks.clear();
	enemyBombs.clear();
	enemies.clear(); // Vaciar por si reiniciamos el juego
	breakableItems.clear(); // Vaciar por si reiniciamos el juego
	items.clear();
	traps.clear();

	space = new Space(1);
	currentHP = player->healthPoints;
	currentMana = player->mana;

	loadMap("res/gameLevels/" + to_string(game->currentLevel) + "_" + to_string(levelRow)
		+ "_" + to_string(levelColumn) + ".txt");

	levelStartMessage = new Actor("res/messages/mensaje_nivel_"+ to_string(game->currentLevel+1) + ".png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	switch (direction) {
	case 0:
		scrollX = 0;
		break;
	case 1:
		scrollX = mapWidth-WIDTH;
		break;
	case 2:
		scrollX = player->x;
		break;
	}
	
	scrollY = player->y-700;
}

void GameLayer::endLevel() {

	game->gold += coins;
	coins = 0;

	if (game->currentLevel <= game->finalLevel) {
		
		levelRow = 0;
		levelColumn = 0;
		changeRoom(0);
		currentHP = game->maxHealth;
		currentMana = game->maxMana;
	}
	else {
		// Lo que pasa al pasarte el juego
		if (!pause && endGame) {
			endGame = false;
			game->currentLevel = 0;
			game->audioBackground = game->menuAudio;
			game->audioBackground->play();
			game->layer = game->menuLayer;
		}
	}
}

void GameLayer::processControls() {

	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_KEYDOWN) {
			// Oculta el cursor cuando se presiona cualquier tecla
			SDL_ShowCursor(SDL_DISABLE);
			cursorVisible = false;
		}
		// Detecta el movimiento del ratón
		if (event.type == SDL_MOUSEMOTION) {
			// Muestra el cursor cuando se mueve el ratón
			if (!cursorVisible) {
				SDL_ShowCursor(SDL_ENABLE);
				cursorVisible = true;
			}
		}

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
		// Procesar Mando
		if (game->input == game->inputGamePad) { // gamePAD
			gamePadToControls(event);
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}
	// Lanzar hechizo
	if (controlSpell && !controlShield) {
		Attack* newSpell = player->castSpell();
		if (newSpell != NULL) {
			space->addDynamicActor(newSpell);
			attacks.push_back(newSpell);
			controlSpell = false;
		}
	}
	// Ataque espada
	if (controlAttack && !controlShield) {
		Attack* newSwordA = player->swordAttack();
		if (newSwordA != NULL) {
			space->addDynamicActor(newSwordA);
			attacks.push_back(newSwordA);
			controlAttack = false;
		}
	}
	
	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
	}
	else if (controlMoveY < 0) {
		player->jump();
	}
	else {
	}
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	bool buttonX = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_X);
	bool buttonLB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	bool buttonRB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	bool buttonStart = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_START);

	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	//cout << "botones:" << buttonA << "," << buttonB << "," << buttonBack << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	int stickY = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTY);
	//cout << "stickY" << stickY << endl;
	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	
	if (buttonA && menuPause) {
		menuPause = false;
		pause = false;
		return;
	}
	if (buttonB && menuPause) {
		pause = true;
		menuPause = false;
		game->audioBackground = game->menuAudio;
		game->audioBackground->play();
		game->layer = game->menuLayer;
		return;
	}

	for (int button = SDL_CONTROLLER_BUTTON_A; button < SDL_CONTROLLER_BUTTON_MAX; ++button) {

		if (SDL_GameControllerGetButton(gamePad, static_cast<SDL_GameControllerButton>(button))) {
			SDL_ShowCursor(SDL_DISABLE);
			cursorVisible = false;
			if (levelStartMessage) {
				pause = false;
				delete levelStartMessage;
				levelStartMessage = nullptr;
				break;
			}
		}
	}

	if (buttonStart) {
		menuPause = true;
	}

	if (menuPause || pause) { return; }

	if (stickX > 4000) {
		controlMoveX = 1;
	}
	else if (stickX < -4000) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}
	if (buttonA || stickY < -11000) {
		controlMoveY = -1;
	}
	else {
		controlMoveY = 0;
		player->canDoubleJump = true;
	}
	if (buttonB) {
		controlSpell = true;
	}
	else {
		controlSpell = false;
		player->canCastSpell = true;
	}
	if (buttonX) {
		controlAttack = true;
	}
	else {
		controlAttack = false;
		player->canSwordAttack = true;
	}
	if (buttonLB) {
		controlDash = true;
	}
	else {
		controlDash = false;
		player->canDash = true;
	}
	if (buttonRB) {
		controlShield = true;
	}
	else {
		controlShield = false;
	}
}

void GameLayer::keysToControls(SDL_Event event) {

	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;

		if (levelStartMessage) {
			pause = false;
			delete levelStartMessage;
			levelStartMessage = nullptr;
		}
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			menuPause = !menuPause;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_k: // ataque
			controlAttack = true;
			break;
		case SDLK_l: // lanza hechizo
			controlSpell = true;
			break;
		case SDLK_SPACE:
			controlShield = true;
			break;
		case SDLK_LSHIFT:
			controlDash = true;
			break;
		}
	}

	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
				player->canDoubleJump = true;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_k: // ataque
			controlAttack = false;
			player->canSwordAttack = true;
			break;
		case SDLK_l: // lanza hechizo
			controlSpell = false;
			player->canCastSpell = true;
			break;
		case SDLK_SPACE:
			controlShield = false;
			break;
		case SDLK_LSHIFT:
			controlDash = false;
			player->canDash = true;
			break;
		}
	}
}

void GameLayer::mouseToControls(SDL_Event event) {

	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			// CLICK TAMBIEN TE MUEVE
			controlMoveX = pad->getOrientationX(motionX);
		}
		if (buttonSpell->containsPoint(motionX, motionY)) {
			controlSpell = true;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = -1;
		}
		if (buttonAttack->containsPoint(motionX, motionY)) {
			controlAttack = true;
		}
		if (buttonDash->containsPoint(motionX, motionY)) {
			controlDash = true;
		}
		if (buttonShield->containsPoint(motionX, motionY)) {
			controlShield = true;
		}
		if (buttonPause->containsPoint(motionX, motionY)) {
			menuPause = true;
		}
		if (buttonPlayPause->containsPoint(motionX, motionY)) {
			menuPause = false;
			pause = false;
		}
		if (buttonHomePause->containsPoint(motionX, motionY) && menuPause) {
			pause = true;
			menuPause = false;
			game->audioBackground = game->menuAudio;
			game->audioBackground->play();
			game->layer = game->menuLayer;
		}
		if (levelStartMessage && levelStartMessage->containsPoint(motionX, motionY)) {
			pause = false;
			delete levelStartMessage;
			levelStartMessage = nullptr;
		}
	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		if (pad->clicked && pad->containsPoint(motionX, motionY)) {
			controlMoveX = pad->getOrientationX(motionX);
			// Rango de -20 a 20 es igual que 0
			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}
		}
		else {
			pad->clicked = false; // han sacado el ratón del pad
			controlMoveX = 0;
		}
		if (buttonSpell->containsPoint(motionX, motionY) == false) {
			controlSpell = false;
			player->canCastSpell = true;
		}
		if (buttonJump->containsPoint(motionX, motionY) == false) {
			controlMoveY = 0;
			player->canDoubleJump = true;
		}
		if (buttonAttack->containsPoint(motionX, motionY) == false) {
			controlAttack = false;
			player->canSwordAttack = true;
		}
		if (buttonDash->containsPoint(motionX, motionY)) {
			controlDash = false;
			player->canDash = true;
		}
		if (buttonShield->containsPoint(motionX, motionY)) {
			controlShield = false;
		}
	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = false;
			// LEVANTAR EL CLICK TAMBIEN TE PARA
			controlMoveX = 0;
		}
		if (buttonSpell->containsPoint(motionX, motionY)) {
			controlSpell = false;
			player->canCastSpell = true;
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = 0;
			player->canDoubleJump = true;
		}
		if (buttonAttack->containsPoint(motionX, motionY)) {
			controlAttack = false;
			player->canSwordAttack = true;
		}
		if (buttonDash->containsPoint(motionX, motionY)) {
			controlDash = false;
			player->canDash = true;
		}
		if (buttonShield->containsPoint(motionX, motionY)) {
			controlShield = false;
		}
	}
}

void GameLayer::update() {

	if (pause) {
		return;
	}

	// Usar escudo
	player->usingShield = controlShield;
	// Dash
	if (controlDash) {
		player->dash();
		controlDash = false;
	}

	// Cambio de habitación - Derecha
	if (player->x >= mapWidth) {
		levelColumn++;
		changeRoom(0);
	}

	// Cambio de habitación - Izquierda
	if (player->x <= 0) {
		levelColumn--;
		changeRoom(1);
	}

	// Cambio de habitación - Arriba
	if (player->y <= 0) {
		levelRow++;
		changeRoom(2);
	}

	// Nivel superado
	if (cup->isOverlap(player) && !bossAlive) {
		
		levelStartMessage = new Actor("res/messages/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		
		game->currentLevel++;
		endLevel();
		if (game->currentLevel > game->finalLevel) { endGame = true; }
		pause = true;
	}

	// Jugador se cae
	if (player->y > mapHeight + 80) {
		levelStartMessage = new Actor("res/messages/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		init();
	}

	space->update();

	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
	}

	if (boss != nullptr && bossRoom) {
		boss->update();
	}

	for (auto const& attack : attacks) {
		attack->update();
	}

	for (auto const& eA : enemyAttacks) {
		eA->update();
	}

	for (auto const& eB : enemyBombs) {
		eB->update();
	}

	// Colisiones , Player - Enemy
	for (auto const& enemy : enemies) {

		if (player->isOverlap(enemy) && enemy->state != game->stateDying
			&& enemy->state != game->stateDead) {
			player->takeDamage(enemy->damage);
		}	
	}

	if (boss != nullptr && player->isOverlap(boss) && boss->state != game->stateDying
		&& boss->state != game->stateDead) {
		player->takeDamage(boss->damage);
	}

	if (player->healthPoints <= 0) {
		levelStartMessage = new Actor("res/messages/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		init();
		return;
	}

	// Colisiones , Player - Ladder

	for (auto const& ladder : ladders) {

		if (ladder->isOverlap(player)) {

			player->onLadder = true;
			break;
		}
		player->onLadder = false;
	}

	// Colisiones , Player - Items

	list<Item*> deleteItems;

	for (auto const& item : items) {

		if (item->isOverlap(player)) {

			bool pInList = std::find(deleteItems.begin(),
				deleteItems.end(),
				item) != deleteItems.end();

			if (!pInList) {
				deleteItems.push_back(item);
			}

			item->onCollision();
		}
	}

	// Colisiones , Player - Traps

	for (auto const& trap : traps) {
	
		if (trap->isOverlap(player)) {
			player->takeDamage(trap->damage);
		}
	}

	// Colisiones , Player - EnemyAttacks, Player - EnemyBombs

	list<Attack*> deleteEnemyAttacks; 
	list<Bomb*> deleteEnemyBombs;

	for (auto const& ep : enemyAttacks) {

		if ((ep->isOverlap(player) && player->invulnerableTime <= 0) || ep->canBeDeleted()) {
			bool pInList = std::find(deleteEnemyAttacks.begin(), deleteEnemyAttacks.end(),
				ep) != deleteEnemyAttacks.end();

			if (!pInList) {
				deleteEnemyAttacks.push_back(ep);
			}
		}
		if (ep->isOverlap(player)) {
			player->takeDamage(ep->damage);
		}
	}

	for (auto const& eB : enemyBombs) {

		if (eB->canBeDeleted()) {
			bool pInList = std::find(deleteEnemyBombs.begin(), deleteEnemyBombs.end(),
				eB) != deleteEnemyBombs.end();

			if (!pInList) {
				deleteEnemyBombs.push_back(eB);
			}
		}
		if (eB->isOverlap(player) && player->invulnerableTime <= 0 && eB->explodeTime <= 0) {
			player->takeDamage(eB->damage);
		}
	}

	// Colisiones , Attack - Enemy, Attack - BreakableItem

	list<Enemy*> deleteEnemies;
	list<Attack*> deleteAttacks;
	list<BreakableItem*> deleteBreakableItems;

	for (auto const& attack : attacks) {
		if (attack->isInRender(scrollX, scrollY) == false || attack->canBeDeleted()) {

			bool pInList = std::find(deleteAttacks.begin(),
				deleteAttacks.end(),
				attack) != deleteAttacks.end();

			if (!pInList) {
				deleteAttacks.push_back(attack);
			}
		}
	}

	for (auto const& attack : attacks) {
		for (auto const& enemy : enemies) {
		
			if (enemy->isOverlap(attack)) {
				bool pInList = std::find(deleteAttacks.begin(),
					deleteAttacks.end(),
					attack) != deleteAttacks.end();

				if (!pInList && attack->canBeDeleted()) {
					deleteAttacks.push_back(attack);
				}

				attack->onCollision();
				if (enemy->state != game->stateDying && enemy->state != game->stateDead) {
					enemy->impacted();

					coins++;
					std::stringstream ss;
					ss << std::setfill('0') << std::setw(4) << coins;
					textcoins->content = ss.str();
				}
			}
		}
		for (auto const& bi : breakableItems) {
			
			if (bi->isOverlap(attack)) {
				bool pInList = std::find(deleteAttacks.begin(),
					deleteAttacks.end(),
					attack) != deleteAttacks.end();

				if (!pInList && attack->canBeDeleted()) {
					deleteAttacks.push_back(attack);
				}
				pInList = std::find(deleteBreakableItems.begin(),
					deleteBreakableItems.end(),
					bi) != deleteBreakableItems.end();

				if (!pInList) {
					deleteBreakableItems.push_back(bi);
				}
				attack->onCollision();
				bi->onCollision();
				createRandomItem(bi->x, bi->y);
			}
		}
		if (boss != nullptr && boss->isOverlap(attack)) {
			bool pInList = std::find(deleteAttacks.begin(),
				deleteAttacks.end(),
				attack) != deleteAttacks.end();

			if (!pInList && attack->canBeDeleted()) {
				deleteAttacks.push_back(attack);
			}

			attack->onCollision();
			boss->takeDamage(attack->damage);

			if (boss->currentHP <= 0) {
				bossAlive = false;
				space->removeDynamicActor(boss);
				delete boss;
				boss = nullptr;
				game->audioBackground->stop();
				game->audioBackground = audioVictory;
				game->audioBackground->play();
			}
		}
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delAttack : deleteAttacks) {
		attacks.remove(delAttack);
		space->removeDynamicActor(delAttack);
		delete delAttack;
	}
	deleteAttacks.clear();

	for (auto const& delBreakableItems : deleteBreakableItems) {
		breakableItems.remove(delBreakableItems);
		space->removeDynamicActor(delBreakableItems);
		delete delBreakableItems;
	}
	deleteBreakableItems.clear();

	for (auto const& delItems: deleteItems) {
		items.remove(delItems);
		space->removeDynamicActor(delItems);
		delete delItems;
	}
	deleteItems.clear();

	for (auto const& delEP : deleteEnemyAttacks) {
		enemyAttacks.remove(delEP);
		space->removeDynamicActor(delEP);
		delete delEP;
	}
	deleteEnemyAttacks.clear();

	for (auto const& delEB : deleteEnemyBombs) {
		enemyBombs.remove(delEB);
		space->removeDynamicActor(delEB);
		delete delEB;
	}
	deleteEnemyBombs.clear();
}

void GameLayer::loadMap(string name) {

	bossRoom = false;
	char character;
	string line;
	ifstream streamFile(name.c_str());

	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		int rowCount = 0;
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 55; // Ancho del mapa en pixels
			rowCount++;
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 54 / 2 + j * 54; // x central
				float y = 54 + i * 54; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
		mapHeight = rowCount * 55;
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y) {

	switch (character) {
		case '1': {
			player = new Player(x, y, game);
			player->healthPoints = currentHP;
			player->mana = currentMana;
			// modificación para empezar a contar desde el suelo.
			player->y = player->y - player->height / 2;
			space->addDynamicActor(player);
			break;
		}
		case 'C': {
			cup = new Tile("res/gameRes/copa.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo.
			cup->y = cup->y - cup->height / 2;
			space->addDynamicActor(cup); // Realmente no hace falta
			break;
		}
		case 'F': {
			Enemy* enemy = new StaticFlying(x, y, game, this);
			// modificación para empezar a contar desde el suelo.
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			//space->addDynamicActor(enemy);
			break;
		}
		case 'V': {
			Enemy* enemy = new FlyingEnemy(x, y, game, this);
			// modificación para empezar a contar desde el suelo.
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			space->addDynamicActor(enemy);
			break;
		}
		case 'A': {
			Enemy* enemy = new Basic(x, y, game);
			// modificación para empezar a contar desde el suelo.
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			space->addDynamicActor(enemy);
			break;
		}
		case 'R': {
			Tile* ladder = new Tile("res/gameRes/ladder.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo. 
			ladder->y = ladder->y - ladder->height / 2;
			ladders.push_back(ladder);
			break;
		}
		case 'B': {
			std::random_device rd;  // Semilla basada en el hardware
			std::mt19937 gen(rd()); // Generador Mersenne Twister
			std::uniform_int_distribution<> distribucion(0, 2);
			int random = distribucion(gen);
			BreakableItem* bi = new BreakableItem(x, y, game, random);
			// modificación para empezar a contar desde el suelo. 
			bi->y = bi->y - bi->height / 2;
			breakableItems.push_back(bi);
			break;
		}
		case 'K': {
			std::random_device rd;  // Semilla basada en el hardware
			std::mt19937 gen(rd()); // Generador Mersenne Twister
			std::uniform_int_distribution<> distribucion(3, 3);
			int random = distribucion(gen);
			BreakableItem* bi = new BreakableItem(x, y, game, random);
			// modificación para empezar a contar desde el suelo. 
			bi->y = bi->y - bi->height / 2;
			breakableItems.push_back(bi);
			break;
		}
		case 'H': {
			Spike* spike = new Spike(x, y, game);
			// modificación para empezar a contar desde el suelo.
			spike->y = spike->y - spike->height / 2;
			traps.push_back(spike);
			space->addStaticActor(spike);
			break;
		}
		case 'P': {
			Tile* tile = new Tile("res/gameRes/bloque_fondo1.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case 'G': {
			Tile* tile = new Tile("res/gameRes/gate.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case '?': {
			Tile* tile = new Tile("res/gameRes/bloque_fondo1_borde_derecha.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case '*': {
			Tile* tile = new Tile("res/gameRes/bloque_fondo1_borde_abajo.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case '-': {
			Tile* tile = new Tile("res/gameRes/bloque_fondo1_borde_arriba.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case '!': {
			Tile* tile = new Tile("res/gameRes/bloque_fondo1_borde_izquierda.png", x, y, 55, 55, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case 'J': {
			bossRoom = true;
			bossAlive = true;
			boss = new Boss1(x, y, game, this);
			// modificación para empezar a contar desde el suelo.
			boss->y = boss->y - boss->height / 2;
			space->addDynamicActor(boss);
			break;
		}
	}
}

void GameLayer::calculateScroll() {
	
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}
	// limite derecha
	if (player->x < mapWidth - (WIDTH + 100) * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}
	// Limite superior (vertical)
	if (player->y > HEIGHT * 0.3) {
		if (player->y - scrollY < HEIGHT * 0.3) {
			scrollY = player->y - HEIGHT * 0.3;
		}
	}
	// Limite inferior (vertical)
	if (player->y < mapHeight - HEIGHT * 0.3) {
		if (player->y - scrollY > HEIGHT * 0.7) {
			scrollY = player->y - HEIGHT * 0.7;
		}
	}
}

void GameLayer::createRandomItem(float x, float y) {

	std::random_device rd;  // Semilla basada en el hardware
	std::mt19937 gen(rd()); // Generador Mersenne Twister
	std::uniform_int_distribution<> distribucion(0, 5); // Rango 0 a 5
	int randomN = distribucion(gen);

	switch (randomN)
	{
		case 0: {
			Item* h = new HealthItem(x, y, game, player);
			items.push_back(h);
			space->addDynamicActor(h);
			break;
		}
		case 1: {
			Item* m = new ManaItem(x, y, game, player);
			items.push_back(m);
			space->addDynamicActor(m);
			break;
		}
		case 4:
		case 5: {
			Coin* c = new Coin(x, y, game, this);
			items.push_back(c);
			space->addDynamicActor(c);
			break;
		}
	}
}

void GameLayer::updateManaBar() {
	
	switch (player->mana)
	{
		case 0: { manabar = manabar0; break; }
		case 1: { manabar = manabar1; break; }
		case 2: { manabar = manabar2; break; }
		case 3: { manabar = manabar3; break; }
		case 4: { manabar = manabar4; break; }
	}
}

void GameLayer::draw() {

	calculateScroll();

	background->draw();

	if (game->currentLevel == 0 && levelRow == 0 && levelColumn == 0) {
		tutorialMessage1->draw(scrollX, scrollY);
		tutorialMessage2->draw(scrollX, scrollY);
		tutorialMessage3->draw(scrollX, scrollY);
		tutorialMessage4->draw(scrollX, scrollY);
		tutorialMessage5->draw(scrollX, scrollY);
		tutorialMessage6->draw(scrollX, scrollY);
		tutorialMessage7->draw(scrollX, scrollY);
	}

	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& trap : traps) {
		trap->draw(scrollX, scrollY);
	}

	for (auto const& ladder : ladders) {
		ladder->draw(scrollX, scrollY);
	}

	for (auto const& bi : breakableItems) {
		bi->draw(scrollX, scrollY);
	}

	for (auto const& item : items) {
		item->draw(scrollX, scrollY);
	}

	for (auto const& attack : attacks) {
		attack->draw(scrollX, scrollY);
	}

	for (auto const& eP : enemyAttacks) {
		eP->draw(scrollX, scrollY);
	}

	for (auto const& eB : enemyBombs) {
		eB->draw(scrollX, scrollY);
	}

	if (bossRoom && !bossAlive) {
		cup->draw(scrollX, scrollY);
	}
	player->draw(scrollX, scrollY);

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << coins;
	textcoins->content = ss.str();
	textcoins->draw();
	backgroundcoins->draw();

	// HUD
	healthFrame->draw();
	healthbar->draw(0,0);
	healthbar->updateHealth(player->healthPoints, game->maxHealth);
	heart->draw();
	updateManaBar();
	manabar->draw();

	if (bossRoom && boss != nullptr) {
		boss->draw(scrollX, scrollY);
		bossHF->draw();
		bossHB->draw(0, 0);
		bossHB->updateHealth(boss->currentHP, boss->maxHP);
		bossName->draw();
	}

	if (game->input == game->inputMouse) {
		buttonJump->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonSpell->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonAttack->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonDash->draw();
		buttonPause->draw();
		buttonShield->draw();
		pad->draw(); // NO TIENEN SCROLL, POSICION FIJA
	}

	if (pause && !menuPause && levelStartMessage) {
		levelStartMessage->draw();
	}

	if (menuPause) {
		pause = true;
		pauseBackground->draw();
		buttonPlayPause->draw();
		buttonHomePause->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}
