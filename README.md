# Akhenaten [![Github Actions](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Windows/badge.svg)](https://github.com/dalerank/Akhenaten/actions)

[![Website](res/badges/website.svg)](https://dalerank.github.io/Akhenaten/)
[![Discord](res/badges/discord.svg)](https://discord.gg/HS4njmBvpb)
[![Download](res/badges/download.svg)](https://dalerank.itch.io/Akhenaten)

[![Windows](res/badges/windows.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_windows/master/windows_build.zip)
[![Linux](res/badges/linux.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_linux/master/linux_build.zip)
[![Mac/Arm](res/badges/mac-arm.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac_arm/master/macos_arm_build.zip)
[![Mac/x64](res/badges/mac-x64.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac_x64/master/macos_x64_build.zip)
[![Android](res/badges/android.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_android/master/apk.zip)
[![iOS](res/badges/ios.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_ios/master/ios_build.zip)
[![Web](res/badges/web.svg)](https://dalerank.github.io/Akhenaten/play/)

[![Tests](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/dalerank/28104123b52e0fc76b56b8df8ca345e7/raw/akhenaten-tests.json)](https://github.com/dalerank/Akhenaten/actions/workflows/akhenaten_integral_tests.yml)

Akhenaten is an open-source reimplementation of **Pharaoh** (Impressions Games, 1999) and its
**Cleopatra** expansion, built to run on modern systems. It is a fork of **Julius/Augustus**, retargeted
from _Caesar 3_ to _Pharaoh_. It loads original Pharaoh save games.

Status: work in progress. The early campaign missions play without major issues. Help is welcome.

You need the original game data. Pharaoh + Cleopatra is sold on
[Steam](https://store.steampowered.com/app/564530/Pharaoh__Cleopatra/) and
[GOG](https://www.gog.com/en/game/pharaoh_cleopatra).
[_Pharaoh: A New Era_](https://store.steampowered.com/app/1351080/Pharaoh_A_New_Era/) (2023) is a separate
remake; its files do not work with Akhenaten.

## Download

Builds are published on [itch.io](https://dalerank.itch.io/Akhenaten). CI also builds every push to `master`;
the latest unstable builds are here:

| Platform | Unstable build |
| --- | --- |
| Windows | [![Windows](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Windows/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_windows/master/windows_build.zip) |
| Linux | [![Linux](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Linux/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_linux/master/linux_build.zip) |
| Linux (Flatpak) | [![Flatpak](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Linux%20Flatpak/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_flatpak/master/akhenaten.flatpak.zip) |
| Bazzite / Steam Deck | [![Bazzite](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Bazzite/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_bazzite/master/bazzite_build.zip) |
| macOS (Apple Silicon) | [![Mac](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Mac/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac_arm/master/macos_arm_build.zip) |
| macOS (Intel) | [![Mac x86_64](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Mac%20x86_64/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_mac_x64/master/macos_x64_build.zip) |
| Android | [![Android](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20Android/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_android/master/apk.zip) |
| iOS / iPadOS | [![iOS](https://github.com/dalerank/akhenaten/workflows/Akhenaten%20Build%20iOS/badge.svg)](https://nightly.link/dalerank/Akhenaten/workflows/akhenaten_ios/master/ios_build.zip) |
| Web | [Play in the browser](https://dalerank.github.io/Akhenaten/play/) · [![Emscripten](https://github.com/dalerank/Akhenaten/actions/workflows/akhenaten_emscripten.yml/badge.svg)](https://github.com/dalerank/Akhenaten/actions/workflows/akhenaten_emscripten.yml) |

On Linux, unpack and run the binary:

```shell
unzip linux_build.zip
chmod +x akhenaten.linux
./akhenaten.linux
```

## Game data

Akhenaten needs the graphics, sounds and other files from an unmodified **Pharaoh install with the
Cleopatra expansion**, patched to the last version (1.3 + Cleopatra). The Pharaoh demo is not supported: it
lacks `Pharaoh_Fonts` and the Cleopatra image packs, and the game rejects it at startup. Saves are written to
the game data folder, so that folder has to be writable.

On first launch Akhenaten asks for the Pharaoh folder. You can also pass the path as the last command-line
argument.

If you only have the installer (`.exe`), put it next to the Akhenaten binary:

```
akhenaten.exe
innoextract.exe      # GOG / Inno Setup installers
unshield.exe         # Sierra / InstallShield (e.g. demo), optional fallback
Installer/
  Setup.exe          # or pharaoh.exe demo installer
PharaohData/         # created on first launch
```

If no Steam copy of Pharaoh is found, Akhenaten unpacks `Installer/*.exe` into `PharaohData`, checks for
`campaign.txt`, saves the path to `akhenaten.cfg` and starts. Inno Setup / GOG installers are unpacked with
[innoextract-nb](https://github.com/dalerank/innoextract-nb), InstallShield ones with `7z` and
[unshield](https://github.com/twogood/unshield). The same extraction is available from **Extract from
installer…** in the configuration window, or from the command line:

```
akhenaten --extract-installer "C:\path\to\Setup.exe" --extract-dir "C:\path\to\pharaoh-data"
```

Run `akhenaten --help` for the full list of command-line options.

## Building from source

The project uses CMake presets (CMake 3.30 or newer). Dependencies (SDL2, FreeType, Tracy and the rest) are
downloaded and built through FetchContent, and output goes to `./build`.

```shell
cmake --list-presets
cmake --preset linux-gcc-debug-make
cmake --build --preset linux-gcc-debug-make
```

Add options on the configure line (for example `-DOPTION_ENABLE_TRACY=OFF`), or put your own presets in
`CMakeUserPresets.json`, which git does not track.

- **Windows:** run `update-workspace.bat` to generate a Visual Studio solution in `./build`, or use a
  `win-msvc-*` preset.
- **Linux (Ubuntu):** `./update-workspace-linux.sh`, then `cmake --build ./build`. On Bazzite, install
  `libstdc++-static` with `rpm-ostree` and reboot first, then run `./update-workspace-bazzite.sh`.
- **macOS:** `./compile_macos.sh arm64` (or `x86_64`, `universal`), or a `macos-*` preset.
- **Android:** configure with `cmake -DCMAKE_BUILD_DEPENDENCIES=android ..` in `build/`, then run
  `./gradlew assembleDebug` in `android/` (needs JDK 17 and the Android SDK).
- **iOS / iPadOS** (macOS host with Xcode): `bash packaging/ios/build_ios.sh build/ios`.

[CLAUDE.md](CLAUDE.md) has the developer details: every preset, command-line flags, the Tracy profiler
version, code style and the integral test suite. To debug game scripts from VS Code, see
[DEBUGGER_VSCODE.md](DEBUGGER_VSCODE.md).

## Documentation

- [Wiki](docs/wiki/index.html): [player guide](docs/wiki/player/index.html) and
  [developer notes](docs/wiki/dev/index.html), including [modding](docs/wiki/dev/guides/modding.html).
  The site version is at [dalerank.github.io/Akhenaten](https://dalerank.github.io/Akhenaten/).
- Changelog: [CHANGELOG_2025_EN.md](CHANGELOG_2025_EN.md) (Russian: [CHANGELOG_2025.md](CHANGELOG_2025.md)).

## Contributing and support

Read [CONTRIBUTING.md](CONTRIBUTING.md) before opening a pull request. Bugs and feature requests go to
[GitHub Issues](https://github.com/dalerank/Akhenaten/issues). Discussion happens on
[Discord](https://discord.gg/HS4njmBvpb).

[![Patreon](res/badges/patreon.svg)](https://patreon.com/imspinner)
[![Sponsor](res/badges/sponsor.svg)](https://github.com/sponsors/dalerank)

## License

AGPL-3.0, see [LICENSE.txt](LICENSE.txt).

![Alt](https://repobeats.axiom.co/api/embed/99a27c096522f0ed847ec37c6495d79552aeb13e.svg "Repobeats analytics image")
