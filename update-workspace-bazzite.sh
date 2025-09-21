#!/bin/sh
brew install sdl2 sdl2_mixer sdl2_image
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cd ..
