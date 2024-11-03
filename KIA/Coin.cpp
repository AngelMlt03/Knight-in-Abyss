#include "Coin.h"
#include "GameLayer.h"

Coin::Coin(float x, float y, Game* game, GameLayer* gl)
    : Item("res/gameRes/moneda.png", x, y, game) {

    gameLayer = gl;
    audioOnCollision = Audio::createAudio("res/soundEffects/efecto_moneda.wav", false);
}

void Coin::onCollision() {

    audioOnCollision->play(); // Sonido al coger la moneda
    gameLayer->coins += 10; // Incrementa los puntos

}