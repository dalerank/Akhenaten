# Ozymandias

[![Github Actions](https://github.com/dalerank/ozymandias/workflows/Ozymandias%20Build%20Windows/badge.svg)](https://github.com/dalerank/Ozymandias/actions)

[Discord Chat](https://discord.gg/HS4njmBvpb)

![2023-08-06_21_29_36-ozymandias](https://github.com/dalerank/Ozymandias/assets/918081/f009ec60-47d6-49e5-811c-2ed72f12ab7c)


This is a fork of the **Julius/Augustus** project with the aim of making it work with _Pharaoh_ instead of _Caesar 3_.

The work is still in progress, so any help or support is appreciated. You can more or less load
original save games and play the first few missions in the campaign without major issues.

If you're looking for _Caesar 3_'s vanilla experience with modern machine compatibility, check out [Julius](https://github.com/bvschaik/julius).<br>
If you want additional features and visual/UI improvements, and don't care about strict
compatibility with the original save files, check out [Augustus](https://github.com/Keriew/augustus).<br>
For the original game, check out the page on [Steam](https://store.steampowered.com/app/564530/Pharaoh__Cleopatra/)
or [GOG](https://www.gog.com/en/game/pharaoh_cleopatra).<br>
For the official upcoming remaster (unrelated to Ozymandias) called _A New Era_, check out the Steam page [here](https://store.steampowered.com/app/1351080/Pharaoh_A_New_Era/).

## Running the game

| Platform       | Latest release | Unstable build |
| -------------- | -------------- | -------------- |
| Windows        | -              | [![Github Actions](https://github.com/dalerank/ozymandias/workflows/Ozymandias%20Build%20Windows/badge.svg)](https://nightly.link/dalerank/Ozymandias/workflows/ozymandias/master/windows_build.zip)              |
| Linux AppImage | -              | [![Github Actions](https://github.com/dalerank/ozymandias/workflows/Ozymandias%20Build%20Linux/badge.svg)](https://nightly.link/dalerank/Ozymandias/workflows/ozymandias_linux/master/linux_build.zip)          |
| Mac            | -              | [![Github Actions](https://github.com/dalerank/ozymandias/workflows/Ozymandias%20Build%20Mac/badge.svg)](https://nightly.link/dalerank/Ozymandias/workflows/ozymandias_mac/master/macos_build.zip)            |



After downloading the most recent binaries from above or building them from source,
start Ozymandias and it will ask you to point to an original Pharaoh installation folder.

Ozymandias, like Julius and Augustus, requires the original assets (graphics, sounds, etc)
from an unmodified game installation to run, in this case it needs _Pharaoh_ **as well as the _Cleopatra_ expansion.**

Note that you must have permission to write in the game data directory as the saves will be
stored there; also, your game must be patched to last version to run Ozymandias.

## Building Ozymandias from source

### Windows + Visual Studio

- Clone the repository
- Install [CMake](https://cmake.org/download/#latest)
- run update-workspace.bat, which download all SDL2 dependencies and create VS solution for you

### Windows + Yours IDE

To build with your favorite IDE, just import the cmakelists.txt file as a project and build from there. Otherwise, you can use [MinGW-w64](https://www.mingw-w64.org/downloads/) to build via CLI:

- Clone the repository
- Install [CMake](https://cmake.org/download/#latest)
- From the project's root folder execute, in order:
  
  ```
  mkdir build
  cd build
  cmake .. -G "MingGW Makefiles"
  mingw32-make
  ```

To run the engine, you'll also need the necessary dynamic libraries in the same folder as the executable, unless the project is set to build with static linkage.

- Navigate to the SDL2, SDL2_mixer and SDL2_image extracted files, and locate the .dll files inside the `bin` folder of the correct architecture (e.g. `SDL2_image-2.6.2/x86_64-w64-mingw32/bin/`)

- Copy the .dll files from each of the above to the `build` folder

### Linux

Only tested on Manjaro, but under Ubuntu or similar you should install the same packages:

- Clone the repository

- From the root folder execute:
  
  ```
  $ ./update-workspace-linux.sh
  $ cmake --build ./build --target clean
  $ cmake --build ./build
  ```

### MacOS

Only tested on Manjaro, but under Ubuntu or similar you should install the same packages:

- Clone the repository

- From the root folder execute:
  
  ```
  $ ./update-workspace-mac.sh
  $ cmake --build ./build --target clean
  $ cmake --build ./build
  ```

## Contributing

Please use `clang-format-15` before submitting changes by using `./clang-format.sh` on Linux.

### Running with different log levels

Use environment variable `SDL_LOG_PRIORITY` for adjustment of logging. For example:

```shell
SDL_LOG_PRIORITY=debug
```

By default `info` level is set.

### Running with tracy

Enable tracy submodule:

```shell
git submodule init
git submodule update
```

Run profiler:

```shell
cd ext/tracy/profiler/build/unix && make && ./Tracy-release
```

Build & run with tracy enabled:

```shell
cmake -DUSE_FUTURE_TRACY=ON .. && make ozymandias && ./ozymandias
```

![Alt](https://repobeats.axiom.co/api/embed/d972b1b3da5423da758f1b4a1396177626bff54b.svg "Repobeats analytics image")
