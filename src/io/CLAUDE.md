# IO Subsystem

Chunk-based save/load system, mod image loading, and localization strings.

## Key Files

| File | Purpose |
|------|---------|
| `io.h` | File reading API: `io_read_file_into_buffer()`, sg3/sgx entry counting |
| `manager.h` | `FileIOManager` — chunk-based schema, auto-version detection |
| `io_buffer.h` | Serialization abstraction: typed read/write to buffers |
| `gamestate/chunks.h` | Global `io_buffer*` declarations for all game data chunks |
| `mods/mods.h` | Mod image loading: group/name lookup, PNG support |
| `gamefiles/lang.h` | Localization string management |

## Save/Load Architecture

### Chunk System
The entire game state is divided into ~60+ named chunks (image grids, terrain, buildings, figures, economy, empire, messages, etc.).

Each chunk has:
- A global `io_buffer*` variable declared in `gamestate/chunks.h`
- A fixed size and optional compression flag
- An associated serialization callback

### FileIOManager Pattern
```cpp
manager.push_chunk(size, compressed, "buildings", &io_buildings);
manager.serialize();    // write to file
manager.unserialize();  // read from file
```
Manager handles: compression, file I/O, chunk ordering, version detection.

### Version Detection
Reads file header, auto-detects sg3/sgx format, applies correct schema.
Always version new save formats — add version checks before changing chunk layout.

### io_buffer Pattern
Two-pass: first pass validates/calculates size, second pass reads or writes.
Supports structs with `ANK_CONFIG_STRUCT` macro for auto-serialization.

## Adding a New Save Chunk

1. Add `io_buffer *io_mychunk` declaration in `gamestate/chunks.h`
2. Implement serialization in the relevant subsystem
3. Register in `FileIOManager` schema with correct size and compression flag
4. Add version guard if changing existing schema

## Mod System

- Mods registered by author + name → assigned group ID
- Image lookup: `group_id + image_name → image_id`
- PNG loading via `png_read.h`
- Max 1000 modded images globally

## Localization

`io/gamefiles/lang.h` — ID-based string lookup.
All user-visible strings go through localization, never hardcoded.

## Grid Serialization

All `grid_xx` data grids use:
```cpp
map_grid_save_buffer(grid, buffer);
map_grid_load_buffer(grid, buffer);
```
No special handling needed — add a chunk entry and call these.

## Invariants

- Never do ad-hoc file I/O in game code — always use the chunk system
- Compression is per-chunk and automatic — don't compress manually
- Chunk ordering in schema is load order — append new chunks at the end
- Version files for all format changes
