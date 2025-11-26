#!/usr/bin/env bash

MAIN_DIR="$PWD"

CORES=$(sysctl -n hw.ncpu)

rm -rf build 2>/dev/null
mkdir build

cmake --build ./build --target clean -- -j"$CORES"
cmake -B build -DCMAKE_C_FLAGS="-UTARGET_OS_MAC -U__MWERKS__ -Uapplec -UTHINK_C -U__SC__"
cmake --build ./build -- -j"$CORES"

cd build/akhenaten.app/Contents/MacOS
mkdir Data 2>/dev/null

cp ../../../../data/* Data/
cp ../../../../res/macos/launch.sh .
chmod +x launch.sh	
