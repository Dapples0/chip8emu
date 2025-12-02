#include "Chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

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

    if (res != (size_t)fileSize) {
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


