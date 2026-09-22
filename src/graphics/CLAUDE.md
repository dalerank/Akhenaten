# Graphics Subsystem

Rendering abstraction over SDL2. Owns the painter, image atlas, fonts, and the UI command system.

## Key Files

| File | Purpose |
|------|---------|
| `graphics.h / .cpp` | Central render API: clipping, primitives, render commands |
| `painter.h / .cpp` | SDL2 abstraction: texture drawing, scaling, transforms |
| `screen.h / .cpp` | Global screen state (width, height, dialog offset) |
| `image.h / .cpp` | Image atlas management: SDL texture loading/caching |
| `image_desc.h` / `image_groups.h` / `imagepak_holder.h` | Image id descriptors, atlas group enums, pak ownership |
| `residency_atlas.h / .cpp` | Residency atlas: repacks the frame's live sprites onto one page (`res_atlas::`) |
| `animation.h` / `animkeys.h` | Animation descriptors and config keys |
| `window.h / .cpp` | Window manager queue (up to 6 concurrent windows), z-order |
| `font.h / .cpp` | Font definitions, glyph management (10+ font types) |
| `text.h` | Text measuring / drawing helpers |
| `video.h` | Intro / cutscene video playback |
| `screenshot.h` | Screenshot capture (`--screenshot-dir`) |
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

### Residency atlas (`res_atlas::`)
The SDL2 renderer auto-batches only while the bound texture and blend mode stay put.
Depth-sorted city drawing switches source texture constantly, which defeats batching.
The residency atlas repacks the sprites actually touched this frame onto a single page,
so consecutive draws share one texture.

- Gated by the `graphics_atlas_render` game feature (`res_atlas::set_render`), wired in
  `platform/akhenaten.cpp`; sources register from `platform/renderer.cpp`.
- `painter` calls `res_atlas::resolve()` to swap a draw onto the page; a miss falls back
  to the original texture, so correctness never depends on the atlas.
- Anything that reloads or frees image paks must `invalidate()` / `forget_source()`, or
  the page keeps stale rects.
- Stats are exposed through `dev/perfmon.cpp` (fill %, pack+blit ms); `dump()` writes the page.

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
