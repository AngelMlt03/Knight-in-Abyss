#include "ManaItem.h"
#include "GameLayer.h"

ManaItem::ManaItem(float x, float y, Game* game, Player* p)
    : Item("res/gameRes/manaPocion.png", x, y, 40, 40, game) {

    player = p;
    audioOnCollision = Audio::createAudio("res/soundEffects/efecto_mana.wav", false);
}

void ManaItem::onCollision() {

    audioOnCollision->play(); // Sonido al coger poción de mana
    player->getMana();
}
