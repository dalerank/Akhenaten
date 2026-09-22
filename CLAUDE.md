# Akhenaten — Developer Guide for Claude

## Project

Modern open-source reimplementation of the classic city-builder **Pharaoh (1999)** by Impressions Games.
Fork of Julius/Augustus, targets Pharaoh + Cleopatra expansion. Full savegame compatibility with the original.
Version: 0.2.7 | License: AGPL-3.0 | Solo maintainer + community contributors.

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
Preset families (each has a matching build preset of the same name):
- Windows / MSVC: `win-msvc-{debug,relwithdebinfo}-{vs2019,vs2022,vs2026,ninja}`,
  plus the short aliases `win-debug` / `win-relwithdebinfo` and `win-clang-cl-relwithdebinfo[-ninja]`
- Linux: `linux-gcc-{debug,release,relwithdebinfo}-make`, `linux-clang-{debug,relwithdebinfo}-ninja`
- macOS: `macos-clang-relwithdebinfo-{make,ninja}[-arm64|-x86_64]`

CI builds `linux-gcc-release-make`; that is the preset the integral-test gate runs against.
All dependencies (SDL2, FreeType, Tracy, etc.) are auto-downloaded via CMake FetchContent — no manual DLL copying.

Build output: `./build/`

### Useful CMake flags
```
-DOPTION_ENABLE_TRACY=OFF    # disable Tracy profiler
-DCMAKE_BUILD_TYPE=Debug     # force debug
```

### Adding a new source file
Sources are collected via `file(GLOB ...)` with **no `CONFIGURE_DEPENDS`**, so a brand-new
`.cpp`/`.h` is **not** picked up by a plain `cmake --build`. Re-run the configure step first
(`cmake --preset <preset>`), then build. Editing existing files needs no reconfigure.
(`src/scripts/*.js` are embedded at build time into `*.js.cpp` — a rebuild re-embeds them;
`tests/*.js` load from disk and need no rebuild.)

## Run & Debug

### Command-line parameters
```
--help                print every registered argument (authoritative list — see src/platform/arguments.cpp)
--window              windowed mode
--size WxH            window size, e.g. 800x600
--pos X,Y             window position
--display-scale PCT   display scale, 50..500
--cursor-scale PCT    cursor scale, 100 / 150 / 200
--render RENDERER     force renderer (opengl, direct3d)
--font PATH           use custom TTF font (overrides the font from localization.js)
--language ru         set language (en, ru, fr, de, it, sp, po, pr, sw, tc, sc, kr)
--nosound             disable audio (skips sound manager init and audio file probing)
--no-resource         run without Pharaoh data files (skips campaign.txt and AUDIO/ probing)
--nodatacheck         skip Pharaoh/Cleopatra install validation at startup
--no-logo             skip the logo screen, go straight to the main menu
--nointro             skip the intro video on startup
--nomouse             disable mouse-driven input (edge/drag camera scrolling) — for tests/screenshots
--config              show configuration dialog on startup
--noconfig-window     skip configuration dialog on startup (even without akhenaten.cfg)
--og                  force original Pharaoh behavior (disable all Enhanced / gameplay-change features)
--enhanced            enable all Enhanced / gameplay-change features (overrides --og if both are set)
--mods PATH           set mods directory
--mixed PATH          hot-reload JS scripts from disk (dev mode)
--unpack_scripts      extract embedded JS to user directory
--integraltests       run the built-in integral test suite and exit (see "Testing" below)
--integraltest-only NAME  with --integraltests, run only tests whose filename contains NAME
--editor              start in the scenario editor (dev-only; blank map, bypasses main menu)
--load-map PATH       load a .map straight into the city, bypassing the main menu
--screenshot-dir PATH directory for screenshots (created if missing; default: working dir)
--logjsfiles          log which JS files are opened
--log-js-handlers     log when JS event handlers are registered
--log-resources       log resource loading (textures, image packs)
--log-sound           log which sound files the game tries to load
--discord-log         verbose Discord RPC logging
--nocrashdlg          suppress crash dialog
--fulldmp             create full crash dump
--extract-installer PATH  extract Pharaoh data from Inno/GOG Setup.exe via innoextract
--extract-dir PATH    output dir for --extract-installer (default: …/akhenaten/pharaoh-data)
--save_debug_texture  save debug textures to DEV_TESTING/tex/
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
Version matters: the CI job installs `clang-format-20`, and `.clang-format` is written for it.
An older local clang-format (e.g. the 19.x bundled with Visual Studio) produces a diff CI rejects —
check `clang-format --version` before formatting.

### Comments

Do **not** sprinkle comments everywhere. Prefer clear names and structure over narration.
(Mirrored for Cursor in `.cursor/rules/minimal-comments.mdc`.)

Comment when:
- a non-obvious invariant, quirk, or workaround needs explaining (why, not what)
- a dangerous edge case would be mis-fixed by a future reader
- data is provisional / a TODO has a clear follow-up

Do not comment:
- restating the next line of code
- section banners for routine logic
- self-evident control flow
- "as above" / history dumps that belong in the commit message

```cpp
// BAD — narrates the obvious
// Advance phase for all linked parts
advance_phase_all_parts(this);

// GOOD — the reason is non-obvious
// Mastaba-style: progress() later does phase+1 per part — main-only bump desyncs path/hall.
advance_phase_all_parts(this);
```

When editing existing code, do not add new comments unless they meet the bar above;
leave useful existing comments alone.

## Testing — integral tests

`tests/*.js` is the integral test suite (219 files). It is a CI gate
(`.github/workflows/akhenaten_integral_tests.yml`); a red run blocks the PR.
**This is the default way to verify a change.**

Run the whole suite (the invocation CI uses):
```
build/RelWithDebInfo/akhenaten.exe --integraltests --no-logo --no-resource --nosound --window --size 800x600
```
Run one test — match is a case-insensitive substring of the filename stem:
```
build/RelWithDebInfo/akhenaten.exe --integraltests --integraltest-only 06 --no-logo --no-resource --nosound --window --size 800x600
```
Exit code is `0` only when every test passed.

Results go to the log, **not** to stdout:
- Windows: `%APPDATA%/Akhenaten/akhenaten-log.txt`
- Linux: `${XDG_DATA_HOME:-~/.local/share}/Akhenaten/akhenaten-log.txt`

Grep it for `\[test:.*\] (PASS|FAIL)` per test and `\[integraltests\] N passed, M failed`
for the summary.

Tests that need real Pharaoh data take the install path as the last positional argument;
`--no-resource` covers the rest.

### Writing a test
A test file defines two globals and is discovered automatically by living in `tests/`:
- `run_test()` — drives the game via `__test_*` helpers, must end with `__test_signal_ready()`
  (otherwise the runner fails it on a frame timeout)
- `check_valid()` — returns truthy on success; usually asserts via
  `__test_find_inlog('[test-marker] …')` against markers the game logs

`tests/*.js` load from disk, so a new or edited test needs **no rebuild** — unlike
`src/scripts/*.js`, which are embedded at build time.

## Verification

Before starting any task, state how you will verify the result.
Default to the integral tests above; say so explicitly when a change cannot be covered by them.

## Git Commits

Do not add `Co-Authored-By: Claude` or any Claude/Anthropic attribution to commit messages or pull request bodies. Do not include "Generated with Claude Code" or similar lines in PR descriptions.

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
├── editor/       scenario editor
├── io/           save/load (chunk schema), mods, localization
├── game/         game state, main loop, resource enums
├── config/       game settings and config-archive readers
├── content/      content/asset registration and loading
├── resource/     resource type metadata
├── empire/       trade routes, empire cities
├── overlays/     city overlay rendering
├── input/        mouse, keyboard, touch, hotkeys
├── sound/        music, speech, effects, city sounds
├── net/          networking / remote services
├── events/       typed event bus infrastructure
├── core/         utilities (CRC32, ZIP, threading, math, logging)
├── debug/        tile overlay / ImGui debug registration
├── dev/          dev tooling (console commands, event history)
├── js/           MuJS JavaScript VM integration
├── scripts/      embedded game JS (building/, city/, ui_*, mission_*)
└── platform/     platform-specific code (Android, Vita, Switch)
```
(`bzip/`, `lame/`, `lzma/` are vendored third-party sources — don't edit them.
`mujs/` is vendored too, but it is a fork we actively modify — see `src/mujs/CLAUDE.md`.)
