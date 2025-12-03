#include <iostream>
using namespace std;

#include "Chip8.h"

#include <chrono>
#include <thread>


int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "usage: main.cpp chip8\n";
        cerr << argc << "\n";
        return 1;
    }

    Chip8 chip8;
    chip8.initialise();
    chip8.load(argv[1]);



    // Command Loop
    bool exit = false;
    while (!exit) {
        // this_thread::sleep_for(std::chrono::microseconds(1200));
        chip8.emulateCycle();


    }


}