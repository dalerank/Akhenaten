#!/usr/bin/env bash

### Compile script for macOS as Universal Binary
###
### Dependencies on ARM Device:
### /opt/homebrew/bin/brew install cmake git
###
### Dependencies on Intel Device:
### /usr/local/bin/brew install cmake git

if [ "$1" == "" ]; then
    echo "Usage: ./compile_macos.sh [arm64|x86_64|universal|clean]"
    exit 1
fi

if [ "$1" != "arm64" ] && [ "$1" != "x86_64" ] && [ "$1" != "universal" ] && [ "$1" != "clean" ]; then
    echo "Invalid argument: $1"
    echo "Usage: ./compile_macos.sh [arm64|x86_64|universal|clean]"
    exit 1
fi

CORES=$(sysctl -n hw.ncpu)

function arm64 {
    mkdir build-arm64
    cmake -B build-arm64 \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=14.0
    cmake --build build-arm64 -- -j"$CORES"
}

function x86_64 {
    mkdir build-x86_64
    cmake -B build-x86_64 \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_OSX_ARCHITECTURES=x86_64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=14.0
    cmake --build build-x86_64 -- -j"$CORES"
}

function universal {
    rm -r build 2>/dev/null
    mkdir build 2>/dev/null
    arm64
    x86_64  
    lipo -create build-arm64/akhenaten.app/Contents/MacOS/akhenaten build-x86_64/akhenaten.app/Contents/MacOS/akhenaten -output /private/tmp/akhenaten_universal
    cp -R build-arm64/akhenaten.app build/akhenaten.app
    cp /private/tmp/akhenaten_universal build/akhenaten.app/Contents/MacOS/akhenaten
    chmod +x build/akhenaten.app/Contents/MacOS/akhenaten
    rm /private/tmp/akhenaten_universal
}

function clean {
    rm -rf build-arm64 build-x86_64 build 2>/dev/null
}

$1