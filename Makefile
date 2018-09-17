 all: main.cpp player.cpp possible_moves.cpp map.cpp
	  g++ -std=c++11 -o main main.cpp player.cpp possible_moves.cpp map.cpp
