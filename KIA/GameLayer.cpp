#include <iomanip>
#include <sstream> 

#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);
	
	gamePad = SDL_GameControllerOpen(0);
	init();
}

void GameLayer::init() {

	audioBackground = Audio::createAudio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	audioHit = Audio::createAudio("res/efecto_impacto.wav", false);

	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);
	buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonSpell = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);
	buttonAttack = new Actor("res/boton_disparo.png", WIDTH * 0.65, HEIGHT * 0.83, 100, 100, game);
	buttonDash = new Actor("res/boton_salto.png", WIDTH * 0.85, HEIGHT * 0.83, 100, 100, game);
	buttonPause = new Actor("res/boton_pausa.png", WIDTH * 0.85, HEIGHT * 0.10, 100, 100, game);

	pauseBackground = new Actor("res/fondo_pausa.png", WIDTH * 0.5, HEIGHT * 0.5, 600, 411, game);
	buttonPlayPause = new Actor("res/boton_play_pause.png", WIDTH * 0.42, HEIGHT * 0.52, 140, 133, game);
	buttonHomePause = new Actor("res/boton_home_pause.png", WIDTH * 0.58, HEIGHT * 0.52, 140, 133, game);

	tiles.clear(); // Vaciar por si reiniciamos el juego
	ladders.clear(); // Vaciar por si reiniciamos el juego
	attacks.clear(); // Vaciar por si reiniciamos el juego
	enemies.clear(); // Vaciar por si reiniciamos el juego

	space = new Space(1);
	scrollX = 0;
	scrollY = 0;

	//game->levelRow = 0;
	//game->levelColumn = 0;

	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, game);

	coins = 0;
	textcoins = new Text("hola", 120, 132, game);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << coins;
	textcoins->content = ss.str();

	backgroundcoins = new Actor("res/moneda.png", 42, 130, 36, 36, game);

	healthFrame = new Actor("res/healthFrame.png", 150, 42, 259, 42, game);
	heart = new Actor("res/corazon.png", 45, 42, 47, 42, game);
	healthbar = new HealthBar(game);
	manabar = new Actor("res/manaBar4.png", 90, 86, 139, 42, game);

	loadMap("res/" + to_string(game->currentLevel) + "_" + to_string(levelRow)
			+ "_" + to_string(levelColumn) + ".txt");
}

void GameLayer::changeRoom(int direction) {

	tiles.clear();
	ladders.clear();
	attacks.clear(); // Vaciar por si reiniciamos el 
	enemies.clear(); // Vaciar por si reiniciamos el juego

	space = new Space(1);

	loadMap("res/" + to_string(game->currentLevel) + "_" + to_string(levelRow)
		+ "_" + to_string(levelColumn) + ".txt");

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
	
	scrollY = 0;
}

void GameLayer::endLevel() {

	if (game->currentLevel < game->finalLevel) {
		game->currentLevel++;
		levelRow = 0;
		levelColumn = 0;
		changeRoom(0);
		// Pantalla nivel finalizado
	}
	else {
		// Lo que pasa al pasarte el juego
	}

	game->gold += coins;
	coins = 0;
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
			manabar = new Actor("res/manaBar" + to_string(player->mana) + ".png", 90, 86, 139, 42, game);
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
	bool buttonBack = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_BACK);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << "," << buttonBack << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	cout << "stickX" << stickX << endl;
	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		controlMoveX = 1;
	}
	else if (stickX < -4000) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}
	if (buttonA) {
		controlAttack = true;
	}
	else {
		controlAttack = false;
	}
	if (buttonB) {
		controlMoveY = -1; // Saltar
	}
	else {
		controlMoveY = 0;
	}
	if (buttonBack) {
		controlSpell = true;
	}
	else {
		controlSpell = false;
	}
}

void GameLayer::keysToControls(SDL_Event event) {

	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			menuPause = true;
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
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_k: // ataque
			controlAttack = false;
			break;
		case SDLK_l: // lanza hechizo
			controlSpell = false;
			break;
		case SDLK_SPACE:
			controlShield = false;
			break;
		case SDLK_LSHIFT:
			controlDash = false;
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
			// dash
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
			game->layer = game->menuLayer;
		}
		if (message && message->containsPoint(motionX, motionY)) {
			pause = false;
			delete message;
			message = nullptr;
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
		}
		if (buttonJump->containsPoint(motionX, motionY) == false) {
			controlMoveY = 0;
		}
		if (buttonAttack->containsPoint(motionX, motionY) == false) {
			controlAttack = false;
		}
		if (buttonDash->containsPoint(motionX, motionY)) {
			// dash
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
		}
		if (buttonJump->containsPoint(motionX, motionY)) {
			controlMoveY = 0;
		}
		if (buttonAttack->containsPoint(motionX, motionY)) {
			controlAttack = false;
		}
		if (buttonDash->containsPoint(motionX, motionY)) {
			// dash
		}
	}
}

void GameLayer::update() {

	if (pause) {
		return;
	}

	// Usar escudo
	player->usingShield = controlShield;

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
	if (cup->isOverlap(player)) {
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
		}
		message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		endLevel();
	}

	// Jugador se cae
	if (player->y > mapHeight + 80) {
		message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		init();
	}

	space->update();

	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
	}

	for (auto const& attack : attacks) {
		attack->update();
	}

	// Colisiones
	for (auto const& enemy : enemies) {

		if (enemy->isTopOverlap(player) && enemy->state != game->stateDying
			&& enemy->state != game->stateDead) {

			audioHit->play(); // Sonido de impacto
			enemy->impacted();
			coins++;
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(4) << coins;
			textcoins->content = ss.str();
			return;
		}
		if (player->isOverlap(enemy) && enemy->state != game->stateDying
			&& enemy->state != game->stateDead) {
			player->takeDamage(10);
			healthbar->updateHealth(player->healthPoints, game->maxHealth);
			if (player->healthPoints <= 0) {
				message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, game);
				pause = true;
				init();
				return;
			}
		}
	}

	// Colisiones , Player - Ladder

	for (auto const& ladder : ladders) {

		if (ladder->isOverlap(player)) {

			player->onLadder = true;
			return;
		}
		player->onLadder = false;
	}

	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Attack*> deleteAttacks;

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

	for (auto const& enemy : enemies) {
		for (auto const& attack : attacks) {
			if (enemy->isOverlap(attack)) {
				bool pInList = std::find(deleteAttacks.begin(),
					deleteAttacks.end(),
					attack) != deleteAttacks.end();

				if (!pInList) {
					deleteAttacks.push_back(attack);
				}

				enemy->impacted();
				audioHit->play(); // Sonido de impacto

				coins++;
				std::stringstream ss;
				ss << std::setfill('0') << std::setw(4) << coins;
				textcoins->content = ss.str();
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
}

void GameLayer::loadMap(string name) {

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
		case 'C': {
			cup = new Tile("res/copa.png", x, y, game);
			// modificación para empezar a contar desde el suelo.
			cup->y = cup->y - cup->height / 2;
			space->addDynamicActor(cup); // Realmente no hace falta
			break;
		}
		case 'S': {
			Enemy* enemy = new Summoner(x, y, game);
			// modificación para empezar a contar desde el suelo.
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			space->addDynamicActor(enemy);
			break;
		}
		case 'G': {
			Enemy* enemy = new Goomba(x, y, game);
			// modificación para empezar a contar desde el suelo.
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			space->addDynamicActor(enemy);
			break;
		}
		case 'J': {
			Enemy* enemy = new Jumper(x, y, game);
			// modificación para empezar a contar desde el suelo.
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			space->addDynamicActor(enemy);
			break;
		}
		case 'A': {
			Enemy* enemy = new Alien(x, y, game);
			// modificación para empezar a contar desde el suelo.
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			space->addDynamicActor(enemy);
			break;
		}
		case '1': {
			player = new Player(x, y, game);
			// modificación para empezar a contar desde el suelo.
			player->y = player->y - player->height / 2;
			space->addDynamicActor(player);
			break;
		}
		case 'R': {
			Tile* ladder = new Tile("res/ladder.png", x, y, game);
			// modificación para empezar a contar desde el suelo. 
			ladder->y = ladder->y - ladder->height / 2;
			ladders.push_back(ladder);
			break;
		}
		case '#': {
			Tile* tile = new Tile("res/bloque_tierra.png", x, y, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case 'P': {
			Tile* tile = new Tile("res/bloque_fondo1.png", x, y, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case '?': {
			Tile* tile = new Tile("res/bloque_fondo1_borde_derecha.png", x, y, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case '*': {
			Tile* tile = new Tile("res/bloque_fondo1_borde_abajo.png", x, y, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
			break;
		}
		case '-': {
			Tile* tile = new Tile("res/bloque_fondo1_borde_arriba.png", x, y, game);
			// modificación para empezar a contar desde el suelo.
			tile->y = tile->y - tile->height / 2;
			tiles.push_back(tile);
			space->addStaticActor(tile);
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
	if (player->x < mapWidth - WIDTH * 0.3) {
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
	if (player->y < mapHeight - HEIGHT * 0.3) {  // mapHeight es la altura del mapa
		if (player->y - scrollY > HEIGHT * 0.7) {
			scrollY = player->y - HEIGHT * 0.7;
		}
	}
}

void GameLayer::summonNewEnemy(int x, int y) {

	srand(time(nullptr));
	// Generamos un número aleatorio entre 0 y 2
	int randomType = rand() % 3;

	Enemy* enemy = nullptr;

	// Según el número aleatorio, se genera un tipo de enemigo
	switch (randomType) {
	case 0:
		enemy = new Goomba(x, y, game);
		break;
	case 1:
		enemy = new Alien(x, y, game);
		break;
	case 2:
		enemy = new Jumper(x, y, game);
		break;
	}
	enemies.push_back(enemy);
	space->addDynamicActor(enemy);
}

void GameLayer::draw() {

	calculateScroll();

	background->draw();

	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& ladder : ladders) {
		ladder->draw(scrollX, scrollY);
	}

	for (auto const& attack : attacks) {
		attack->draw(scrollX, scrollY);
	}

	cup->draw(scrollX, scrollY);
	player->draw(scrollX, scrollY);

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	textcoins->draw();
	backgroundcoins->draw();

	// HUD

	healthFrame->draw();
	healthbar->draw(0,0);
	heart->draw();
	manabar->draw();

	if (game->input == game->inputMouse) {
		buttonJump->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonSpell->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonAttack->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonDash->draw();
		buttonPause->draw();
		pad->draw(); // NO TIENEN SCROLL, POSICION FIJA
	}

	if (pause && !menuPause && message) {
		message->draw();
	}

	if (menuPause) {
		pause = true;
		pauseBackground->draw();
		buttonPlayPause->draw();
		buttonHomePause->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}
