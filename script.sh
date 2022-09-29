#!/bin/bash

g++ impl1.cpp main.cpp reusable.cpp -o impl1
g++ impl2.cpp main.cpp reusable.cpp -o impl2

x=$(./impl1 $1 $2)
y=$(./impl2 $1 $2)

echo "Score 1: $x"
echo "Score 2: $y"
