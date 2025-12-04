#include <iostream>
using namespace std;

#include "Chip8.h"
#include "Display.h"

#include <chrono>
#include <thread>


int main(void) {

    Chip8 chip8;
    chip8.load("testroms/4-flags.ch8");
    // 3-corax+.ch8 4-flags.ch8 5-quirks.ch8 6-keypad.ch8 Pong (1 player) (1).ch8 Tetris [Fran Dachille, 1991].ch8
    Display display;

    // Command Loop
    Uint32 start_time = SDL_GetTicks();
    bool running = true;
    while (running) {
        Uint32 cycleTime = SDL_GetTicks();
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                for (int i = 0; i < MAX_SIZE; i++)
                    if (event.key.keysym.sym == chip8.keymap[i]) {
                        chip8.key[i] = 1;
                    }
            }
            if (event.type == SDL_KEYUP) {
                for (int i = 0; i < MAX_SIZE; i++) {
                    if (event.key.keysym.sym == chip8.keymap[i]){
                        chip8.key[i] = 0;
                    }
                    
                }
            }
        }

        chip8.emulateCycle();

        display.draw(chip8.gfx);

        this_thread::sleep_for(std::chrono::microseconds(3000));
    }




}