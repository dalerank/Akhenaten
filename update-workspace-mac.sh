#!/usr/bin/env bash

bash .ci-scripts/mac/download-sdl.sh

mkdir -p build
# https://github.com/koalaman/shellcheck/wiki/SC2103
(
  cd build || exit
  cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" .. -G "Unix Makefiles"
)
