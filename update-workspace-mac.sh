#!/bin/zsh

mkdir -p ~/Library/Frameworks
mkdir build
cd build
mkdir tmp
FILENAME=SDL2-2.28.0.dmg
if [ ! -f "tmp/$FILENAME" ]
then
  curl "https://libsdl.org/release/$FILENAME" --output "tmp/$FILENAME"
  VOLUME=$(hdiutil attach "tmp/$FILENAME" | grep -o '/Volumes/.*')
  echo "Installing framework: /Volumes/SDL2/*.framework"
  cp -rp "$VOLUME"/*.framework ~/Library/Frameworks
  hdiutil detach "$VOLUME"
fi

FILENAME_MIXER=SDL2_mixer-2.8.0.dmg
if [ ! -f "tmp/$FILENAME_MIXER" ]
then
  curl "https://libsdl.org/projects/SDL_mixer/release/$FILENAME_MIXER" --output "tmp/$FILENAME_MIXER"
  VOLUME=$(hdiutil attach "tmp/$FILENAME_MIXER" | grep -o '/Volumes/.*')
  echo "Installing framework:" "/Volumes/SDL2_mixer"/*.framework
  cp -rp "$VOLUME"/*.framework ~/Library/Frameworks
  hdiutil detach "$VOLUME"
fi

FILENAME_IMAGE=SDL2_image-2.6.3.dmg
if [ ! -f "tmp/$FILENAME_IMAGE" ]
then
  curl "https://libsdl.org/projects/SDL_image/release/$FILENAME_IMAGE" --output "tmp/$FILENAME_IMAGE"
  VOLUME=$(hdiutil attach "tmp/$FILENAME_IMAGE" | grep -o '/Volumes/.*')
  echo "Installing framework:" "/Volumes/SDL2_image"/*.framework
  cp -rp "$VOLUME"/*.framework ~/Library/Frameworks
  hdiutil detach "$VOLUME"
fi

cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" .. -G "Unix Makefiles"
cd ..
