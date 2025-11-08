#!/usr/bin/env bash

MAIN_DIR="$PWD"

CORES=$(sysctl -n hw.ncpu)

if [ -z "$1" ]; then
  echo "Usage: ./compile_macos [arm64|x86_64|u2b]"
  exit 1
fi

if [ "$1" != "arm64" ] && [ "$1" != "x86_64" ] && [ "$1" != "u2b" ]; then
  echo "Error: Invalid option '$1'"
  echo "Usage: ./compile_macos [arm64|x86_64|u2b]"
  exit 1
fi

rm -rf build 2>/dev/null
mkdir build

function assemble_package()
{
	cd build/akhenaten.app/Contents/MacOS
	mkdir ../Frameworks Data 2>/dev/null
	
	cp -R "$HOME"/Library/Frameworks/SDL2.framework ../Frameworks/
	cp -R "$HOME"/Library/Frameworks/SDL2_mixer.framework ../Frameworks/
	cp ../../../../data/* Data/
	cp ../../../../res/macos/launch.sh .
	chmod +x launch.sh
}

function compile_arm64()
{
	export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:$PKG_CONFIG_PATH"
	export LDFLAGS="-L/opt/homebrew/lib"
	export CFLAGS="-I/opt/homebrew/include"
	export CPPFLAGS="-I/opt/homebrew/include"

	cmake --build ./build --target clean -- -j"$CORES"
	cmake -B build -DCMAKE_OSX_ARCHITECTURES="arm64" -DCMAKE_C_FLAGS="-UTARGET_OS_MAC -U__MWERKS__ -Uapplec -UTHINK_C -U__SC__"
	cmake --build ./build -- -j"$CORES"
	assemble_package	
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

function compile_u2b()
{
	rm -f /private/tmp/akhenaten_* 2>/dev/null
	compile_x86_64
	install_name_tool -add_rpath "@executable_path/../Frameworks" akhenaten
	mv akhenaten /private/tmp/akhenaten_x86
	cd "$MAIN_DIR"
	compile_arm64
	install_name_tool -add_rpath "@executable_path/../Frameworks" akhenaten
	mv akhenaten /private/tmp/akhenaten_arm
	lipo /private/tmp/akhenaten_arm /private/tmp/akhenaten_x86 -output akhenaten -create
	rm /private/tmp/akhenaten_*
}

if [ "$1" = "arm64" ]; then
	compile_arm64
fi

if [ "$1" = "x86_64" ]; then
	compile_x86_64
fi

if [ "$1" = "u2b" ]; then
	compile_u2b
fi

