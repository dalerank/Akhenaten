# JS / MuJS bindings

Bridge between game C++ and embedded MuJS scripts (`src/scripts/`).

## Placement preview draw APIs

Ghost preview for buildings is increasingly implemented in JS
(`[es=(building_*, ghost_preview)]`). Shared paint entry points live on
`city.planner` (`src/scripts/city/planner.js` → `src/js/city_planner_js.cpp`).

**Conventions** (full detail: `src/building/CLAUDE.md` → «JS ghost_preview / placement draw APIs»):

- Full `COLOR_MASK_*` can now be passed from JS: bind color params as `color` (== `uint32_t`),
  which converts via `js_touint32` (J1, resolved). Do not use `int` for color params.
- Port preview *logic* to JS; use planner primitives — do not add thin `__*_draw_*`
  wrappers around a single existing C++ draw function.
- Call `draw_ghost` (parent) before `draw_from_below` / `draw_ghost_overlay` (subcommands).

Reference implementation: `src/scripts/building/farm.js` (`building_farm_ghost_preview`).
