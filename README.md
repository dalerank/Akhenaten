# Akhenaten [![Github Actions](x64/workflows/Akhenaten%20Build%20Windows/badge.svg)](https://github.com/dalerank/Akhenaten/actions)

[![Website](https://github.com/user-attachments/assets/6fd1fee4-dfa9-4fdb-9067-f3eaf611d3f3)](https://akhenatengame.squarespace.com/)
[![Discord](https://github-production-user-asset-6210df.s3.amazonaws.com/918081/263684745-bcca8b70-13c4-48d8-8e91-4b0be8a440e6.png)](https://discord.gg/HS4njmBvpb)
[![Download](https://github-production-user-asset-6210df.s3.amazonaws.com/918081/263685010-cd624917-786d-487b-89c0-298bc694f3f2.png)](https://dalerank.itch.io/Akhenaten)
[![Windows](https://github-production-user-asset-6210df.s3.amazonaws.com/918081/263685266-d429392e-a91e-4233-b496-3863e50af5f6.png)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_windows/master/windows_build.zip)
[![Linux](https://github-production-user-asset-6210df.s3.amazonaws.com/918081/263685605-8ce46564-04e7-45a7-afa4-0ffe32335dd8.png)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_linux/master/linux_build.zip)
[![Mac/Arm](https://github.com/user-attachments/assets/8b16ea98-5ef4-4206-943e-8e8950fa4507)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac_arm/master/macos_build.zip)
[![Mac/x86](https://github-production-user-asset-6210df.s3.amazonaws.com/918081/263685850-a5f39f18-0220-411b-bb70-9bdbc9d48311.png)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac_x64/master/macos_build.zip)
[![Android](https://github-production-user-asset-6210df.s3.amazonaws.com/918081/268461479-834ae5f0-f57d-4105-b499-869982383a87.png)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_android/master/apk.zip)
[![Chrome-icon](https://github.com/user-attachments/assets/45074e6d-4f35-4773-9ae9-37935040425a)](https://dalerank.github.io/)

Akhenaten aims to make the original game Pharaoh compatible with modern systems with redesigned original engine.
Unlike the original game, which was developed by Impressions Games, Akhenaten is a community-driven effort to keep the game alive and accessible.

This is a fork of the **Julius/Augustus** project with the aim of making it work with _Pharaoh_ instead of _Caesar 3_.

The work is still in progress, so any help or support is appreciated. Allows you to load original save games 
from Pharaoh and play the initial campaign missions without major issues.

For the original game, check out the page on [Steam](https://store.steampowered.com/app/564530/Pharaoh__Cleopatra/)
or [GOG](https://www.gog.com/en/game/pharaoh_cleopatra).<br>
For the official 2023 remaster (unrelated to Akhenaten) called _Pharaoh: A New Era_, check out the Steam page [here](https://store.steampowered.com/app/1351080/Pharaoh_A_New_Era/).

## Running the game

| Platform       | Latest release | Unstable build |
| -------------- | -------------- | -------------- |
| Windows        | -              | [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Windows/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_windows/master/windows_build.zip)  |
| Linux binary | -                | [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Linux/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_linux/master/linux_build.zip)        |
| Mac (arm)      | -              | [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Mac/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac/master/macos_build.zip)            |
| Mac (x64)      | -              | [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Mac%20x86_64/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac/master/macos_build.zip)            |
| Android        | -              | [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Android/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_android/master/apk.zip) |
| Flatpak        | -              | [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Linux%20Flatpak/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_flatpak/master/akhenaten.flatpak.zip) |
| Bazzite        | -              | [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Bazzite/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_bazzite/master/bazzite_build.zip) |
| Emscripten     | -              | [![Akhenaten Build Emscripten](https://github.com/dalerank/Akhenaten/actions/workflows/akhenaten_emscripten.yml/badge.svg)](https://github.com/dalerank/Akhenaten/actions/workflows/akhenaten_emscripten.yml) |



After downloading the most recent binaries from above or building them from source,
start Akhenaten and it will ask you to point to an original Pharaoh installation folder.

Akhenaten, like Julius and Augustus, requires the original assets (graphics, sounds, etc)
from an unmodified game installation to run, in this case it needs _Pharaoh_ **as well as the _Cleopatra_ expansion.**

Note that you must have permission to write in the game data directory as the saves will be
stored there; also, your game must be patched to last version to run Akhenaten.

[![Become a patron](https://github.com/user-attachments/assets/f8f97765-7dad-428b-a722-a26a2d3d39fb)](https://patreon.com/imspinner)[![Become a patron](https://github.com/user-attachments/assets/ed3eed16-0419-49ba-8a8c-53c1413c125b)](https://github.com/sponsors/dalerank)


## Building Akhenaten from source

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

#### Building from source

- Clone the repository

- From the root folder execute:

  ```
  $ ./update-workspace-linux.sh
  $ cmake --build ./build --target clean
  $ cmake --build ./build
  ```

  * The script assumes that you are running Ubuntu. On other distributions you could find and install relevant packages manually and then run these commands instead of the script:
    ```
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
    cd ..
    ```

#### Running the binary

##### Installing dependencies

On Ubuntu and other `deb` distributions:

`sudo apt install libsdl2-2.0.0 libsdl2-mixer-2.0.0`

On Fedora and other `rpm` distributions:

`sudo yum install SDL2 SDL2_mixer`

##### Running the game

Assuming the zip file is in your Downloads directory:
```shell
cd ~/Downloads
unzip linux_build.zip
chmod +x akhenaten.linux
./akhenaten.linux
```

#### Building in Bazzite (https://bazzite.gg/) on Steam Deck or other platform
You will have to use rpm-ostree to install static version of stdc++ which is not recommended
and will make system updates slower.
But you won't be able to build Akhenaten without it. 
```shell
rpm-ostree install libstdc++-static
systemctl reboot
```
And after reboot:
```shell
./update-workspace-bazzite.sh
```

### MacOS (ARM only)

- Clone the repository

- From the root folder execute:

  ```
  $ ./compile_macos.sh
  ```

### Android

- Clone the repository

- From the root folder executr:

  ```
  sudo apt install openjdk-17-jdk openjdk-17-jre ninja-build
  sudo wget https://dl.google.com/android/repository/commandlinetools-linux-9123335_latest.zip
  sudo unzip commandlinetools-linux-9123335_latest.zip
  cd cmdline-tools/bin
  sdkmanager --install "platform-tools" "build-tools;30.0.1" "emulator" "platforms;android-33"
  cd ../../build
  cmake -DCMAKE_BUILD_DEPENDENCIES=android ..
  cd ../android
  ./gradlew assembleDebug
  ```

## Existing build options

### Building with logging stack trace on crash

Checkout `cpptrace` submodule:

```shell
git submodule init
git submodule update ext/cpptrace
```

Build in Debug mode.

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
git submodule update ext/tracy
```

Run profiler:

```shell
cd ext/tracy/profiler/build/unix && make && ./Tracy-release
```

Build & run with tracy enabled:

```shell
cmake -DUSE_FUTURE_TRACY=ON .. && make akhenaten && ./akhenaten
```

### Parameters:

```
 --display-scale NUMBER //Scales the display by a factor of NUMBER. Number can be between 0.5 and 5
 --cursor-scale NUMBER //Scales the mouse cursor by a factor of NUMBER. Number can be 1, 1.5 or 2
 --render // use specific renderer directx, opengl, vulkan
 --size // window size. Example: 800x600
 --window // enable window mode
 --mixed // hot reload scripts from disk
 --save_debug_texture // save screen output to game folder
```

![Alt](https://repobeats.axiom.co/api/embed/99a27c096522f0ed847ec37c6495d79552aeb13e.svg "Repobeats analytics image")










