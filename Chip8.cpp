#include "Chip8.h"
#include <fstream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <bitset>
#include <iostream>
using namespace std;

Chip8::Chip8() {
    pc = 0x200;
    I = 0;
    sp = 0;
    delay_timer = 0;
    sound_timer = 0;

    font = {
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

    keymap = {
        SDLK_1, SDLK_2, SDLK_3, SDLK_4,
        SDLK_q, SDLK_w, SDLK_e, SDLK_r,
        SDLK_a, SDLK_s, SDLK_d, SDLK_f,
        SDLK_z, SDLK_x, SDLK_c, SDLK_v,
    }; 
    // Clear display D:
    clearDisplay();

    // Initialises stack, registers, and key
    for (int i = 0; i < MAX_SIZE; ++i) {
        stack[i] = 0;
        registerV[i] = 0;
        // key[i] = 0; // May want to uncomment this
    }

    // Sets all elements to 0
    memory.fill(0);


    // Load font into memory
    copy(font.begin(), font.end(), memory.begin());
    
}

Chip8::~Chip8() {}


void Chip8::load(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        cerr << "Bad ROM\n";
        exit(-1);
    }

    // Get file size
    fseek(fp, 0 , SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    char *buffer = (char*)malloc(sizeof(char) * fileSize);
    
    size_t res = fread(buffer, sizeof(char), fileSize, fp);
    if (res != (size_t)fileSize) {
        cerr << "Bad ROM\n";
        exit(-1);
    }

	if((4096-512) > fileSize) {
		for(int i = 0; i < fileSize; ++i)
			memory[i + 512] = buffer[i];
	}
	else {
        cerr << "Rom too big\n";
    }

	
	fclose(fp);
	free(buffer);

}

void Chip8::emulateCycle() {
    uint16_t opcode = memory[pc] << 8 | memory[pc + 1];
    // Extract operations
    uint8_t vX = (opcode & 0x0F00) >> 8;
    uint8_t vY = (opcode & 0x00F0) >> 4;
    uint16_t nnn = opcode & 0x0FFF; 
    uint8_t nn = opcode & 0x0FF; // same as kk
    uint8_t n = opcode & 0x0F; // height

    
    pc += 2;

    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x000F) {
                case 0x0000: // 00E0 - Clears the screen
                    clearDisplay();
                break;
                case 0x000E: // Returns from subrotinez
                    --sp;
                    pc = stack[sp];
                break;
            }
        break;
        case 0x1000: // Jumps to addresss NNN
            pc = nnn;
        break;

        case 0x2000: // 2NNN - Calls subroutine at NNN
            stack[sp] = pc;
            ++sp;
            pc = nnn;
        break;
        
        case 0x3000: // 3XNN - Skips the next instruction set if vX equals NN
            if (registerV[vX] == nn) {
                pc += 2;
            }
        break;
        
        case 0x4000: // Skips the next instruction if vX does not equal NN
            if (registerV[vX] != nn) {
                pc += 2;
            }
        break;
        case 0x5000: // Skips the next instruction if vX equals vY
            if (registerV[vX] == registerV[vY]) {
                pc += 2;
            }
        break;

        case 0x6000: // 6XNN - Sets vX to NN
            registerV[vX] = nn;
        break;

        case 0x7000: // 7XNN - Adds NN to vX *carry flag is not changed)
            registerV[vX] += nn;
        break;

        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000: // 8XY0 - sets vX to the value of vY
                    registerV[vX] = registerV[vY];
                break;
                case 0x0001: // 8XY1 - sets vX to vX OR vY 
                    registerV[vX] = (registerV[vX] | registerV[vY]);

                break;

                case 0x0002: // 8XY2 - sets vX to vX AND xY
                    registerV[vX] = (registerV[vX] & registerV[vY]);
                break;

                case 0x0003: // 8XY3 -  sets vX to vX XOR vY
                    registerV[vX] = (registerV[vX] ^ registerV[vY]);
                break;

                case 0x0004: // 8XY4 - Adds vY to vX. VF is set to 1 when there's an overflow, and to 0 when there is not
                {
                    uint16_t res = registerV[vX] += registerV[vY];

                    if (res > 255) {
                        registerV[MAX_SIZE - 1] = 1;
                    } else {
                        registerV[MAX_SIZE - 1] = 0;
                    }

                    registerV[vX] = res & 0xFF;
                }
                break;
                case 0x0005: // 8XY4 - Subtracts vY from vX. VF is set to 0 when there's an underflow, and to 1 when there is not
                    if (registerV[vY] > registerV[vX]) {
                        registerV[MAX_SIZE - 1] = 0;
                    } else {
                        registerV[MAX_SIZE - 1] = 1;
                    }
                    registerV[vX] -= registerV[vY];
                break;

                case 0x0006: // 8XY6 - Shifts vX to the right by 1, then stores the least significant bit of vX prior to the shift into VF
                    registerV[MAX_SIZE - 1] = (registerV[vX] & 0x1);

                    registerV[vX] >>= 1;

                break;
                
                case 0x0007: // 8XY7 - Sets vX to vY minus vX. VF is set to 0 when there's an underflow, and 1 when there is not
                    if (registerV[vX] > registerV[vY]) {
                        registerV[MAX_SIZE - 1] = 0;
                    } else {
                        registerV[MAX_SIZE - 1] = 1;
                    }
            
                    registerV[vX] = registerV[vY] - registerV[vX];        
                break;
                
                case 0x000E: // 8XYE - Shifts vX to the left by 1, then sets VF to 1 if the most significant bit of vX prior to that shift was set, or to 0 if it was unset
                    registerV[MAX_SIZE - 1] = (registerV[vX] & 0x80) >> 7;
                    registerV[vX] <<= 1;
                break;

            }
        break;

        case 0x9000: // 9XY0 - Skips the next instruction if vX does not equal to vY
            if (registerV[vX] != registerV[vY]) {
                pc += 2;
            }
        break;

        case 0xA000: // ANNN - sets I to the address NNN
            I = nnn;
        break;

        case 0xB000: //BNNN - Jumps to the address NNN plus v0
            pc = nnn + registerV[0];
        break;

        case 0xC000: // CXNN - Sets vX to the result of a bitwise AND operation on a random number (0-255) and NN
            registerV[vX] = (randGen() & nn);
        break;

        case 0xD000: // DXYN - Draws a sprite at (vX, vY) with a width of 8 pixels and height of N pixels. VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that does not happen
            {
            registerV[MAX_SIZE - 1] = 0;

            for (int row = 0; row < n; ++row) {
                for (int col = 0; col < 8; ++col) {
                    uint8_t pixel = (memory[I + row] & (0x80 >> col)) != 0;
                    if (pixel) {
                        int pos = (registerV[vX] + col) % WIDTH + ((registerV[vY] + row) % HEIGHT) * WIDTH;
                        if (gfx[pos] == 0xFFFFFFFF) { // Collision detection
                            registerV[MAX_SIZE - 1] = 1;
                            gfx[pos] = 0xFF000000;
                        } else {
                            gfx[pos] = 0xFFFFFFFF;
                        }
                    }
                }
            }
            }


        break;

        case 0xE000:
            switch (opcode & 0x00FF) {
                case 0x009E: // EX9E - Skips the next instruction if the key stored in vX is pressed
                    if (key[registerV[vX]]) {
                        pc += 2;
                    }
                break;
                case 0x00A1: // EXA1 - Skips the next instruction if the key stored in vX is not pressed
                    if (!key[registerV[vX]]) {
                        pc += 2;
                    }
                break;
            }
        break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007: // FX07 - sets vX to the value to the delay timer
                    registerV[vX] = delay_timer;
                break;

                case 0x000A: // FX0A - A key press is awaited, and then stored in vX
                    {
                    bool keyPress = false;
                    for (int i = 0; i < MAX_SIZE; ++i) {
                        if (key[i] != 0) {
                            registerV[vX] = i;
                            keyPress = true;
                        }
                    }

                    if (!keyPress) {
                        // pc -= 2;
                        return;
                    }
                    }

                break;

                case 0x0015: // 0xFX15 - sets delay timer to vX
                    delay_timer = registerV[vX];
                break;
                
                case 0x0018: // 0xFX18 - sets sound timer to vX
                    sound_timer = registerV[vX];
                break;

                case 0x001E: // 0xFX1E - adds vX to I. VF is not affected
                    I += registerV[vX];
                break;

                case 0x0029: // FX29 - Sets I to the location of the sprite for the charactrer in vX
                    // I = FONT_START_ADDRESS + (5 * registerV[vX]);
                    I = 5 * registerV[vX];
                break;

                case 0x0033: // FX33 - Stores the binary-coded decimal representation of vX, with the hundreds digit in memory location in I, the tens digit at location I + 1, and the ones digit at location I + 2  
                    memory[I] = registerV[vX] / 100;
                    memory[I + 1] = (registerV[vX]  / 10) % 10;
                    memory[I + 2] = registerV[vX]  % 10;
                                
                break;

                case 0x0055: // FX55 - Stores from v0 to vX (inclusive) in memory, starting at address I. The offset from I is increased by 1 for each value written, but I is left unmodified
                    for (int i = 0; i < vX; ++i) {
                        memory[I + i] = registerV[i];
                    }
                break;

                case 0x0065: // FX65 - Fills from v0 to vX (inclusive) with values from memory, starting at address I. The offset from I is increased by 1 for each value read, but I is left unmodified
                    for (int i = 0; i < vX; ++i) {
                        registerV[i] = memory[I + i];
                    }
                    I += vX + 1;

                break;
            }       
        break;

        default:
        break;
    }
    // Do delays here
    if (delay_timer > 0) {
        --delay_timer;
    }

    if (sound_timer > 0) {
        --sound_timer;
    }
    return;
}

void Chip8::clearDisplay() {
    // Clear screen
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        gfx[i] = 0;
    }
 
}

uint8_t Chip8::randGen() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 255);

    return (uint8_t)dist(gen);

}
