#!/bin/sh
sudo apt -qq update
# Note: libpng-dev is not needed as libpng is built from source via FetchContent
# Installing it could cause conflicts with the bundled 
sudo apt install --yes git cmake build-essential
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cd ..
