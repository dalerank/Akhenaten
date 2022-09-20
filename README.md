# Ozymandias 

This is a fork of the **Julius/Augustus** project with the aim of making it work with _Pharaoh_ instead of _Caesar 3_.

The work is still in progress, so any help or support is appreciated. You can more or less load
original save games and play the first few missions in the campaign without major issues.

If you're looking for _Caesar 3_'s vanilla experience with modern machine compatibility,
check out [Julius](https://github.com/bvschaik/julius).<br>
If you want additional features and visual/UI improvements, and don't care about strict
compatibility with the original save files, check out [Augustus](https://github.com/Keriew/augustus).<br>
For the original game, check out the page on [Steam](https://store.steampowered.com/app/564530/Pharaoh__Cleopatra/)
or [GOG](https://www.gog.com/en/game/pharaoh_cleopatra).<br>
For the official upcoming remaster (unrelated to Ozymandias) called _A New Era_, check out the Steam page [here](https://store.steampowered.com/app/1351080/Pharaoh_A_New_Era/).

## Running the game

| Platform       | Latest release | Unstable build |
|----------------|----------------|----------------|
| Windows        | -              | -              | 
| Linux AppImage | -              | -              |
| Mac            | -              | -              |

After downloading the most recent binaries from above or building them from source,
start Ozymandias and it will ask you to point to an original Pharaoh installation folder.

Ozymandias, like Julius and Augustus, requires the original assets (graphics, sounds, etc)
from an unmodified game installation to run, in this case it needs _Pharaoh_ **as well as the _Cleopatra_ expansion.**

Note that you must have permission to write in the game data directory as the saves will be
stored there; also, your game must be patched to last version to run Ozymandias.

## Building Ozymandias from source

### Windows

- Clone the repo
- Install [MinGW](https://code.visualstudio.com/docs/cpp/config-mingw). You can for example follow this instructions:
  - Important here: Choose MinGW64 
- Install [CMake](https://github.com/Kitware/CMake/releases/download/v3.24.2/cmake-3.24.2-windows-x86_64.zip)
- Download [SDL2](https://github.com/libsdl-org/SDL/releases/download/release-2.24.0/SDL2-devel-2.24.0-mingw.zip) and extract it to folder ext/SDL2
- Download [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.2/SDL2_mixer-devel-2.6.2-mingw.) and extract it to folder ext/SDL2
- Download [SDL2_image](https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.2/SDL2_mixer-devel-2.6.) and extract it to folder ext/SDL2
- From root folder execute:
  ```
  mkdir build
  cd build
  cmake .. -G "MingGW Makefiles"
  mingw32-make
  ```


### Linux

Only tested this on Manjaro but under ubuntu similar you should install following packages:

- Clone the repo
- Install (You will need to enable AUR on Manjaro):
  - CMake
  - g++
  - sdl2
  - sdl2_mixer
  - sdl2_image

- From the root folder execute:
  ```
  mkdir build
  cd build
  cmake ..
  make
  ```

### Mac

- Currently no one on mac here but you can try the instructions from Julius. They should be similar beside the additional need for SDL2_Image. https://github.com/bvschaik/julius/wiki/Building-Julius
- Feel free to add a pull request to add mac instructions here.