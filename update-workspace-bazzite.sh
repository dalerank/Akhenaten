#!/bin/sh
# Bazzite/Steam Deck build: enables GAME_PLATFORM_STEAMDECK (name "steamdeck", UI scale defaults).
mkdir -p build
cd build
cmake -DOPTION_STEAMDECK=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
cd ..
