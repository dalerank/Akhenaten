# Graphics Subsystem

Rendering abstraction over SDL2. Owns the painter, image atlas, fonts, and the UI command system.

## Key Files

| File | Purpose |
|------|---------|
| `graphics.h / .cpp` | Central render API: clipping, primitives, render commands |
| `painter.h / .cpp` | SDL2 abstraction: texture drawing, scaling, transforms |
| `screen.h / .cpp` | Global screen state (width, height, dialog offset) |
| `image.h / .cpp` | Image atlas management: SDL texture loading/caching |
| `window.h / .cpp` | Window manager queue (up to 6 concurrent windows), z-order |
| `font.h / .cpp` | Font definitions, glyph management (10+ font types) |
| `elements/ui.h / .cpp` | Core UI command system: `cmd_t` accumulation and flush |
| `elements/generic_button.h` | Simple button model with callbacks |
| `elements/scrollbar.h` | Scrollbar state and input |
| `elements/panel.h` | Panel rendering (outer/inner styles) |
| `elements/imui.h / .cpp` | ImGui integration (debug/overlay UIs only) |

## Rendering Patterns

### UI Command Accumulation (primary pattern)
```cpp
ui::push(ui::cmd_t{...});   // queue draw commands
ui::flush_commands();        // execute all at once
```
Use `ui::button()`, `ui::panel()`, `ui::label()` helpers instead of raw `cmd_t`.

### Render Command System (lower level)
`render_command_t` describes tile/sprite/ornament rendering.
Parallel support: per-thread command buffers merged after workers finish.
Types: tiles, sprites, ornaments, generic draws, rectangles.

### Drawing conventions
- Positions in screen pixels; blocks are 16×16
- Colors: `color` type (32-bit ARGB)
- Fonts: pick from `FONT_*` enum
- Image IDs reference atlas groups (e.g., `GROUP_DIALOG_BACKGROUND`)
- Images must be pre-loaded into atlases; IDs are stable references

## SDL2 Usage

Never call SDL directly from game code. All SDL access goes through `painter`:
- `SDL_Texture` — one texture atlas per image group
- `SDL_Renderer` — held by painter, used for all draw operations

## ImGui Usage

ImGui is **only for debug/overlay UIs** — not for main game UI.
Wrapper: `ui::Begin(name)` draws a game-style background panel then calls `ImGui::Begin()`.
Main game UI uses the custom `ui::cmd_t` system.

## Layer Stack

```
painter (SDL2 wrapper)
  ↑
screen (resolution state)
  ↑
image (texture atlas cache)
  ↑
ui elements (buttons, panels, text)
  ↑
windows (modal screens)
  ↑
widgets (persistent HUD)
```

## Invariants

- No direct SDL calls outside `painter` and `graphics.cpp`
- Game UI: custom `ui::cmd_t`; debug overlays: ImGui
- Texture atlas IDs are stable — never hardcode pixel coordinates
