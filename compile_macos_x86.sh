#!/usr/bin/env bash

MAIN_DIR="$PWD"

CORES=$(sysctl -n hw.ncpu)

rm -rf build 2>/dev/null
mkdir build

function assemble_package()
{
	cd build/akhenaten.app/Contents/MacOS
	mkdir ../Frameworks Data 2>/dev/null
	
	cp ../../../../data/* Data/
	cp ../../../../res/macos/launch.sh .
	chmod +x launch.sh
}

function compile_x86_64()
{
	export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH"
	export LDFLAGS="-L/usr/local/lib"
	export CFLAGS="-I/usr/local/include"
	export CPPFLAGS="-I/usr/local/include"

	cmake --build ./build --target clean -- -j"$CORES"
	cmake -B build -DCMAKE_OSX_ARCHITECTURES="x86_64" -DCMAKE_C_FLAGS="-UTARGET_OS_MAC -U__MWERKS__ -Uapplec -UTHINK_C -U__SC__"
	cmake --build ./build -- -j"$CORES"
	assemble_package
}
compile_x86_64


