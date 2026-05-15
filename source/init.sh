#! /bin/bash

g++ -fsanitize=address -g3 -x c++ -o a.out *.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

./a.out $1