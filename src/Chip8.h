#pragma once
#include <cstdint>
#include "constants.h"
#include <SDL2/SDL.h>

class Chip8 {
    public:
        void initialise();
        void load(const char *filename);
        void emulateCycle(SDL_Renderer *renderer, SDL_Texture *texture);
        void updateGraphics();
        void storeKey();

        uint32_t gfx[WIDTH* HEIGHT]; // 2048
        uint8_t keymap[MAX_SIZE] = {
            SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4,
            SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9,
            SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e,
            SDLK_f
        };
        uint8_t key[MAX_SIZE];

    private:
        unsigned short opcode;
        unsigned char memory[MEMORY_SIZE];
        unsigned char registerV[MAX_SIZE];
        unsigned short I;
        unsigned short pc;
        unsigned char delay_timer;
        unsigned char sound_timer;
        unsigned short stack[MAX_SIZE];
        unsigned short stackPointer;
        unsigned char font[FONT_SIZE] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };


};

