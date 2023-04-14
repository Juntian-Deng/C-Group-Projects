#!/bin/bash
g++ -o main -ISFML-2.5.1/include -LSFML-2.5.1/lib main.cpp -lsfml-graphics -lsfml-window -lsfml-system 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/SFML-2.5.1/lib:
./main