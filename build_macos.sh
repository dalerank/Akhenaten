#!/usr/bin/env bash

CORES=$(sysctl -n hw.ncpu)

cmake --build ./build --target clean -- -j"$CORES"

cmake -B build \
  -DCMAKE_C_FLAGS="-I/opt/homebrew/include/SDL2 -UTARGET_OS_MAC -U__MWERKS__ -Uapplec -UTHINK_C -U__SC__" \
  -DCMAKE_CXX_FLAGS="-I/opt/homebrew/include/SDL2" \
  -DCMAKE_EXE_LINKER_FLAGS="-L/opt/homebrew/lib" \
  -DCMAKE_PREFIX_PATH="/opt/homebrew"

cmake --build ./build -- -j"$CORES"

cd build/akhenaten.app/Contents/MacOS

mkdir ../Frameworks
cp -R "$HOME"/Library/Frameworks/SDL2.framework ../Frameworks/
cp -R "$HOME"/Library/Frameworks/SDL2_mixer.framework ../Frameworks/

install_name_tool -add_rpath "@executable_path/../Frameworks" akhenaten
