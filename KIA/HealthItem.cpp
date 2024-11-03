#include "HealthItem.h"
#include "GameLayer.h"

HealthItem::HealthItem(float x, float y, Game* game, Player* p)
    : Item("res/gameRes/corazon.png", x, y, game) {

    player = p;
    //audioOnCollision = Audio::createAudio("res/soundEffects/efecto_moneda.wav", false);
}

void HealthItem::onCollision() {

    //audioOnCollision->play(); // Sonido al coger la vida
    player->heal();
}