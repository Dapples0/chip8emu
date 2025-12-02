#include <iostream>
using namespace std;

#include "Display.h"
#include "Window.h"
#include "Chip8.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "usage: main.cpp chip8\n";
        return 1;
    }

    Chip8 chip8;
    chip8.initialise();
    chip8.load(argv[1]);

    Window window;
    Display display;
    display.render(window.getWindow());
    display.createTexture();

    // Command Loop
    uint32_t tick;
    SDL_Event event;
    while(true) {
        tick = SDL_GetTicks();

        // Check if there has been an event
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }

            if (event.type == SDL_KEYDOWN) {
                for (int i = 0; i < MAX_SIZE; ++i) {
                    if (event.key.keysym.sym == chip8.keymap[i]) {
                        chip8.key[i] = 1;
                    }
                }
            }

            if (event.type == SDL_KEYUP)  {
                for (int i = 0; i < MAX_SIZE; ++i) {
                    if (event.key.keysym.sym == chip8.keymap[i]) {
                        chip8.key[i] = 0;
                    }
                }
            }
        }

        chip8.emulateCycle(display.getRenderer(), display.getTexture());
    }




}