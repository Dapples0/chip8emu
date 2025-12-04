#pragma once
#include <SDL2/SDL.h>
#include "constants.h"

class Display {
    public:
        Display();
        ~Display();
        void draw(uint32_t gfx[WIDTH * SCALE]);

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;

};