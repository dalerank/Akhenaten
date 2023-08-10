#!/usr/bin/env bash

mkdir -p ~/Library/Frameworks
mkdir build
cd build
local FILENAME=SDL2-2.28.0.dmg
if [ ! -f "tmp/$FILENAME" ]
then
  curl -o "https://libsdl.org/release/$FILENAME" "tmp/$FILENAME"
  local VOLUME=$(hdiutil attach "tmp/$FILENAME" | grep -o '/Volumes/.*')
  echo "Installing framework:" "/Volumes/SDL2"/*.framework
  cp -rp "$VOLUME"/*.framework ~/Library/Frameworks
  hdiutil detach "$VOLUME"
fi

local FILENAME_MIXER=SDL2_mixer-2.0.4.dmg
if [ ! -f "tmp/$FILENAME_MIXER" ]
then
  curl -o "https://libsdl.org/projects/SDL_mixer/release/$FILENAME_MIXER" "tmp/$FILENAME_MIXER"
  local VOLUME=$(hdiutil attach "tmp/$FILENAME_MIXER" | grep -o '/Volumes/.*')
  echo "Installing framework:" "/Volumes/SDL2_mixer"/*.framework
  cp -rp "$VOLUME"/*.framework ~/Library/Frameworks
  hdiutil detach "$VOLUME"
fi

local FILENAME_IMAGE=SDL2_image-2.6.3.dmg
if [ ! -f "tmp/$FILENAME_IMAGE" ]
then
  curl -o "https://libsdl.org/projects/SDL_mixer/release/$FILENAME_IMAGE" "tmp/$FILENAME_IMAGE"
  local VOLUME=$(hdiutil attach "tmp/$FILENAME_IMAGE" | grep -o '/Volumes/.*')
  echo "Installing framework:" "/Volumes/SDL2_mixer"/*.framework
  cp -rp "$VOLUME"/*.framework ~/Library/Frameworks
  hdiutil detach "$VOLUME"
fi

cmake -DCMAKE_BUILD_TYPE=Release ..
cd ..