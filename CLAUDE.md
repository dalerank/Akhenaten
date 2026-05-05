# Akhenaten — Developer Guide for Claude

## Project

Modern open-source reimplementation of the classic city-builder **Pharaoh (1999)** by Impressions Games.
Fork of Julius/Augustus, targets Pharaoh + Cleopatra expansion. Full savegame compatibility with the original.
Version: 0.2.6 | License: AGPL-3.0 | Solo maintainer + community contributors.

## Build (Windows)

### Visual Studio (recommended)
```bat
update-workspace.bat   # downloads dependencies, generates VS solution in ./build
```
Then open `./build/akhenaten.sln` in Visual Studio.

### CMake presets
```powershell
cmake --list-presets                          # see all options
cmake --preset win-msvc-debug-vs2022          # configure (Debug)
cmake --build --preset win-msvc-debug-vs2022  # build
# or RelWithDebInfo (stack trace + optimizations):
cmake --preset win-msvc-relwithdebinfo-vs2022
cmake --build --preset win-msvc-relwithdebinfo-vs2022
```
All dependencies (SDL2, FreeType, Tracy, etc.) are auto-downloaded via CMake FetchContent — no manual DLL copying.

Build output: `./build/`

### Useful CMake flags
```
-DOPTION_ENABLE_TRACY=OFF    # disable Tracy profiler
-DCMAKE_BUILD_TYPE=Debug     # force debug
```

## Run & Debug

### Command-line parameters
```
--window              windowed mode
--language ru         set language (en, ru, fr, de, it, sp, po, pr, sw, tc, sc, kr)
--nosound             disable audio
--config              show configuration dialog on startup
--mods PATH           set mods directory
--mixed PATH          hot-reload JS scripts from disk (dev mode)
--unpack_scripts      extract embedded JS to user directory
--logjsfiles          log which JS files are opened
--nocrashdlg          suppress crash dialog
--fulldmp             create full crash dump
--save_debug_texture  save debug textures to DEV_TESTING/tex/
--size WxH            window size, e.g. 800x600
SDL_LOG_PRIORITY=debug  env var for verbose logging (info by default)
```
Last positional argument = path to Pharaoh installation directory.

### Tracy profiler
Tracy v0.13.1 is enabled by default. **Must use Tracy GUI v0.13.1** — other versions cause protocol mismatch.
Download: https://github.com/wolfpld/tracy/releases/tag/v0.13.1

### JS debugging (VS Code)
MuJS scripts can be debugged via DAP:
1. In-game console: `js_debugger start` (default port 4711)
2. In VS Code: attach configuration, type `mujs`, `localhost:4711`
See `DEBUGGER_VSCODE.md` for full walkthrough.

## Code Style

Enforced by **clang-format 20.1.0** (rules in `.clang-format`).
Format changed files before committing:
```
git clang-format --style=file --extensions cpp,cc,cxx,h,hpp
```
CI will reject PRs that fail formatting checks.

## Git Commits

Do not add `Co-Authored-By: Claude` or any Claude/Anthropic attribution to commit messages.

## Documentation

The wiki lives in `docs/wiki/`. When editing mission scripts or their data, update the corresponding wiki page:

- **Mission scripts** (`src/scripts/mission_N_*.js`) — if you change win criteria, starting funds, tutorial thresholds, event logic, or available buildings, update `docs/wiki/player/missions/<cityname>.html`.  
  The Developer Reference section on each mission page lists exact file paths, line numbers, and message IDs — keep those in sync.
- **Mission index** (`docs/wiki/player/missions/index.html`) — if missions are added, reordered, or their objectives change, update the corresponding table row.
- **Game messages** (`src/scripts/game_messages_en.js`) — message IDs referenced in mission pages are listed in the Developer Reference spoiler on each mission page; update them if IDs or line numbers shift.

## Project Rules (from CONTRIBUTING.md)

- Goal: exact reimplementation of original Pharaoh logic with savegame compatibility
- PRs that change game logic or major UI are declined for now
- "Enhanced edition" features planned for later — don't implement them now
- Discuss changes via GitHub Issues or Discord before opening a PR

## Source Layout

See `src/CLAUDE.md` for architecture details.

```
src/
├── building/     buildings, construction, static params
├── city/         city simulation aggregate (population, labor, finance, religion)
├── figure/       figure framework (movement, AI base, routing)
├── figuretype/   concrete figure types (cartpusher, soldier, enemy, etc.)
├── graphics/     rendering, painter (SDL2 wrapper), fonts, image atlas
├── grid/         tile map data, pathfinding, terrain, floodplain
├── window/       modal UI windows (dialogs, building info, empire)
├── widget/       persistent HUD (sidebar, top menu, minimap)
├── scenario/     mission config, events, requests, win criteria
├── io/           save/load (chunk schema), mods, localization
├── game/         game state, main loop, resource enums
├── empire/       trade routes, empire cities
├── overlays/     city overlay rendering
├── js/           MuJS JavaScript VM integration
└── platform/     platform-specific code (Android, Vita, Switch)
```
