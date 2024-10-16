#include "HealthBar.h"

HealthBar::HealthBar(Game* game) 
	: Actor("res/healthBar.png", 100, 40, 160, 45, game) {

}

void HealthBar::updateHealth(float currentHealth, float maxHealth) {
    // Calculamos el porcentaje de vida
    healthPercentage = currentHealth / maxHealth;

    // Ajustamos el ancho de la barra seg�n el porcentaje
    width = 120 * healthPercentage;  // El ancho de la barra se escala seg�n el porcentaje de salud
}