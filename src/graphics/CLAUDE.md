# Graphics Subsystem

Rendering abstraction over SDL2. Owns the painter, image atlas, fonts, and the UI command system.

## Key Files

| File | Purpose |
|------|---------|
| `graphics.h / .cpp` | Central render API: clipping, primitives, render commands |
| `painter.h / .cpp` | Sprite drawing: scaling, software clip, atlas lookup; draws through `g_render` |
| `render_device.h` | Render device interface (`g_render`, `sprite_draw_t`); implemented in `platform/renderer.cpp` |
| `screen.h / .cpp` | Global screen state (width, height, dialog offset) |
| `image.h / .cpp` | Image atlas management: SDL texture loading/caching |
| `image_desc.h` / `image_groups.h` / `imagepak_holder.h` | Image id descriptors, atlas group enums, pak ownership |
| `residency_atlas.h` | Residency atlas (implementation in `platform/residency_atlas.cpp`): repacks the frame's live sprites onto one page (`res_atlas::`) |
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

## Frame

`akhenaten_launcher_t::run_and_draw()` (`platform/akhenaten.cpp`), in order:

1. `game.update()` — simulation ticks.
2. `game.frame_begin()` under `draw_phase::scope` — the window stack draws itself
   (`graphics/window.cpp`). During this phase the simulation must not change:
   `draw_phase::check_write` logs `[draw-phase] ... writes the simulation during the draw`
   (tests 289, 334, 572, 581 check that drawing leaves the saved state unchanged).
3. `game.handle_input_frame()` — input, planner.
4. `game.frame_pre_present()` — the residency atlas packs this frame's misses and blits them onto
   its page. `g_render.renderer()` flushes the queued sprites first, so code that calls SDL itself
   (the atlas, ImGui) always draws after them.
5. `platform_renderer_render()` — last sprite flush, filter, render texture copied to the window, present.

### City view (`widget/widget_city.cpp`, `screen_city_t::draw`)

- The visible tile rows are split into blocks, one task per block on `game.mt`. A worker gets a
  copy of the `painter` whose `command_buffer` / `subcommand_buffer` point at its block
  (`ImageDraw::parallel_block_commands(blk)`), and writes `render_command_t` records — it draws nothing.
- `ImageDraw::merge_block_commands_into_global` appends the blocks in row order, renumbers `id`
  and rebases the subcommand ranges.
- `ImageDraw::apply_render_commands` sorts by (layer, sort y, sort x descending, id) — above 256 records
  the blocks are sorted in parallel and merged — then executes every record through `painter` on the
  main thread and clears the list.
- Two such passes: flat (ground, flat figures/ornaments, then terrain height) and height
  (buildings, animations, figures). Then single-threaded passes push records the same way:
  placement preview, post-processing effects, debug. `finalize_render` runs the debug records.
  The overlay view (`draw_with_overlay`) walks the tiles on the main thread only.
- Workers must not write anything shared. What a tile draw has to change goes through a queue
  applied on the main thread between the passes: water animation frames (`g_water_frame_queue` in
  `widget_city.cpp`), city ambient sounds (`sound_city().view_queue`). A figure's per-frame draw state
  lives in `figure_draw_state` (`grid/figure`), filled by `map_figure_sort_by_y`; pyramid ramp links
  are resolved by `pyramid_ramp_prepare_frame_links()` before the height pass.

### Records

`render_command_t` (`graphics.h`, trivially copyable, ~80 bytes): `rtype`, `layer`
(`layer_ground` sorts before `layer_scene`), `image_id`, `pixel`, an optional `sort_pixel`,
`mask`, `scale`, `flags`, and `start_subcommand..finish_subcommand` — a range in the subcommand
buffer drawn right after the parent, in order (`create_subcommand` attaches to the last
non-ground record). The sort moves whole records.

### painter → device

`painter` resolves the image, swaps the texture for a residency-atlas page rect
(`res_atlas::resolve`), computes scale and the software clip and hands a `sprite_draw_t` to
`g_render.draw_sprite`. The device (`platform/renderer.cpp`) queues sprites; `flush_sprites()` merges
consecutive sprites with the same material and clip into one `SDL_RenderGeometry`. Every primitive,
texture create/destroy or read-back flushes the queue first.

Window UI is pushed as `ui::cmd_t` and run by `ui::flush_commands()` at the end of the window draw;
a command pushed while another runs is executed in its place.

### Frame timers

`render_stats::phase_scope` charges main-thread time to one frame part; a nested scope pauses the
outer one, so the parts never overlap: `update`, `record` (city walk and record, waiting for the
workers), `merge`, `sort`, `execute` (records through `painter`), `ui`, `device` (sprite flushes),
`atlas` (`frame_pre_present`), `present`. Console `render_stats <tag>` logs the averages since the
last call (`render_stats[<tag>] parts_ms ...`, `other` = what no part covers); perfmon shows each part.

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
  `platform/akhenaten.cpp`; on by default on every platform.
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

The SDL render API is called only in `platform/` (`renderer.cpp`, `residency_atlas.cpp`, the Switch/Vita backends). Graphics, widget and window code draws through `g_render` from `graphics/render_device.h` and through `painter`; render entry points log `called off the main thread` when used from a worker (`core/main_thread.h`).

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

- No SDL render calls outside `platform/` (see SDL2 Usage)
- Game UI: custom `ui::cmd_t`; debug overlays: ImGui
- Texture atlas IDs are stable — never hardcode pixel coordinates
