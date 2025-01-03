#!/usr/bin/env bash

FRAMEWORKS_PATH=$HOME/Library/Frameworks
SDL2_VERSION=2.28.0
SDL2_MIXER_VERSION=2.6.3
SDL2_IMAGE_VERSION=2.6.3

TMPDIR=$(mktemp -d -t akhenaten_sdl)

# $1 = $base_url
# $2 = $filename.dmg
install_dmg () {
  DMG_DOWNLOAD_PATH="$TMPDIR/$2"

  printf "Downloading %s to temp dir: \n      %s\n\n" "$2" "$DMG_DOWNLOAD_PATH"
  curl "$1/$2" --output "$DMG_DOWNLOAD_PATH"
  VOLUME=$(hdiutil attach "$DMG_DOWNLOAD_PATH" | grep -o '/Volumes/.*')
  printf "\nInstalling framework from %s to %s\n" "$VOLUME" "$FRAMEWORKS_PATH"
  cp -rp "$VOLUME"/*.framework "$FRAMEWORKS_PATH"
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
