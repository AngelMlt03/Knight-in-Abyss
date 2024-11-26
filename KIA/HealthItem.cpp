#include "HealthItem.h"
#include "GameLayer.h"

HealthItem::HealthItem(float x, float y, Game* game, Player* p)
    : Item("res/gameRes/corazon.png", x, y, 46, 40, game) {

    player = p;
    audioOnCollision = Audio::createAudio("res/soundEffects/efecto_curacion.wav", false);
}

void HealthItem::onCollision() {

    audioOnCollision->play(); // Sonido al coger la vida
    player->heal();
}