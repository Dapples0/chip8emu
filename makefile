CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

all:
	g++ src/main.cpp src/Chip8.cpp -o chip8