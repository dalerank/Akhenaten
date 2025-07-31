#!/usr/bin/env bash

./update-workspace-mac.sh

cmake --build ./build --target clean
cmake -B build -DCMAKE_C_FLAGS="-UTARGET_OS_MAC -U__MWERKS__ -Uapplec -UTHINK_C -U__SC__"
cmake --build ./build

cd build/akhenaten.app/Contents/MacOS

mkdir ../Frameworks
cp -R "$HOME"/Library/Frameworks/SDL2.framework ../Frameworks/
cp -R "$HOME"/Library/Frameworks/SDL2_mixer.framework ../Frameworks/

install_name_tool -add_rpath "@executable_path/../Frameworks" akhenaten
