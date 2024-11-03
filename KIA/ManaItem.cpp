#include "ManaItem.h"
#include "GameLayer.h"

ManaItem::ManaItem(float x, float y, Game* game, Player* p)
    : Item("res/gameRes/manaPocion.png", x, y, game) {

    player = p;
    //audioOnCollision = Audio::createAudio("res/soundEffects/efecto_moneda.wav", false);
}

void ManaItem::onCollision() {
    GameLayer* gameLayer = dynamic_cast<GameLayer*>(game->gameLayer);

    //audioOnCollision->play(); // Sonido al coger la moneda
    player->getMana();
}
