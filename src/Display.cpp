#include "Display.h"
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
 

Display::Display() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Could not initialise SDL\n";
        exit(-1);
    }

}

Display::~Display() {
    SDL_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);

}

void Display::render(SDL_Window *window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetScale(renderer, SCALE, SCALE);
}


void Display::draw(SDL_Texture *texture, uint32_t gfx[WIDTH * SCALE]) {
    SDL_UpdateTexture(texture, NULL, gfx, WIDTH*sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Display::createTexture() {
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

SDL_Renderer *Display::getRenderer() {
    return renderer;
}

SDL_Texture *Display::getTexture() {
    return texture;
}
