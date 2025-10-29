#!/usr/bin/env bash

if [ -z "$1" ]; then
  echo "Usage: ./compile_macos [arm64 | x86_64]"
  exit 1
fi

if [ "$1" != "arm64" ] && [ "$1" != "x86_64" ]; then
  echo "Error: Invalid architecture '$1'"
  echo "Usage: ./compile_macos [arm64 | x86_64]"
  exit 1
fi

CORES=$(sysctl -n hw.ncpu)

cmake --build ./build --target clean -- -j"$CORES"
cmake -B build -DCMAKE_OSX_ARCHITECTURES="$1" -DCMAKE_C_FLAGS="-UTARGET_OS_MAC -U__MWERKS__ -Uapplec -UTHINK_C -U__SC__"
cmake --build ./build -- -j"$CORES"

cd build/akhenaten.app/Contents/MacOS
mkdir ../Frameworks Data 2>/dev/null

cp -R "$HOME"/Library/Frameworks/SDL2.framework ../Frameworks/
cp -R "$HOME"/Library/Frameworks/SDL2_mixer.framework ../Frameworks/
cp ../../../../data/* Data/

install_name_tool -add_rpath "@executable_path/../Frameworks" akhenaten
