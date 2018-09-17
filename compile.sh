
#!/bin/bash

## Compile our two program files
g++ -std=c++11 -Ofast -march=native -o code main.cpp player.cpp map.cpp possible_moves.cpp
