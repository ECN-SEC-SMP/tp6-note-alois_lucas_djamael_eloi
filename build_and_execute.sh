#!/bin/bash
sudo apt-get install libsfml-dev
sudo apt-get install build-essential
rm -rf build
mkdir -p build
cd build
cmake ..
make
./Otrio_Game