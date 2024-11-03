#include <random>

#include "BreakableItem.h"
#include "GameLayer.h"

BreakableItem::BreakableItem(float x, float y, Game* game)
    : Item(getSprite(), x, y, game) {

    //audioOnCollision = Audio::createAudio("res/soundEffects/efecto_moneda.wav", false);
}

string BreakableItem::getSprite() {

    std::random_device rd;  // Semilla basada en el hardware
    std::mt19937 gen(rd()); // Generador Mersenne Twister
    std::uniform_int_distribution<> distribucion(0, 5); // Rango 0 a 5
    int randomN = distribucion(gen);

    return "res/breakableItem" + to_string(randomN) + ".png";
}

void BreakableItem::onCollision() {
    GameLayer* gameLayer = dynamic_cast<GameLayer*>(game->gameLayer);

    if (gameLayer) {  // Verifica que el casting fue exitoso
        //audioOnCollision->play(); // Sonido al coger la moneda

    }
}
