#include <iostream>
using namespace std;

#include "Chip8.h"
#include "Display.h"

#include <chrono>
#include <thread>


int main(int argc, char **argv) {

    Chip8 chip8;
    chip8.load("testroms/1-chip8-logo.ch8");
    Display display;


    // Command Loop
    bool exit = false;
    Uint32 start;
    while (!exit) {
        start = SDL_GetTicks();
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                break;
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
        // this_thread::sleep_for(std::chrono::microseconds(1200));
        chip8.emulateCycle();
        display.draw(chip8.gfx);
    }


}