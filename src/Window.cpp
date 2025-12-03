#include "Window.h"
#include <SDL2/SDL_video.h>

#include <iostream>
using namespace std;


Window::Window() {
    windows = SDL_CreateWindow("chip8",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                HEIGHT * WIDTH,
                                HEIGHT * SCALE,
                                SDL_WINDOW_SHOWN
                                );

    if (!windows) {
        cerr << "Could not create window\n";
        exit(-1);
    }
}

Window::~Window() {
    SDL_DestroyWindow(windows);
}

SDL_Window *(Window::getWindow)() {
    return windows;
}