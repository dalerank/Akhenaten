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
The SDL2 OpenGL renderer merges consecutive draws only while the bound texture and blend mode
stay put (the D3D9 backend never merges: one draw call per sprite whatever we do).
The residency atlas repacks the sprites actually touched this frame onto a single page,
so consecutive draws share one texture.

- Gated by the `graphics_atlas_render` game feature (`res_atlas::set_render`), wired in
  `platform/akhenaten.cpp`; on by default on desktop, off on Android/web/consoles.
  Sources register from `platform/renderer.cpp`.
- Page size is `graphics_atlas_page_size` capped by 8192 and the renderer's max texture size.
  A full page is recycled (at most once per 600 frames); when it fills again, sprites that do not
  fit draw from their pak pages and one warning is logged.
- `painter` calls `res_atlas::resolve()` to swap a draw onto the page; a miss falls back
  to the original texture, so correctness never depends on the atlas.
- Anything that reloads or frees image paks must `invalidate()` / `forget_source()`, or
  the page keeps stale rects.
- SDL queues draws only with `SDL_HINT_RENDER_BATCHING`, which it drops for a renderer chosen by name;
  `platform/renderer.cpp` sets it. Of the queued copies only the opengl backend merges same-texture runs;
  direct3d / direct3d11 / direct3d12 still issue one draw per copy from a single vertex upload.
- Stats are exposed through `dev/perfmon.cpp` (fill %, pack+blit ms); `dump()` writes the page.
- `render_stats` (console, perfmon) counts sprite draws, texture/blend switches and estimated
  batches per frame, plus draw/present ms.
- Every painter draw uses the premultiplied blend mode; `ImgFlag_Alpha` scales the tint by the
  alpha instead of switching to `SDL_BLENDMODE_BLEND`. Only PNG textures marked straight
  (`texture_alpha.h`) still blend as straight alpha.

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
