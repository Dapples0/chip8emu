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

        // Polls any events
        if (SDL_PollEvent(&event)) {
            
            // Quits SDL window on close press
            if(event.type == SDL_QUIT) {
                running = false;
            }

            // Sets held key to true
            if (event.type == SDL_KEYDOWN) {
                for (int i = 0; i < MAX_SIZE; i++)
                    if (event.key.keysym.sym == chip8.keymap[i]) {
                        chip8.key[i] = 1;
                    }
            }

            // Sets held key to false on release
            if (event.type == SDL_KEYUP) {
                for (int i = 0; i < MAX_SIZE; i++) {
                    if (event.key.keysym.sym == chip8.keymap[i]){
                        chip8.key[i] = 0;
                    }
                    
                }
            }
        }

        // Execute cycle
        chip8.emulateCycle();

        // Updates screen to reflect changes
        display.draw(chip8.gfx);

        this_thread::sleep_for(std::chrono::microseconds(3000));
    }


    return 0;

}