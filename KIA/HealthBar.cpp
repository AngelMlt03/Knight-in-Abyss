#include "HealthBar.h"

HealthBar::HealthBar(Game* game) 
	: Actor("res/healthBar.png", 55, 21, 226, 42, game) {

}

void HealthBar::updateHealth(float currentHealth, float maxHealth) {
    // Calculamos el porcentaje de vida
    healthPercentage = currentHealth / maxHealth;

    // Ajustamos el ancho de la barra según el porcentaje
    width = 226 * healthPercentage;  // El ancho de la barra se escala según el porcentaje de salud

	
}

void HealthBar::draw(float scrollX, float scrollY) {

	// Recorte en el fichero de la imagen
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth; // texture.width;
	source.h = fileHeight; // texture.height;
	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	destination.w = width;
	destination.h = height;
	// Modificar para que la referencia sea el punto central

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}