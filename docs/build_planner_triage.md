# build_planner triage

Measured 2026-09-09 against `src/building/construction/build_planner.h` (216 lines) and
`build_planner.cpp` (1512 lines). Nothing here is changed yet; this is the survey behind the
"split the planner" item, kept so the work can start from numbers instead of impressions.

## Shape

| | count | where |
|---|---|---|
| public mutable data members | 24 | `build_planner.h:131-156` |
| private data members | 12 | `build_planner.h:68-83` |
| methods / inline functions | 80 | whole class |
| `public:` / `private:` flips | 3 | `build_planner.h:104`, `:163`, `:166` |
| rule-flag wrappers | 22 | `build_planner.h:108-129` |
| inline tile arrays | 5 | `build_planner.h:68-74` |

One global instance, `g_city_planner`.

## State is public and written from outside

24 data members sit in the public section, and outside code does not only read them -- it
writes them. Ten writes to four fields, none of which goes through a method:

| field | external writes |
|---|---|
| `global_rotation` | 4 |
| `road_orientation` | 2 |
| `draw_as_constructing` | 2 |
| `custom_building_variant` | 2 |

Reads are wider still: `build_type` is touched from 12 places outside the planner,
`in_progress` from 10, `global_rotation` from 9. So the class has no invariant it can defend --
any caller can leave it half-configured, and `construction_active()` / `in_progress` /
`build_type` can disagree with each other.

## Memory

`TILE_DIM = 40` (sized for the 17x34 large royal tomb plus rotation headroom), and five arrays
are inline members, so the global carries them whether or not anything is being placed:

| array | element | bytes |
|---|---|---|
| `tile_graphics_array` | `int` | 6 400 |
| `tile_sizes_array` | `int` | 6 400 |
| `tile_blocked_array` | `bool` | 1 600 |
| `tile_coord_cache` | `tile2i` (5 ints = 20 B) | 32 000 |
| `pixel_coords_cache` | `vec2i` (8 B) | 12 800 |
| **total** | | **~58 KB** |

`tile_coord_cache` alone is 32 KB because `tile2i` stores five ints (`x`, `y`, `grid_offset`,
`abs_x`, `abs_y` -- `src/grid/point.h:11-18`), not a pair.

## Placement drawing lives in three places

| path | size | count |
|---|---|---|
| static helpers on `build_planner` | `build_planner.h:191-200` | 9 statics, 8 of them drawing |
| `building_planer_renderer` (`building_impl::preview`) | 279 lines | 17 C++ `ghost_preview` overrides |
| JS `ghost_preview` via `src/js/city_planner_js.cpp` (277 lines) | `src/scripts/building/*.js` | 13 implementations |

The migration from C++ `preview::ghost_preview` to JS is partway done (the rules are in
`src/building/CLAUDE.md`), so a type's ghost can currently be defined in either of two places,
with a third set of primitives underneath. Any split of the planner has to decide where the
drawing half ends up, or it will just move the seam.

## Rule flags

`e_planner_rule` (23 named values, `build_planner.h:10-38`) is stored in an `sbitarray64
rules`, reached through `is_flag()`, and wrapped by 22 one-line predicates.

Worth being precise: these wrappers are **used**, 1-6 call sites each -- they are not dead
weight, so collapsing them to `is_flag(Rule)` is a style call, not a cleanup. The one
exception is `needFerry()`, which has **zero** call sites and can go.

Note also that the enum has deliberate holes (15, 19, 20 are skipped), so it is not dense --
anything that wants to iterate it or index by it has to account for that.

## Suggested split

Three parts, in the order they can be done without a flag day:

1. **`planner_grid`** -- the five arrays plus `update_coord_caches()`, `init_tiles()`,
   `set_tile_size()`, `set_graphics_row()`, `is_blocked_tile()`, `pixel_coord_offset()`.
   Self-contained, no callers outside the planner, and it takes the 58 KB with it so it can be
   allocated only while a placement is active.
2. **`planner_rules`** -- `e_planner_rule`, `rules`, `is_flag()`, `set_flag()`, the checks
   (`update_obstructions_check`, `update_requirements_check`, `checks_generic_rules`,
   `check_road_access`, `update_unique_only_one_check`) and the warnings.
3. **`planner_view`** -- the nine static draw helpers plus `draw()`, `draw_graphics()`,
   `draw_road_access_marker()`, `draw_tile_graphics_array()`. This is the part that has to be
   reconciled with the two other drawing paths above, so it goes last.

What stays behind is the state machine: `build_type`, `start` / `end`, the four orientation
fields, `in_progress`, and `construction_start` / `update` / `finalize` / `cancel`. That is
where the public fields should become private, once the parts above stop reading them.

## Risk

This touches the placement UI, which `CONTRIBUTING.md` puts off-limits for now, and the
integral suite covers placement only per building type (`tests/*_place*.js`), not the planner's
own state transitions. Steps 1 and 2 are behaviour-preserving and testable through the existing
placement tests; step 3 is not, and should not start without a way to see the ghosts.
