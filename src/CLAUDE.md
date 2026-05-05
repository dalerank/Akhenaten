# Source Architecture

## Module Responsibilities

| Directory | What it owns |
|-----------|-------------|
| `building/` | Building instances, types, static params, construction planner, monuments |
| `city/` | City simulation aggregate — population, labor, finance, religion, sentiment, resources |
| `figure/` | Figure base framework — movement, routing, AI state machine, formations, combat |
| `figuretype/` | Concrete figure types (cartpusher, soldier, immigrant, merchant, enemy, animal, etc.) |
| `graphics/` | SDL2 rendering, image atlas, fonts, UI command system, painter abstraction |
| `grid/` | Tile map data grids, pathfinding/routing, terrain, water, floodplain |
| `window/` | Modal UI windows (city info, building panels, message dialogs, empire screen) |
| `widget/` | Persistent HUD elements (sidebar, top menu, minimap, city view) |
| `scenario/` | Mission metadata, win criteria, timed events, requests, invasions |
| `io/` | Chunk-based save/load, mod image loading, localization strings |
| `game/` | Main game loop, resource type enums, config, simulation tick |
| `empire/` | Empire cities, trade routes, caravans, ships |
| `overlays/` | Map overlay rendering (desirability, crime, water, labor, etc.) |
| `js/` | MuJS VM integration, script loading, DAP debugger server |
| `platform/` | Platform-specific init code (Android, PS Vita, Nintendo Switch) |
| `events/` | Typed event bus infrastructure (`g_city_events`) |
| `core/` | Utilities: CRC32, event bus, ZIP, threading, math |

## Key Global Singletons

```cpp
g_city          // city_t — city simulation aggregate root
g_window_manager // windows_manager_t — modal window stack
```

## Common Patterns Across the Codebase

### METAINFO macro (building and figure registration)
Both buildings and figures use a macro to register their type:
```cpp
BUILDING_METAINFO(BUILDING_FARM, building_farm, building_industry)
FIGURE_METAINFO(FIGURE_CARTPUSHER, figure_cartpusher)
```
This sets `TYPE` constant and registers the type in the factory. Never skip it.

### Runtime data buffer
Both buildings (186 bytes) and figures (40 bytes) carry a fixed-size `runtime_data` buffer
for type-specific mutable state. Access via macro-generated accessors.
Do not exceed the buffer limit — enforced by `static_assert`.

### Static params (immutable config)
Per-type configuration loaded once from config archives at startup.
`building_static_params`, `figure_static_params` — never modified at runtime.
Access: `building::current_params()`, figure equivalent.

### Type-safe downcasting
```cpp
auto *farm = building->dcast<building_farm>();   // returns nullptr if wrong type
auto *farm = building->dcast_farm();              // convenience shorthand
```
Never use `static_cast` for building/figure downcasts.

### Update cycle (day/week/month/year)
Simulation runs: `update_day → update_week → update_month → update_year`
Each subsystem hooks into the relevant frequency. City drives building and figure updates.

### Event bus
Cross-subsystem notifications use typed events:
```cpp
g_city_events.post(event_finance_changed{amount});
```
Subscribers register callbacks; no direct cross-module coupling.

### Config/content loading
`ANK_CONFIG_PROPERTY(struct, field1, field2...)` exposes struct fields for JSON serialization.
Content loaded from SGX/SGX archives at startup.

## Data Flow Summary

```
scenario (mission config)
    ↓
grid (tile map data, pathfinding)
    ↓
city (simulation state)
   ├─ buildings (spawn figures, consume labor/resources)
   ├─ figures (walk grid, deliver goods, fight)
   └─ grid (desirability, crime, routing updated by both)
    ↓
graphics/window/widget (render city state to screen)
    ↓
io (persist all state to disk)
```
