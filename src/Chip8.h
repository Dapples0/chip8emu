#pragma once
#include <cstdint>
#include "constants.h"
#include <SDL2/SDL.h>

class Chip8 {
    public:
        void initialise();
        void load(const char *filename);
        void emulateCycle();
        void updateGraphics();
        void storeKey();

        uint32_t gfx[WIDTH* HEIGHT] = {}; // 2048
        uint8_t keymap[MAX_SIZE] = {
            SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4,
            SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9,
            SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e,
            SDLK_f
        };
        uint8_t key[MAX_SIZE] = {};

    private:
        void executeOperation(uint8_t vX, uint8_t vY, uint8_t n, uint8_t nn, uint8_t nnn);
        void clearDisplay();
        uint8_t randGen();
        uint16_t opcode;
        unsigned char memory[MEMORY_SIZE] = {};
        uint8_t registerV[MAX_SIZE] = {};
        uint16_t I = {};
        uint16_t pc = {};
        uint8_t delay_timer = {};
        uint8_t sound_timer = {};
        uint16_t stack[MAX_SIZE] = {};
        uint8_t sp = {};
        uint8_t font[FONT_SIZE] = {
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

