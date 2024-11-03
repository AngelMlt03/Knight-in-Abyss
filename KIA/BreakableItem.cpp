#include "BreakableItem.h"
#include "GameLayer.h"

BreakableItem::BreakableItem(float x, float y, Game* game)
    : Item("res/ladder.png", x, y, game) {

    //audioOnCollision = Audio::createAudio("res/efecto_moneda.wav", false);
}

void BreakableItem::onCollision() {
    GameLayer* gameLayer = dynamic_cast<GameLayer*>(game->gameLayer);

    if (gameLayer) {  // Verifica que el casting fue exitoso
        //audioOnCollision->play(); // Sonido al coger la moneda

    }
}
