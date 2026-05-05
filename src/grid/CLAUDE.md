# Grid Subsystem

Owns all tile map data and pathfinding. The game world is a fixed 228×228 tile grid.

## Key Files

| File | Purpose |
|------|---------|
| `grid.h` | Core grid type system (`grid_xx`), map layout, iteration templates |
| `point.h` | `tile2i` coordinate type — relative (map) and absolute (grid) coords |
| `tiles.h` | Tile visual updates: roads, water, vegetation, rocks, meadows |
| `building.h` | Building occupancy map, damage, rubble, highlights |
| `property.h` | Bitfield properties: multi-tile marking, native land, construction state |
| `terrain.h` | Terrain type data |
| `elevation.h` | Height data |
| `vegetation.h` | Plant growth data |
| `water.h / canals.h / floodplain.h` | Water systems and flood mechanics |
| `routing/routing.h` | Pathfinding: distance grids, terrain traversal, connectivity checks |
| `*_strength.h` | Strength grids for soldier/enemy/animal units |

## Coordinate System

- **Map-relative**: `(x, y)` within the map area
- **Grid-absolute**: offset `0..51983` into the flat 228×228 array
- Conversion: `MAP_OFFSET(x, y) = start_offset + GRID_OFFSET(x, y)`
  where `start_offset = scenario_map_data()`
- **`tile2i`** class caches computed offset lazily — prefer it over manual math
- Always check `map_grid_is_valid_offset(offset)` before accessing a tile

## Grid Data System

`grid_xx<T>` template stores typed data per tile (uint8/int8/uint16/int16/uint32/int32).
Grids self-register on construction. Operations:
```cpp
map_grid_get(grid, offset)
map_grid_set(grid, offset, value)
map_grid_fill(grid, value)
map_grid_save_buffer / map_grid_load_buffer   // serialization
```

## Tile Iteration

```cpp
map_grid_area_foreach(tile, radius, [](tile2i t) { /* ... */ });
// Automatically dispatches tile2i vs offset; prefer over manual loops
```

Batch updates faster than individual sets — use `map_tiles_update_all_*()` for full map,
`map_tiles_update_region_*()` for local changes.

## Routing / Pathfinding

BFS distance grids from a source tile. Multiple traversal modes:
- `ROADS` — citizen/worker movement
- `ENEMY` — enemy units
- `WALLS` — wall patrollers
- `ANIMAL` — animal herds
- `WATER` (BOAT / DEEP_WATER) — ships and ferries
- `AMPHIBIA` — amphibious units

```cpp
map_routing_calculate_distances_from_point(tile, terrain_type);
// Populates distance grid; figure routing reads from it
```

## Cross-Subsystem Connections

- **`building/`** — writes occupancy map on place/destroy
- **`city/`** — reads desirability, crime, malaria risk, water, natives
- **`figure/`** — figures hold `tile2i` and `routing_path_id`; pathfinding results stored in grid
- **`scenario/`** — map entry/exit points, invasion zones, herd spawn points
- **`io/`** — all grids serialized via `map_grid_save/load_buffer`

## Invariants

- Map size is always 228×228 (GRID_LENGTH = 228)
- `tile2i` is the canonical coordinate type — avoid raw offsets in new code
- Always validate offsets before grid access
- Floodplain tiles update annually — don't assume static terrain
