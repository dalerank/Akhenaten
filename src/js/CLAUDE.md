# JS / MuJS bindings

Bridge between game C++ and embedded MuJS scripts (`src/scripts/`).

## Placement preview draw APIs

Ghost preview for buildings is increasingly implemented in JS
(`[es=(building_*, ghost_preview)]`). Shared paint entry points live on
`city.planner` (`src/scripts/city/planner.js` → `src/js/city_planner_js.cpp`).

**Conventions** (full detail: `src/building/CLAUDE.md` → «JS ghost_preview / placement draw APIs»):

- Keep full `COLOR_MASK_*` in C++ draw helpers until color args use `uint32` (J1).
- Port preview *logic* to JS; use planner primitives — do not add thin `__*_draw_*`
  wrappers around a single existing C++ draw function.
- Call `draw_ghost` (parent) before `draw_from_below` / `draw_ghost_overlay` (subcommands).

Reference implementation: `src/scripts/building/farm.js` (`building_farm_ghost_preview`).
