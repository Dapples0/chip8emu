#pragma once


class Chip8 {
    public:
        void intialise();
        void load();
        void emulateCycle();
        void updateGraphics();
        void storeKey();
};

