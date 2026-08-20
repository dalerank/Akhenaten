# JS / MuJS bindings

Bridge between game C++ and embedded MuJS scripts (`src/scripts/`).

## UI callbacks (ES-only)

Canon for new / migrated UI element trees (`ui { … }` in `src/scripts/ui_*.js`).
Full migration checklist: `docs/ui_es_only_migration.md`.

**Do:**

- Push callbacks via `*_event` fields: `onclick_event`, `onrclick_event`,
  `ondraw_event`, `onhover_event`, `oninput_event`, `ondoubleclick_event`.
- Or omit `onclick_event`: click dispatches `[es=(widget_id, element_id)]`
  (element key in `ui { }`). Use explicit `onclick_event` when the event
  name should differ from the element id (shared handlers, helpers).
- Put logic in `[es=(widget_id, event_name)]` handlers.
- Helpers: override like empire —
  `help_button({ onclick_event: "help" })` + `[es=(W, help)]`
  (defaults already use `onclick_event: "help"` / `"go_back"`).
- Shared chrome across a window family: tag windows `[es=ParentType]` and
  register one `[es=(ParentType, event)]`. Dispatch tries exact
  `section+event` first, then falls back to `ParentType+event`
  (advisor strip, building_info mothball/overlay).
- Top menu: submenu items use immediate `ui.button` + `onclick_event`
  (fallback: menu `onclick_event`, then `item.id`; handlers on
  `top_menu_submenu` / `top_menu_editor_submenu`).

**Do not (new code):**

- `onclick: function(){…}` / other anonymous push callbacks in config
- `onclick: factory(…)` (e.g. `show_window_by_id("…")`, `show_advisor_window(…)`)
- `onclick: named_global` / `.onclick = …` on button elements (accessor removed)
- Top-menu item `onclick: named` (use `onclick_event` on `ui.button`)

Named `onclick` / `onrclick` / `onhover` / `onunhover` on button elements
and named `onclick_item` / `onrightclick_item` / `ondoubleclick_item` on
scroll lists are removed (use `*_event` or omit click for element-id ES).
JS `onclick` accessor removed.

**Out of scope for this rule:** anonymous `textfn` / `checkedfn` (pull APIs).

Reference: `src/scripts/ui_empire_window.js`.

## Placement preview draw APIs

Ghost preview for buildings is increasingly implemented in JS
(`[es=(building_*, ghost_preview)]`). Shared paint entry points live on
`city_planner` (`src/scripts/city/planner.js` → `src/js/city_planner_js.cpp`).

**Conventions** (full detail: `src/building/CLAUDE.md` → «JS ghost_preview / placement draw APIs»):

- Full `COLOR_MASK_*` can now be passed from JS: bind color params as `color` (== `uint32_t`),
  which converts via `js_touint32` (J1, resolved). Do not use `int` for color params.
- Port preview *logic* to JS; use planner primitives — do not add thin `__*_draw_*`
  wrappers around a single existing C++ draw function.
- Call `draw_ghost` (parent) before `draw_from_below` / `draw_ghost_overlay` (subcommands).

Reference implementation: `src/scripts/building/farm.js` (`building_farm_ghost_preview`).
