#include <SDL2/SDL.h>

#pragma once


class Window {
    public:
        Window();
        ~Window();
        SDL_Window *getWindow();
    private:
        SDL_Window *windows;
};