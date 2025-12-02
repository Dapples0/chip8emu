CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

all:
	g++ src/*.cpp -o chip8 -lSDL2