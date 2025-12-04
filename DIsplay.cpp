#include <SDL2/SDL.h>
#include "constants.h"
#include "Display.h"
#include <iostream>
using namespace std;


Display::Display() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        cerr << "Could not initialise SDL\n";
        exit(1);
    }
    window = SDL_CreateWindow("chip-8",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, 
                                WIDTH * SCALE, 
                                HEIGHT * SCALE, 
                                SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cerr << "Could not create SDL window\n";
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetScale(renderer, SCALE, SCALE);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);



}

Display::~Display() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void Display::draw(uint32_t pixels[WIDTH*SCALE]) {
    SDL_UpdateTexture(texture,
                NULL,
                pixels,
                WIDTH*sizeof(uint32_t));
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer,
                texture,
                NULL,
                NULL);
    SDL_RenderPresent(renderer);
}