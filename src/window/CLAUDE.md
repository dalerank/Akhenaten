# Window & Widget Subsystem

`window/` — modal UI screens (dialogs, panels, info windows).
`widget/` — persistent HUD elements (sidebar, top menu, minimap, city view).

## Key Files

### window/
| File | Purpose |
|------|---------|
| `autoconfig_window.h / .cpp` | Base class for all windows; auto-loads layout from config; inherits `ui::widget` |
| `message_dialog*.cpp` | Modal dialogs for game events, advisors, tutorials |
| `window_city.h / .cpp` | Main city view window |
| `editor/` | Scenario editor windows |

### widget/
| File | Purpose |
|------|---------|
| `widget_city.h` | Main gameplay screen: isometric rendering, tile input, overlay tooltips |
| `widget_sidebar.h` | Collapsible sidebar with expanded/collapsed states |
| `widget_top_menu_game.h` | Top menu bar with submenu support |
| `widget_minimap.h` | Small map overlay |
| `city/` | City rendering helpers (tile drawing, building ghosts, ornaments) |

## Window vs Widget

| | `window/` | `widget/` |
|--|-----------|-----------|
| Lifetime | Modal (shown/hidden) | Persistent (always active during gameplay) |
| Examples | Building info, message dialogs, empire map | Sidebar, top menu, minimap |
| Base class | `autoconfig_window` → `ui::widget` | `autoconfig_window` |

## Window Stack

`windows_manager_t` (`g_window_manager`) — queue of up to 6 windows.
Windows are modal (one active), but underlying windows draw for dialogs over gameplay.

## Adding a New Window

1. Create `window_my_window.h` inheriting from `autoconfig_window`
2. Implement: `draw_background()`, `draw_foreground()`, `handle_mouse()`, `get_tooltip_text()`, `get_section()`
3. Override `archive_load()` to load element tree from config
4. Build UI in `draw_foreground()` using `ui::button()`, `ui::panel()`, `ui::label()`
5. Register with `window_show()` to display

## Adding a New Widget

1. Create in `widget/` inheriting from `autoconfig_window`
2. Call from main game loop (see `widget_top_menu_draw()`, `widget_sidebar_city_*()`)
3. Manages state across frames; handles its own input and drawing

## Adding a New UI Element Type

1. Create in `graphics/elements/` inheriting from `ui::element`
2. Override `draw()`, `load()`, property setters
3. Add `dcast_*` helper for type-safe access if needed
4. Register in `ui_js.h` for JavaScript bindings if needed

## Input Handling

- Return `true` from handlers if event consumed (prevents fallthrough)
- Mouse: `m->button`, `m->x`, `m->y`
- Tooltips: set via `ui::set_tooltip()` during draw or input; queried via `ui::get_tooltip()`

## JS Callbacks

`autoconfig_window` elements can have JavaScript callbacks.
Use `ui_js.h` bindings to expose new element events to scripts.

## Invariants

- Windows must go through `g_window_manager`, not drawn directly
- Widgets called from main game loop — not modal, not pushed to window stack
- ImGui only in debug overlays (`overlay_menu_js.cpp`), not in regular windows/widgets
