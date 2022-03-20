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

## Building Ozymandias from source

If you want to build this repository yourself, check [Building Ozymandias](doc/BUILDING.md) for
details. (TODO)

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
