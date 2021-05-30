# Running Ozymandias

Ozymandias requires the original Pharaoh files to run. This can be an old CD-ROM version, or a digital copy
from either [GOG](https://www.gog.com/game/pharaoh_cleopatra) or
[Steam](https://store.steampowered.com/app/564530/Pharaoh__Cleopatra/).

Note that there are [command line options](#command-line-options) which are available to all platforms.

## Windows

Ozymandias supports Windows XP and higher.

1. Install Pharaoh using the provided installer (GOG/Steam/CD-ROM).
2. Download the [latest release](https://github.com/3t0n/Ozymandias/releases) of Ozymandias or compile from source.
3. Copy ozymandias.exe, SDL2.dll and SDL2_mixer.dll to the folder where you installed Pharaoh
4. Run ozymandias.exe

**Note:** If you install Pharaoh using Steam and plan to use Steam to launch the game,
***do not*** rename `ozymandias.exe` to `c3.exe`.
Doing so will make the mouse cursor disappear when using right-click to scroll.
   
Instead, open `SierraLauncher.ini` and replace `Game1Exe=c3.exe` with the `Game1Exe=ozymandias.exe`.

## Linux/BSD

1. Obtain the game data files of Pharaoh by checking one of the two next sections.
2. Download the [latest AppImage release](https://github.com/3t0n/Ozymandias/releases) of Ozymandias.
3. Make the downloaded AppImage executable by going into the file properties or running
   `chmod +x ozymandias-*.AppImage` in the same folder as the AppImage.
4. You can then run it just like any Linux executable.
5. (Optional) You can install [AppImageLauncher](https://github.com/TheAssassin/AppImageLauncher#readme)
   in order to integrate the AppImage in your OS. You'll then be able to launch it easily from the menu
   just like other apps.

### GOG version with InnoExtract
If you bought the GOG edition, you can download the offline installer exe, and use
[InnoExtract](http://constexpr.org/innoextract/) to extract the game files:

1. Build Ozymandias or install using your package manager
2. [Install](http://constexpr.org/innoextract/install) `innoextract` for your distribution
3. Download the Pharaoh offline installer exe from GOG
4. Run the following command to extract the game files to a new `app` directory:

        $ innoextract -m setup_caesar3_2.0.0.9.exe

5. Move the `ozymandias` executable to the extracted `app` directory and run from there, OR run Ozymandias
   with the path to the game files as parameter:

        $ ozymandias path-to-app-directory

Note that your user requires write access to the directory containing the game files, since the
saved games are also stored there.

### Using WINE

Another option is to get the game files by installing Pharaoh using [WINE](https://www.winehq.org/):

1. Build Ozymandias or install using your package manager
2. Install Pharaoh using WINE, take note where the game is installed
3. Run Ozymandias with the path where the game is installed:

        $ ozymandias path-to-c3-directory

## Command line options

Ozymandias supports some command-line options. Its usage is:

    $ ozymandias [ARGUMENTS] [DATA_DIR]

`[ARGUMENTS]` can be the following:

* `--display-scale NUMBER`

    Optional. Scales the entire Ozymandias application by a factor of `NUMBER`. Useful for high-dpi systems.

    `NUMBER`can be any number between `0.5` and `5`. The default is `1`.

* `--cursor-scale NUMBER`

    Optional. Scales the mouse cursor by a factor of `NUMBER`. Cursor scaling is independent of display scaling.

    `NUMBER` can only be set to `1`, `1.5` or `2`. The default is `1`.

`[DATA_DIR]` Is the location of the Pharaoh asset files.

If `[DATA_DIR]` is not provided, Ozymandias will try to load the asset files from the directory where it is installed.

If the files are not found, it will check if a previous valid directory was stored in the internal preferences
and load the asset files from that directory.

If Ozymandias still fails to load the assets, it will ask you to point to a valid directory.
