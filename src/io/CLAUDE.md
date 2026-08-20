# IO Subsystem

Chunk-based save/load, mod image loading, and localization strings.

## Key Files

| File | Purpose |
|------|---------|
| `chunk_serializer.h` | `ChunkSerializer` / `g_chunk_io` — schema, serialize/unserialize |
| `chunk_container.h` | `svx` — sectioned `.svx` container + shared prefixed zip codec |
| `io_buffer.h` | Typed bind/read/write into chunk buffers; optional defaulters |
| `gamestate/boilerplate.h` | `GamestateIO` facade, `save_data_version()` |
| `gamestate/boilerplate_detail.h` | `GamestateLoadDetail` — pre/post load, version probe, raw map load |
| `gamestate/save_versions.h` | `latest_save_version` changelog |
| `gamestate/file_schemas.h` | Format schema entry points (`file_schema`, builders) |
| `gamestate/file_schema_*.cpp` | Per-format `push_chunk` lists (map / sav / svx) |
| `gamestate/chunks.h` | Global `io_buffer*` declarations for game data chunks |
| `io.h` | Low-level file reads (`io_read_file_into_buffer`, sg3/sgx counts) |
| `mods/mods.h` | Mod image loading: group/name lookup, PNG support |
| `gamefiles/lang.h` | Localization string management |

## Save/Load Layers

```
GamestateIO::write_savegame / load_savegame / write_map / write_family_marker / …
        ↓
ChunkSerializer (g_chunk_io)  — push_chunk schema, fill buffers, apply state
        ↓
  .svx  → svx sectioned container (by name, CRC, defaulters)
  .sav / .map → legacy positional stream (unchanged Pharaoh layouts)
```

`write_family_marker` writes a tiny positional `.sav` stub (`family_index`) so `Save/<player>/` exists when starting a dynasty — not a city save (no Ironwill / last_save).

### Versions (do not conflate)

- `save_data_version()` / `latest_save_version` — **what** is inside chunks; drives `if (version > N)` in binds and schema gates.
- `svx::CONTAINER_REV` / `svx_container_version()` — **how** `.svx` is laid out on disk; only the container cares.

Current save data version: **189** (sectioned `.svx`; chunk field layout unchanged at that bump).

### ChunkSerializer

```cpp
g_chunk_io.push_chunk(size, compressed, "buildings", iob_buildings);
g_chunk_io.serialize(path, 0, FILE_FORMAT_SAVE_FILE_EXT, save_data_version(), file_schema);
g_chunk_io.unserialize(reader, 0, format, GamestateIO::read_file_version, file_schema);
```

- Schema is built by `file_schema` in `gamestate/file_schemas.cpp`, with per-format
  lists in `file_schema_map.cpp`, `file_schema_sav.cpp` (`.sav` + family marker),
  `file_schema_svx.cpp`. Legacy positional `.svx` and sectioned `.svx` share
  `file_schema_svx`; dead padding chunks are gated with `g_chunk_io.is_sectioned()`.
- Writes go through `<path>.tmp` then rename (atomic when `offset == 0`).
- `file_chunk_t::resize()` is the **only** place a chunk buffer may be reallocated (re-hooks `io_buffer`).

### `.svx` container (`class svx`)

Self-describing sections: file header + per-section header/payload/epilog. Lookup by **name**; order in the file does not matter. Apply order still follows the schema.

| Event | Policy |
|-------|--------|
| Missing section + `iob->has_default()` | apply defaulter, log |
| Missing section, no defaulter | **refuse load** (required chunk) |
| Bad CRC / truncated / broken epilog | **refuse load** |
| Unknown section in file | warn, skip |

Legacy `.svx` (no magic) still loads via the positional path. Dead chunks `file_version` / `chunks_schema` stay in that path only (`is_sectioned()` false).

Shared codec: every compressed piece is `[u32 prefix][body]` with `svx::PAYLOAD_UNCOMPRESSED` / zip — used by both legacy and sectioned writers (`svx::compress_prefixed` / `decompress_prefixed`).

Chunk names are on-disk keys: max `svx::NAME_LEN` (32), no silent truncation.

### io_buffer

Bind callback for read/write. Optional default callback / `reset_data()` for chunks that may be absent in older saves. Presence of a defaulter = chunk is optional.

## Adding a New Save Chunk

1. Declare `io_buffer *io_mychunk` in `gamestate/chunks.h`, implement bind (+ defaulter if the chunk can be missing from older files).
2. `push_chunk(size, compressed, "short_name", iob)` in `file_schema_svx.cpp` for `FILE_FORMAT_SAVE_FILE_EXT` (name ≤ 32 chars).
3. Bump `latest_save_version` only if existing field layout/meaning changes — or when gating the new chunk with `if (file_version > N)` until the version cascade is cleaned up.
4. Do not rename existing chunk names without an alias plan — names are part of the `.svx` format.

## Mod System

- Mods registered by author + name → group ID
- Image lookup: `group_id + image_name → image_id`
- PNG via `png_read.h`

## Localization

`io/gamefiles/lang.h` — ID-based lookup. User-visible strings go through localization, not hardcoded C++.

## Grid Serialization

```cpp
map_grid_save_buffer(grid, buffer);
map_grid_load_buffer(grid, buffer);
```

## Invariants

- Game code goes through `GamestateIO` / `g_chunk_io`, not ad-hoc save writes
- Compression is per-chunk via the shared prefixed codec — do not invent a second zip framing
- Schema apply order matters even for sectioned files (binds may depend on earlier chunks)
- Corrupt/truncated `.svx` must fail the whole load; missing optional sections use defaulters only
