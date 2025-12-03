#include "Chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <bitset>
using namespace std;

void Chip8::initialise() {
    pc = 0x200;
    opcode = 0;
    I = 0;
    stackPointer = 0;

    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        gfx[i] = 0;
    }

    for (int i = 0; i < MAX_SIZE; ++i) {
        stack[i] = 0;
        registerV[i] = 0;
    }

    for (int i = 0; i < MEMORY_SIZE; ++i) {
        memory[i] = 0;
    }

    // Load font into memory
    for (int i = 0; i < FONT_SIZE; ++i) {
        memory[i + FONT_START_ADDRESS] = font[i];
    }

    delay_timer = 0;
    sound_timer = 0;
}


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

    if (res > (4096 - 512)) {
        cerr << "ROM too big\n";
        exit(-1);
    }

    for (int i = 0; i < (4096 - 512); ++i) {
        memory[i + 512] = buffer[i];
    }

    fclose(fp);
    free(buffer);
    
}

void Chip8::emulateCycle(SDL_Renderer *renderer, SDL_Texture *texture) {
    opcode = memory[pc] << 8 | memory[pc + 1];
    I = opcode & 0x0FFF;
    pc += 2;

    // Extract operations
    uint8_t vX = (opcode & 0x0F00) >> 8;
    uint8_t vY = (opcode & 0x00F0) >> 4;
    uint8_t nnn = (opcode & 0x0FFF);
    uint8_t nn = (opcode & 0x00FF); // same as kk
    uint8_t n = (opcode & 0x000F); // n is height

    executeOperation(opcode, vX, vY, nnn, nn, n);

    // Do delays here
    return;
}

void Chip8::updateGraphics() {

    return;
}

void Chip8::storeKey() {

    return;
}

void executeOperation(unsigned short opcode, uint8_t vX, uint8_t vY, uint8_t n, uint8_t nn, uint8_t nnn) {
    switch (opcode & 0xF000) {
        case 00E0:

    }
}

