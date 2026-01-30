# !/bin/bash
sudo apt-get install libsfml-dev build-essential cmake -y
rm -rf ./build
mkdir -p ./build
cd ./build
cmake ..
make
./Otrio_Game