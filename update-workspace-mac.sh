#!/usr/bin/env bash

bash .ci-scripts/mac/download-sdl.sh

mkdir -p build
# https://github.com/koalaman/shellcheck/wiki/SC2103
(
  cd build || exit
  cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=11.7 -DCMAKE_BUILD_TYPE=RelWithDebInfo .. -G "Unix Makefiles"
)
