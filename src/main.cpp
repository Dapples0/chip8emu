#include <iostream>
using namespace std;

#include "Chip8.h"

Chip8 chip8;

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "usage: main.cpp chip8";
        return 1;
    }


    chip8.intialise();
    chip8.load(argv[1]);
}