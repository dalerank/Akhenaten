#!/usr/bin/env bash

CORES=$(sysctl -n hw.ncpu)

rm -rf build 2>/dev/null
mkdir build

cmake --build ./build --target clean -- -j"$CORES"
cmake -B build -DPNG_LIBRARY="/opt/homebrew/opt/libpng/lib"
cmake --build ./build -- -j"$CORES"

install_name_tool -add_rpath @loader_path build/akhenaten.app/Contents/MacOS/akhenaten

find build/_deps/sdl2_mixer-build/ -type f ! -type l -name 'libSDL2*' -exec /bin/cp {} build/akhenaten.app/Contents/MacOS/ \;