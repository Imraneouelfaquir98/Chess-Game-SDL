	#include "../include/Interface.hpp"

	int main(int argc, char const *argv[])
	{
		Interface *interface = new Interface();
		interface->firstWindow();
		return 0;
	}

	//g++ -c Interface.cpp Board.cpp Move.cpp Engine.cpp main.cpp Evaluate.cpp Node.cpp MCTS.cpp `sdl2-config --cflags --libs`
	//g++ Interface.o Board.o Move.o Engine.o main.o Evaluate.o Node.o MCTS.o -o exe  `sdl2-config --cflags --libs` -lSDL2_image
