#include <random>

#include "BreakableItem.h"
#include "GameLayer.h"

BreakableItem::BreakableItem(float x, float y, Game* game, int random)
    : Item(getSprite(random), x, y, getWidth(random), getHeight(random), game) {

    //audioOnCollision = Audio::createAudio("res/soundEffects/efecto_moneda.wav", false);
}

string BreakableItem::getSprite(int random) {

    cout << to_string(random);
    return "res/gameRes/breakableItem" + to_string(random) + ".png";
}

int BreakableItem::getWidth(int random) {

    int w = 40;
    cout << to_string(random);
    switch (random)
    {
        case 0:
        case 1:
        case 2: {
            w = 80;
            break;
        }
        case 3: {
            w = 90;
            break;
        }
    }

    return w;
}

int BreakableItem::getHeight(int random) {

    int h = 70;
    cout << to_string(random);
    switch (random)
    {
        case 0: {
            h = 65;
            break;
        }
        case 1:
        case 2: {
            h = 120;
            break;
        }
        case 3: {
            h = 56;
            break;
        }
    }

    return h;
}

void BreakableItem::onCollision() {
    GameLayer* gameLayer = dynamic_cast<GameLayer*>(game->gameLayer);

    if (gameLayer) {  // Verifica que el casting fue exitoso
        //audioOnCollision->play(); // Sonido al coger la moneda

    }
}
