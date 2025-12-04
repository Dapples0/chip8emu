#include <iostream>
using namespace std;

#include "Chip8.h"

#include <chrono>
#include <thread>


int main(int argc, char **argv) {

    Chip8 chip8;
    chip8.load("testroms/1-chip8-logo.ch8");



    // Command Loop
    // bool exit = false;
    // while (!exit) {
    //     // this_thread::sleep_for(std::chrono::microseconds(1200));
    //     chip8.emulateCycle();


    // }


}