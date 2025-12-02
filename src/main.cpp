#include <iostream>
using namespace std;

#include "Chip8.h"



int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "usage: main.cpp chip8";
        return 1;
    }

    Chip8 chip8;
    chip8.initialise();
    chip8.load(argv[1]);
}