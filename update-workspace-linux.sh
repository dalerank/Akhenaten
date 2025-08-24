#!/bin/sh
sudo apt -qq update
sudo apt install --yes git cmake build-essential libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cd ..
