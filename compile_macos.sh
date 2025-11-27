#!/usr/bin/env bash

CORES=$(sysctl -n hw.ncpu)

rm -rf build 2>/dev/null
mkdir build

cmake --build ./build --target clean -- -j"$CORES"
cmake -B build -DPNG_LIBRARY="/opt/homebrew/opt/libpng/lib"
cmake --build ./build -- -j"$CORES"

set -x

install_name_tool -add_rpath @loader_path build/akhenaten.app/Contents/MacOS/akhenaten

cp build/_deps/sdl2_mixer-build/libSDL2_mixer-2.0.801.0.0.dylib build/akhenaten.app/Contents/MacOS/

