#!/usr/bin/env bash

ln -s "$HOME"/Library/Frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h src/SDL_mixer.h

FRAMEWORKS_PATH=$HOME/Library/Frameworks
SDL2_VERSION=2.32.10
SDL2_MIXER_VERSION=2.8.1
SDL2_IMAGE_VERSION=2.8.8

TMPDIR=$(mktemp -d -t akhenaten_sdl)

# $1 = $base_url
# $2 = $filename.dmg
install_dmg () {
  DMG_DOWNLOAD_PATH="$TMPDIR/$2"

  printf "Downloading %s to temp dir: \n      %s\n\n" "$2" "$DMG_DOWNLOAD_PATH"
  curl "$1/$2" --output "$DMG_DOWNLOAD_PATH"
  VOLUME=$(hdiutil attach "$DMG_DOWNLOAD_PATH" | grep -o '/Volumes/.*')
  printf "\nInstalling framework from %s to %s\n" "$VOLUME" "$FRAMEWORKS_PATH"
  FRAMEWORK_NAME=$(find $VOLUME -maxdepth 1 -type d -iname "*.framework" -exec basename {} \;)
  cp -rp "$VOLUME/$FRAMEWORK_NAME" "$FRAMEWORKS_PATH"
  if [ -d "$VOLUME"/optional ]
  then
    CHILD_FRAMEWORKS_PATH="$FRAMEWORKS_PATH/$FRAMEWORK_NAME/Versions/A/Frameworks"
    printf "\nCopying optional frameworks from %s to %s\n" "$VOLUME" "$CHILD_FRAMEWORKS_PATH"
    mkdir -p "$CHILD_FRAMEWORKS_PATH"
    cp -rp "$VOLUME"/optional/*.framework "$CHILD_FRAMEWORKS_PATH"
  fi
  hdiutil detach "$VOLUME"
  rm "$DMG_DOWNLOAD_PATH"
}

# $1 = SDL2|SDL2_mixer|...
installed_framework_version () {
  version=$(xmllint --xpath '/plist/dict/key[text()="CFBundleVersion"]/following::string[1]/text()' "$HOME/Library/Frameworks/$1.framework/Resources/Info.plist")
  echo "$version" | tr -d '\n'
}

# $1 = SDL2|SDL2_mixer|...
error_different_version () {
  printf "ERROR: %s Framework is already installed at %s/Library/Frameworks/%s.framework at a different version!\n \
      Remove it or update manually to prevent conflicts\n" "$1" "$HOME" "$1"
  exit 1
}

main () {
  mkdir -p "$FRAMEWORKS_PATH"

  if [ ! -d "$FRAMEWORKS_PATH/SDL2.framework" ]
  then
    SDL2_FILENAME=SDL2-$SDL2_VERSION.dmg
    install_dmg "https://libsdl.org/release/" $SDL2_FILENAME
  elif [ "$(installed_framework_version SDL2)" != "$SDL2_VERSION" ]
  then
    error_different_version SDL2
  else
    echo "SDL2 framework already installed at required version, skipping"
  fi

  if [ ! -d "$FRAMEWORKS_PATH/SDL2_mixer.framework" ]
  then
    SDL2_MIXER_FILENAME=SDL2_mixer-$SDL2_MIXER_VERSION.dmg
    install_dmg "https://libsdl.org/projects/SDL_mixer/release/" $SDL2_MIXER_FILENAME
  elif [ "$(installed_framework_version SDL2_mixer)" != "$SDL2_MIXER_VERSION" ]
  then
    error_different_version SDL2_mixer
  else
    echo "SDL2_mixer framework already installed at required version, skipping"
  fi

  if [ ! -d "$FRAMEWORKS_PATH/SDL2_image.framework" ]
  then
    SDL2_IMAGE_FILENAME=SDL2_image-$SDL2_IMAGE_VERSION.dmg
    install_dmg "https://libsdl.org/projects/SDL_image/release/" $SDL2_IMAGE_FILENAME
  elif [ "$(installed_framework_version SDL2_image)" != "$SDL2_IMAGE_VERSION" ]
  then
    error_different_version SDL2_image
  else
    echo "SDL2_image framework already installed at required version, skipping"
  fi
}

main

exit 0
