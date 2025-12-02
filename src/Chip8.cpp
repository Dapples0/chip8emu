#include "Chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;


unsigned char font[80] = {
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

void Chip8::initialise() {
    pc = 0x200;
    opcode = 0;
    I = 0;
    stackPointer = 0;

    for (int i = 0; i < 2048; ++i) {
        gfx[i] = 0;
    }

    for (int i = 0; i < 16; ++i) {
        stack[i] = 0;
        registerV[i] = 0;
    }

    for (int i = 0; i < 4096; ++i) {
        memory[i] = 0;
    }

    // Load font into memory
    for (int i = 0; i < 80; ++i) {
        memory[i] = font[i];
    }

    delay_timer = 0;
    sound_timer = 0;
}


void Chip8::load(const char *filename) {

    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        cerr << "Bad ROM";
        exit(-1);
    }

    // Get file size
    fseek(fp, 0 , SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    char *buffer = (char*)malloc(sizeof(char) * fileSize);

    size_t res = fread(buffer, sizeof(char), fileSize, fp);

    if (res != fileSize) {
        cerr << "Bad ROM";
        exit(-1);
    }
    cout << res;
    if (res > (4096 - 512)) {
        cerr << "ROM too big";
        exit(-1);
    }

    for (int i = 0; i < (4096 - 512); ++i) {
        memory[i + 512] = buffer[i];
    }

    fclose(fp);
    free(buffer);
    
}

void Chip8::emulateCycle() {

    return;
}

void Chip8::updateGraphics() {

    return;
}

void Chip8::storeKey() {

    return;
}


