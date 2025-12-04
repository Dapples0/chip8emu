#pragma once
#include <cstdint>
#include "constants.h"
#include <SDL2/SDL.h>
#include <array>

class Chip8 {
    public:
        Chip8();
        ~Chip8();
        void load(const char *filename);
        void emulateCycle();
        void updateGraphics();
        void storeKey();

        
        std::array<uint8_t, MAX_SIZE> keymap;
        uint8_t key[MAX_SIZE];
        uint32_t gfx[WIDTH* HEIGHT] = {}; // 2048
    private:
        void executeOperation(uint8_t vX, uint8_t vY, uint8_t n, uint8_t nn, uint8_t nnn);
        void clearDisplay();
        uint8_t randGen();
        uint16_t opcode;
        std::array<uint8_t, MEMORY_SIZE> memory;
        uint8_t registerV[MAX_SIZE] = {};
        uint16_t I;
        uint16_t pc;
        uint8_t delay_timer;
        uint8_t sound_timer;
        uint16_t stack[MAX_SIZE];
        uint8_t sp;
        std::array<uint8_t, FONT_SIZE> font;
        

};

