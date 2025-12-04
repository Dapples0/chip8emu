CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

all:
	g++ *.cpp -o chip8 -lSDL2