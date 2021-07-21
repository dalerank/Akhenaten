# Ozymandias 

**Ozymandias** is a fork of the **Julius** project that intends to port the original Pharaoh
to modern systems, like Julius and Augustus do for Caesar 3, as well as potentially any
other game in the City Building series.

If you're looking for _Caesar 3_'s vanilla experience with modern machine compatibility,
check out [Julius](https://github.com/bvschaik/julius).
If you want additional features and visual/UI improvements, and don't care about strict
compatibility with the original save files, check out [Augustus](https://github.com/Keriew/augustus).<br>
Ozymandias, like Julius and Augustus, requires the original assets (graphics, sounds, etc)
from an unmodified Pharaoh installation to run.

The work is still in progress, so any help or support is appreciated. You can more or less
complete the first 5 training missions.

What is working:
- Main graphics
- Main animations
- Loading original save files
- City messages
- Empire map display
- Campaign map progression
- Service and religion
- Workers
- (and more)

What is not working:
- Saving the game
- Empire requests
- Monuments
- Some animals and resources
- Irrigation
- Combat

If you want a more complete list, check out the
[TODO list on Notion](https://www.notion.so/Ozymandias-cfdc021c220b4d48b57bd431ed0f2a01).<br>
Check out also the original ["Bugs & idiosyncrasies"](doc/bugs.md) from Julius to find out
more about some known bugs.

## Building Ozymandias from source

If you want to build this repository yourself, check [Building Ozymandias](doc/BUILDING.md) for
details. (Note: outdated!)

## Running the game

| Platform | Latest release | Unstable build |
|----------|----------------|----------------|
| Windows  | - | - | 
| Linux AppImage | - | - |
| Mac | - | - |

First, download the game for your platform from the list above.

Alternatively, you can build Ozymandias yourself.

Then you can either copy the game to the Pharaoh folder, or run the game from an independent
folder, in which case the game will ask you to point to the Pharaoh folder.

Note that you must have permission to write in the game data directory as the saves will be
stored there. Also, your game must be patched to last version to use Ozymandias.
