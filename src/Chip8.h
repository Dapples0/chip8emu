#pragma once


class Chip8 {
    public:
        void initialise();
        void load(const char *filename);
        void emulateCycle();
        void updateGraphics();
        void storeKey();

        unsigned gfx[64 * 32]; // 2048
        unsigned char key[16];

    private:
        unsigned short opcode;
        unsigned char memory[4096];
        unsigned char registerV[16];
        unsigned short I;
        unsigned short pc;
        unsigned char delay_timer;
        unsigned char sound_timer;
        unsigned short stack[16];
        unsigned short stackPointer;

};

