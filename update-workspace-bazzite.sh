#!/bin/sh
brew install
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cd ..
