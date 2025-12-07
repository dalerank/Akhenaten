#!/usr/bin/env bash

CORES=$(sysctl -n hw.ncpu)

#rm -rf build 2>/dev/null
#mkdir build

cmake --build ./build --target clean -- -j"$CORES"
cmake -B build -DPNG_LIBRARY="/opt/homebrew/opt/libpng/lib"
cmake --build ./build -- -j"$CORES"
