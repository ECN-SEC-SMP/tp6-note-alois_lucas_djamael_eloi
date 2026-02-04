# !/bin/bash
sudo apt install libsfml-dev build-essential cmake -y
rm -rf ./build
mkdir -p ./build
cd ./build
cmake ..
make
./Otrio_Game