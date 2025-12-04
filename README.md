# Chip8 Emulator

## About
Chip8 emulator written in C++ with SDL2. Currently does not have timer and sound support. All in all, this emulator *should* pass most Chip8 test suites. 

## How to run
In the root directory, compile the program by running (make sure to install all dependencies i.e. SDL2):
```
make
```
Then
```
./chip8
```
To run the program.

## Changing ROMS
*All roms can be found in the _**testroms**_ folder  in the root directory.*

ROMS can be changed by editing the filename passed in 
```
chip8.load("testroms/your_rom");
```
and compiling the program again with
```
make
```
## Credits
https://austinmorlan.com/posts/chip8_emulator/ | For debugging certain opcode operations.

https://github.com/jjnietoc/chip8 | *Heavily drew inspiration* on SDL intergration and DXYN operation.