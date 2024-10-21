#include "Text.h"

Text::Text(string content, float x, float y, Game* game) {
	this->content = content;
	this->x = x;
	this->y = y;
	this->game = game;
}

void Text::draw() {
    // Definir colores: borde negro y texto dorado
    SDL_Color borderColor = { 0, 0, 0, 255 };    // Negro
    SDL_Color textColor = { 255, 215, 0, 255 };  // Amarillo dorado (#FFD700)

    // Crear superficie y textura para el borde negro
    SDL_Surface* borderSurface = TTF_RenderText_Blended(game->font, content.c_str(), borderColor);
    SDL_Texture* borderTexture = SDL_CreateTextureFromSurface(game->renderer, borderSurface);

    // Crear superficie y textura para el texto dorado
    SDL_Surface* textSurface = TTF_RenderText_Blended(game->font, content.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);

    // Definir el rectángulo para posicionar el texto
    SDL_Rect rect;
    rect.x = x - textSurface->w / 2;
    rect.y = y - textSurface->h / 2;
    rect.w = textSurface->w;
    rect.h = textSurface->h;

    // Renderizar el borde negro con pequeños desplazamientos para simular el contorno
    int borderThickness = 3;  // Grosor del borde
    SDL_Rect borderRect = rect;

    // Renderizar alrededor (arriba, abajo, izquierda, derecha y las diagonales)
    for (int dx = -borderThickness; dx <= borderThickness; ++dx) {
        for (int dy = -borderThickness; dy <= borderThickness; ++dy) {
            // Evitar el centro para que no solape con el texto dorado
            if (dx != 0 || dy != 0) {
                borderRect.x = rect.x + dx;
                borderRect.y = rect.y + dy;
                SDL_RenderCopy(game->renderer, borderTexture, NULL, &borderRect);
            }
        }
    }

    // Renderizar el texto dorado en el centro
    SDL_RenderCopy(game->renderer, textTexture, NULL, &rect);

    // Liberar las superficies y texturas
    SDL_FreeSurface(borderSurface);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(borderTexture);
    SDL_DestroyTexture(textTexture);
}

