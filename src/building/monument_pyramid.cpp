#include "monument_pyramid.h"

#include "graphics/view/view.h"
#include "monuments.h"
#include "core/direction.h"
#include "core/custom_span.hpp"
#include "graphics/image.h"
#include "widget/city/tile_draw.h"
#include "widget/city/flat_draw.h"
#include "window/building/common.h"
#include "city/city_warnings.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "game/game.h"
#include "game/undo.h"
#include "city/city_resource.h"
#include "city/city_message.h"
#include "grid/random.h"
#include "grid/tiles.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "grid/figure.h"
#include "graphics/view/lookup.h"
#include "graphics/graphics.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "figuretype/figure_worker.h"
#include "construction/build_planner.h"
#include "widget/widget_city.h"
#include "grid/routing/routing_grids.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include "grid/canals.h"
#include "grid/water.h"
#include "building/monument_mastaba.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_pyramid_ramp.h"
#include "graphics/image_groups.h"

#include <numeric>
#include <string>
#include <algorithm>

namespace {

constexpr int k_causeway_width = 2;
constexpr int k_causeway_max_length = 80;

// N, E, S, W in map coords.
const vec2i k_causeway_dir[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
const vec2i k_causeway_perp[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool building_type_is_pyramid_complex(e_building_type t) {
    return t == BUILDING_STEPPED_PYRAMID_COMPLEX
        || t == BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX
        || t == BUILDING_PYRAMID_COMPLEX
        || t == BUILDING_GRAND_PYRAMID_COMPLEX
        || t == BUILDING_MUDBRICK_PYRAMID_COMPLEX
        || t == BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX;
}

bool building_type_is_grand_pyramid_complex(e_building_type t) {
    // OG: grand causeway is fixed east (map), not player-rotated / multi-dir.
    return t == BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX
        || t == BUILDING_GRAND_PYRAMID_COMPLEX
        || t == BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX;
}

// OG pyramid_part_update_image (finished stays blocks==0 on CASING):
//   half  -> IMAGE_GROUP_BENT_PYRAMID (Bent_pyramid_00112+) row (blocks-1) / (5-blocks)
//   else  -> IMAGE_GROUP_PYRAMID (Bent_pyramid_00001+, same art as Pyramid) row (blocks-1) / (11-blocks)
int bent_og_part_image(building& part, const pyramid_part_state& ps, bool finished) {
    building* head = part.main();
    const e_building_type t = head ? head->type : part.type;
    const auto& params = building_static_params::get(t);
    const int pyramid0 = params.first_img("corner_bricks");
    if (pyramid0 <= 0) {
        return 0;
    }
    const int half_first = params.first_img("half_bricks");
    const int bent0 = half_first > 0 ? half_first : pyramid0 + 111;
    int kind = g_monument_pyramid_engine.layout_kind(head, ps.subtype);
    kind = g_monument_pyramid_engine.rotated_kind(kind, g_camera.orientation / 2);
    const bool half = g_monument_pyramid_engine.bent_is_half_layer((int)ps.size_variant, (int)ps.layer);
    if (finished || ps.stage == PYRAMID_STAGE_CASING) {
        const int blocks = finished ? 0 : (int)ps.blocks;
        return half ? bent0 + (5 - blocks) * 8 + kind : pyramid0 + (11 - blocks) * 8 + kind;
    }
    if (ps.blocks > 0) {
        return (half ? bent0 : pyramid0) + (ps.blocks - 1) * 8 + kind;
    }
    return 0;
}

struct pyramid_causeway_probe {
    bool ok = false;
    int dir = 1; // east preferred
    int length = 0;
    tile2i origin;
};

// Cursor tile → map NW of the multipart footprint. Default construction_place
// uses building_size (2×2 part) which under-corrects 8–20 tile pyramids.
tile2i pyramid_place_nw_from_cursor(tile2i end, vec2i init_tiles) {
    const int sx = init_tiles.x;
    const int sy = init_tiles.y;
    switch (g_camera.orientation) {
    case DIR_2_BOTTOM_RIGHT:
        return end.shifted(-sx + 1, 0);
    case DIR_4_BOTTOM_LEFT:
        return end.shifted(-sx + 1, -sy + 1);
    case DIR_6_TOP_LEFT:
        return end.shifted(0, -sy + 1);
    default:
        return end;
    }
}

bool causeway_strip_clear(tile2i origin, int dir, int length, int width) {
    const vec2i step = k_causeway_dir[dir & 3];
    const vec2i perp = k_causeway_perp[dir & 3];
    for (int i = 0; i < length; ++i) {
        for (int w = 0; w < width; ++w) {
            tile2i t = origin.shifted(step.x * i + perp.x * w, step.y * i + perp.y * w);
            if (!map_grid_is_inside(t, 1)) {
                return false;
            }
            // TERRAIN_NOT_CLEAR already includes floodplain/road/water/building.
            // Do not also reject floodplain-*adjacent* land — Nile approaches are
            // almost always next to floodplain, and that would make complexes
            // unplaceable on real maps.
            if (map_terrain_is(t, TERRAIN_NOT_CLEAR) || map_has_figure_at(t)) {
                return false;
            }
        }
    }
    return true;
}

bool causeway_end_reaches_water(tile2i origin, int dir, int length, int width) {
    const vec2i step = k_causeway_dir[dir & 3];
    const vec2i perp = k_causeway_perp[dir & 3];
    for (int w = 0; w < width; ++w) {
        tile2i t = origin.shifted(step.x * length + perp.x * w, step.y * length + perp.y * w);
        if (!map_grid_is_inside(t, 1) || !map_terrain_is(t, TERRAIN_WATER)) {
            return false;
        }
    }
    return true;
}

tile2i causeway_origin_on_face(tile2i pyramid_nw, vec2i size, int dir, int width) {
    switch (dir & 3) {
    case 0: // north face → -y
        return pyramid_nw.shifted((size.x - width) / 2, -1);
    case 1: // east face → +x
        return pyramid_nw.shifted(size.x, (size.y - width) / 2);
    case 2: // south face → +y
        return pyramid_nw.shifted((size.x - width) / 2, size.y);
    case 3: // west face → -x
        return pyramid_nw.shifted(-1, (size.y - width) / 2);
    }
    return pyramid_nw;
}

pyramid_causeway_probe map_pyramid_complex_find_causeway(tile2i pyramid_nw, vec2i size, bool east_only) {
    pyramid_causeway_probe best;
    // Prefer east (OG grand is east-only); plain complex may use other cardinals.
    const int order_all[4] = {1, 2, 3, 0};
    const int order_east[1] = {1};
    const int *order = east_only ? order_east : order_all;
    const int n_dirs = east_only ? 1 : 4;
    for (int oi = 0; oi < n_dirs; ++oi) {
        const int dir = order[oi];
        const tile2i origin = causeway_origin_on_face(pyramid_nw, size, dir, k_causeway_width);
        for (int length = 1; length <= k_causeway_max_length; ++length) {
            if (!causeway_strip_clear(origin, dir, length, k_causeway_width)) {
                break;
            }
            if (!causeway_end_reaches_water(origin, dir, length, k_causeway_width)) {
                continue;
            }
            best.ok = true;
            best.dir = dir;
            best.length = length;
            best.origin = origin;
            return best;
        }
    }
    return best;
}

void draw_causeway_ghost(build_planner &planer, painter &ctx, const pyramid_causeway_probe &probe, bool blocked) {
    if (!probe.ok && probe.length <= 0) {
        return;
    }
    const int length = probe.ok ? probe.length : std::max(1, probe.length);
    const vec2i step = k_causeway_dir[probe.dir & 3];
    const vec2i perp = k_causeway_perp[probe.dir & 3];
    const color mask = blocked ? COLOR_MASK_RED_30 : COLOR_MASK_GREEN_30;
    tile2i origin = probe.origin;
    for (int i = 0; i < length; ++i) {
        for (int w = 0; w < k_causeway_width; ++w) {
            tile2i t = origin.shifted(step.x * i + perp.x * w, step.y * i + perp.y * w);
            if (!map_grid_is_inside(t, 1)) {
                continue;
            }
            planer.draw_flat_tile(ctx, g_camera.lookup_tile_to_pixel(t), mask);
        }
    }
}

pyramid_causeway_probe causeway_probe_from_runtime(tile2i pyramid_nw, vec2i size, uint8_t length, uint8_t dir) {
    pyramid_causeway_probe probe;
    if (length == 0) {
        return probe;
    }
    probe.ok = true;
    probe.dir = dir & 3;
    probe.length = length;
    probe.origin = causeway_origin_on_face(pyramid_nw, size, probe.dir, k_causeway_width);
    return probe;
}

int complex_walkway_image(e_building_type complex_type) {
    const auto &params = building_static_params::get(complex_type);
    int img = params.first_img("complex_walkway");
    if (img <= 0) {
        img = params.first_img("clear_land");
    }
    if (img <= 0) {
        img = params.first_img("empty_land");
    }
    return img;
}

int annex_building_image(e_building_type complex_type, e_building_type annex_type) {
    // Pack from the parent complex `_pack` / base anim; group id from the annex
    // building's `base { id:… }` (9/10/11). OG orientation: valley uses ori/2
    // (4 frames), mortuary/causeway use ori/2&1 (2 frames).
    int pack = 0;
    if (complex_type != BUILDING_NONE) {
        const auto &cx = building_static_params::get(complex_type);
        pack = cx.animations["base"].pack;
        if (pack <= 0) {
            pack = cx.animations["clear_land"].pack;
        }
    }
    if (pack <= 0) {
        pack = building_static_params::get(annex_type).animations["base"].pack;
    }
    if (pack <= 0) {
        return 0;
    }

    const auto &ax = building_static_params::get(annex_type).animations["base"];
    const int group = ax.id > 0 ? ax.id : 9;
    image_ensure_pak_loaded(pack);
    const int base = image_id_from_group(pack, group);
    if (base <= 0) {
        return 0;
    }
    const int ori2 = (g_camera.orientation / 2) & 3;
    if (annex_type == BUILDING_VALLEY_TEMPLE) {
        return base + ori2;
    }
    return base + (ori2 & 1);
}

e_building_type annex_parent_complex_type(tile2i annex_tile) {
    // Causeway strip tiles around the annex stay owned by the complex main.
    for (int dy = -2; dy <= 3; ++dy) {
        for (int dx = -2; dx <= 3; ++dx) {
            tile2i n = annex_tile.shifted(dx, dy);
            if (!map_grid_is_inside(n, 1)) {
                continue;
            }
            building *b = building_at(n);
            if (!b || b->state == BUILDING_STATE_UNUSED) {
                continue;
            }
            building *main = b->main();
            if (main && building_type_is_pyramid_complex(main->type)) {
                return main->type;
            }
        }
    }
    return BUILDING_NONE;
}

void refresh_annex_orientation_tiles(building &annex) {
    const e_building_type cx = annex_parent_complex_type(annex.tile);
    int img = annex_building_image(cx, annex.type);
    if (img <= 0) {
        img = building_static_params::get(annex.type).base_img();
    }
    if (img <= 0) {
        return;
    }
    map_building_tiles_add(annex.id, annex.tile, annex.size, img, TERRAIN_BUILDING);
}

void refresh_complex_causeway_orientation(building &complex) {
    auto *mon = complex.dcast_monument();
    if (!mon) {
        return;
    }
    const auto &d = mon->runtime_data();
    if (d.causeway_length == 0) {
        return;
    }
    building_pyramid *pyr = complex.dcast_pyramid();
    if (!pyr) {
        return;
    }
    const pyramid_causeway_probe probe = causeway_probe_from_runtime(
        complex.tile, pyr->pyramid_params().init_tiles, d.causeway_length, d.causeway_dir);
    if (!probe.ok || probe.length <= 0) {
        return;
    }

    const int walk_img = complex_walkway_image(complex.type);
    const vec2i step = k_causeway_dir[probe.dir & 3];
    const vec2i perp = k_causeway_perp[probe.dir & 3];
    tile2i origin = probe.origin;
    for (int i = 0; i < probe.length; ++i) {
        const bool paint_walkway = (i < 2) || (i == probe.length - 1);
        for (int w = 0; w < k_causeway_width; ++w) {
            tile2i t = origin.shifted(step.x * i + perp.x * w, step.y * i + perp.y * w);
            if (!map_grid_is_inside(t, 1)) {
                continue;
            }
            const int owner = map_building_at(t.grid_offset());
            if (owner <= 0) {
                continue;
            }
            building *ob = building_get(owner);
            if (!ob) {
                continue;
            }
            if (building_type_is_pyramid_complex_annex(ob->type)) {
                // One refresh per 2×2 annex (draw from its NW tile only).
                if (ob->tile == t) {
                    refresh_annex_orientation_tiles(*ob);
                }
                continue;
            }
            if (owner == complex.id && paint_walkway && walk_img > 0) {
                map_image_set(t.grid_offset(), walk_img);
            }
        }
    }
}

void claim_causeway_tiles(int building_id, const pyramid_causeway_probe &probe) {
    if (!probe.ok || probe.length <= 0 || building_id <= 0) {
        return;
    }
    int walk_img = 0;
    if (building *b = building_get(building_id)) {
        walk_img = complex_walkway_image(b->type);
    }
    const vec2i step = k_causeway_dir[probe.dir & 3];
    const vec2i perp = k_causeway_perp[probe.dir & 3];
    tile2i origin = probe.origin;
    // OG pyramid_complex_area_op mode 2: walkway image on the start 2×2 and the
    // water-edge land column only; middle strip keeps existing ground tiles.
    for (int i = 0; i < probe.length; ++i) {
        const bool paint_walkway = (i < 2) || (i == probe.length - 1);
        for (int w = 0; w < k_causeway_width; ++w) {
            tile2i t = origin.shifted(step.x * i + perp.x * w, step.y * i + perp.y * w);
            if (!map_grid_is_inside(t, 1)) {
                continue;
            }
            const int grid_offset = t.grid_offset();
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_terrain_add(grid_offset, TERRAIN_BUILDING);
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_property_set_multi_tile_xy(grid_offset, 0, 0, true);
            map_monuments_set_progress(t, 0);
            if (paint_walkway && walk_img > 0) {
                map_image_set(grid_offset, walk_img);
            }
        }
    }
}

void clear_causeway_tiles(int building_id, const pyramid_causeway_probe &probe) {
    if (probe.length <= 0) {
        return;
    }
    const vec2i step = k_causeway_dir[probe.dir & 3];
    const vec2i perp = k_causeway_perp[probe.dir & 3];
    tile2i origin = probe.origin;
    int xmin = origin.x(), xmax = origin.x();
    int ymin = origin.y(), ymax = origin.y();
    bool any = false;
    for (int i = 0; i < probe.length; ++i) {
        for (int w = 0; w < k_causeway_width; ++w) {
            tile2i t = origin.shifted(step.x * i + perp.x * w, step.y * i + perp.y * w);
            if (!map_grid_is_inside(t, 1)) {
                continue;
            }
            const int grid_offset = t.grid_offset();
            const int owner = map_building_at(grid_offset);
            bool wipe = false;
            if (owner > 0) {
                if (building *ob = building_get(owner)) {
                    if (building_type_is_pyramid_complex_annex(ob->type)) {
                        if (ob->state != BUILDING_STATE_DELETED_BY_GAME) {
                            ob->state = BUILDING_STATE_DELETED_BY_GAME;
                        }
                        wipe = true;
                    }
                }
            }
            // Only wipe tiles still owned by this complex (avoid clearing
            // unrelated buildings if runtime length/dir were stale).
            if (!wipe && building_id > 0 && owner != building_id) {
                continue;
            }
            map_building_tile_clear_at(grid_offset, /*building_type*/ 0);
            xmin = any ? std::min(xmin, t.x()) : t.x();
            xmax = any ? std::max(xmax, t.x()) : t.x();
            ymin = any ? std::min(ymin, t.y()) : t.y();
            ymax = any ? std::max(ymax, t.y()) : t.y();
            any = true;
        }
    }
    if (any) {
        map_tiles_update_region_empty_land(true, tile2i(xmin - 1, ymin - 1), tile2i(xmax + 1, ymax + 1));
    }
}

bool slot_owned_by_complex(tile2i t, int complex_id) {
    for (int dy = 0; dy < 2; ++dy) {
        for (int dx = 0; dx < 2; ++dx) {
            if (map_building_at(t.shifted(dx, dy).grid_offset()) != complex_id) {
                return false;
            }
        }
    }
    return true;
}

bool place_next_complex_annex(int complex_id, const pyramid_causeway_probe &probe) {
    if (!probe.ok || probe.length < 2 || complex_id <= 0) {
        return false;
    }
    building *cx = building_get(complex_id);
    if (!cx) {
        return false;
    }

    const vec2i step = k_causeway_dir[probe.dir & 3];
    const int slots = std::max(1, probe.length / 2);
    tile2i origin = probe.origin;
    for (int s = 0; s < slots; ++s) {
        tile2i t = origin.shifted(step.x * (s * 2), step.y * (s * 2));
        if (!map_grid_is_inside(t, 2) || !slot_owned_by_complex(t, complex_id)) {
            continue;
        }

        e_building_type bt = BUILDING_CAUSEWAY;
        if (s == 0) {
            bt = BUILDING_MORTUARY_TEMPLE;
        }
        if (s == slots - 1) {
            bt = BUILDING_VALLEY_TEMPLE;
        }

        for (int dy = 0; dy < 2; ++dy) {
            for (int dx = 0; dx < 2; ++dx) {
                map_building_tile_clear_at(t.shifted(dx, dy).grid_offset(), 0);
            }
        }

        building *b = building_create(bt, t, 0);
        if (!b) {
            return false;
        }
        game_undo_add_building(b);
        int img = annex_building_image(cx->type, bt);
        if (img <= 0) {
            img = building_static_params::get(bt).base_img();
        }
        if (img <= 0) {
            img = complex_walkway_image(cx->type);
        }
        map_building_tiles_add(b->id, t, 2, img, TERRAIN_BUILDING);
        return true;
    }
    return false;
}

void place_all_complex_annex(int complex_id, const pyramid_causeway_probe &probe) {
    if (!probe.ok || complex_id <= 0) {
        return;
    }
    claim_causeway_tiles(complex_id, probe);
    while (place_next_complex_annex(complex_id, probe)) {
    }
}

bool complex_annex_has_free_slot(int complex_id, const pyramid_causeway_probe &probe) {
    if (!probe.ok || probe.length < 2 || complex_id <= 0) {
        return false;
    }
    const vec2i step = k_causeway_dir[probe.dir & 3];
    const int slots = std::max(1, probe.length / 2);
    tile2i origin = probe.origin;
    for (int s = 0; s < slots; ++s) {
        tile2i t = origin.shifted(step.x * (s * 2), step.y * (s * 2));
        if (map_grid_is_inside(t, 2) && slot_owned_by_complex(t, complex_id)) {
            return true;
        }
    }
    return false;
}

} // namespace

bool building_type_is_pyramid_complex_annex(e_building_type t) {
    return t == BUILDING_MORTUARY_TEMPLE
        || t == BUILDING_CAUSEWAY
        || t == BUILDING_VALLEY_TEMPLE;
}

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_stepped_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_stepped_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_stepped_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_stepped_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_stepped_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_stepped_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_stepped_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_stepped_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_stepped_pyramid_wall)

static_assert(std::is_same<building_stepped_pyramid_complex::preview,
    building_stepped_pyramid::preview_renderer>::value,
    "complex must inherit stepped pyramid planner preview (causeway gate)");
static_assert(std::is_same<building_grand_stepped_pyramid_complex::preview,
    building_stepped_pyramid::preview_renderer>::value,
    "grand stepped complex must inherit stepped pyramid planner preview");
static_assert(std::is_same<building_grand_pyramid_complex::preview,
    building_stepped_pyramid::preview_renderer>::value,
    "grand complex must inherit stepped pyramid planner preview");
static_assert(std::is_same<building_mudbrick_pyramid_complex::preview,
    building_stepped_pyramid::preview_renderer>::value,
    "mudbrick complex must inherit stepped pyramid planner preview");
static_assert(std::is_same<building_grand_mudbrick_pyramid_complex::preview,
    building_stepped_pyramid::preview_renderer>::value,
    "grand mudbrick complex must inherit stepped pyramid planner preview");
static_assert(std::is_same<building_pyramid_complex::preview,
    building_stepped_pyramid::preview_renderer>::value,
    "true complex must inherit stepped pyramid planner preview");

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_stepped_pyramid_complex)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_grand_stepped_pyramid_complex)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_bent_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_bent_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_bent_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_bent_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_bent_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_bent_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_mudbrick_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_mudbrick_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_small_mudbrick_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_mudbrick_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_mudbrick_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_mudbrick_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_mudbrick_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_mudbrick_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_mudbrick_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mudbrick_pyramid_complex)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_grand_mudbrick_pyramid_complex)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mortuary_temple)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_pyramid_causeway)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_valley_temple)

void building_mortuary_temple::on_place_update_tiles(int, int) {
    refresh_annex_orientation_tiles(base);
}

void building_mortuary_temple::update_map_orientation(int /*map_orientation*/) {
    refresh_annex_orientation_tiles(base);
}

void building_pyramid_causeway::on_place_update_tiles(int, int) {
    refresh_annex_orientation_tiles(base);
}

void building_pyramid_causeway::update_map_orientation(int /*map_orientation*/) {
    refresh_annex_orientation_tiles(base);
}

void building_valley_temple::on_place_update_tiles(int, int) {
    refresh_annex_orientation_tiles(base);
}

void building_valley_temple::update_map_orientation(int /*map_orientation*/) {
    refresh_annex_orientation_tiles(base);
}

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_medium_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_pyramid)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_pyramid_corner)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_large_pyramid_wall)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_pyramid_complex)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_grand_pyramid_complex)

struct pyramid_part {
    e_building_type type;
    tile2i offset;
    building *b;
};

struct monument_small_stepped_pyramid : public monument {
    monument_small_stepped_pyramid() : monument{ BUILDING_SMALL_STEPPED_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600} });
        phases.push_back({ 7, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 8, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 9, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({10, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({11, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({12, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({13, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({14, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({15, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({16, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({17, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({18, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({19, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({20, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({21, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({22, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({23, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({24, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_small_stepped_pyramid;

struct monument_medium_stepped_pyramid : public monument {
    monument_medium_stepped_pyramid() : monument{ BUILDING_MEDIUM_STEPPED_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600} });
        phases.push_back({ 7, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 8, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 9, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 10, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 11, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 12, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 13, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 14, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 15, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 16, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 17, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 18, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 19, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 20, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 21, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 22, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 23, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 24, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 25, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 26, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 27, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 28, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 29, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 30, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 31, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        phases.push_back({ 32, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_medium_stepped_pyramid;

// Large stepped pyramid (20×20). Schedule: foundation 0–6, then brick courses → finish@36.
// Also used by the stepped pyramid complex until causeway/temples change costs.
// Top-down limestone casing polish is NOT stepped — true/mudbrick only.
struct monument_large_stepped_pyramid : public monument {
    monument_large_stepped_pyramid() : monument{ BUILDING_LARGE_STEPPED_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600} });
        // 20×20 = 5 layers × 6 brick courses after phase 6 → finish at 36
        // (medium still finishes at 32; shared height draw handles both).
        for (int p = 7; p <= 35; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        }
        phases.push_back({ 36, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_large_stepped_pyramid;

// Bent pyramids share the stepped construction/rendering pipeline, so their phase
// schedules mirror the stepped ones (the phase count drives the layer rendering:
// small = 24 phases over an 8x8 footprint, medium = 32 phases over 12x12).
struct monument_small_bent_pyramid : public monument {
    monument_small_bent_pyramid() : monument{ BUILDING_SMALL_BENT_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600} });
        for (int p = 7; p <= 23; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        }
        phases.push_back({ 24, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_small_bent_pyramid;

struct monument_medium_bent_pyramid : public monument {
    monument_medium_bent_pyramid() : monument{ BUILDING_MEDIUM_BENT_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600} });
        for (int p = 7; p <= 31; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800} });
        }
        phases.push_back({ 32, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_medium_bent_pyramid;


struct monument_small_pyramid : public monument {
    monument_small_pyramid() : monument{ BUILDING_SMALL_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800}, {RESOURCE_LIMESTONE, 1200} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000}, {RESOURCE_LIMESTONE, 1000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200}, {RESOURCE_LIMESTONE, 800} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400}, {RESOURCE_LIMESTONE, 600} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600}, {RESOURCE_LIMESTONE, 400} });
        for (int p = 7; p <= 23; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800}, {RESOURCE_LIMESTONE, 200} });
        }
        // Polish: no new limestone; stonemasons via need_stonemason().
        // Count = init_tiles/4 layers (8→2). Phases 24–25 collide with stepped
        // hight_impl large band — building_small_pyramid draws completed height instead.
        constexpr int k_polish_phases = 8 / 4; // == num layers
        for (int i = 0; i < k_polish_phases; ++i) {
            phases.push_back({ (uint8_t)(24 + i), monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        }
        phases.push_back({ 26, monument_phase_resource{RESOURCE_NONE, 0} }); // last id; finish = set_phase(27)
    }
} g_monument_small_pyramid;

// Mudbrick small: same phase shape as true small, RESOURCE_STONE → RESOURCE_BRICKS.
// TODO(orig-data): Heaven totals S = 4800 bricks / 192 limestone (schedule overshoots).
struct monument_small_mudbrick_pyramid : public monument {
    monument_small_mudbrick_pyramid() : monument{ BUILDING_SMALL_MUDBRICK_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_BRICKS, 4800}, {RESOURCE_LIMESTONE, 1200} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_BRICKS, 4000}, {RESOURCE_LIMESTONE, 1000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_BRICKS, 3200}, {RESOURCE_LIMESTONE, 800} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_BRICKS, 2400}, {RESOURCE_LIMESTONE, 600} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_BRICKS, 1600}, {RESOURCE_LIMESTONE, 400} });
        for (int p = 7; p <= 23; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_BRICKS, 800}, {RESOURCE_LIMESTONE, 200} });
        }
        constexpr int k_polish_phases = 8 / 4;
        for (int i = 0; i < k_polish_phases; ++i) {
            phases.push_back({ (uint8_t)(24 + i), monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        }
        phases.push_back({ 26, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_small_mudbrick_pyramid;

// True medium (12×12): height mirrors medium stepped (courses through 31), then
// polish top-down (layers = 12/4 = 3) without new limestone; terminal 35.
struct monument_medium_pyramid : public monument {
    monument_medium_pyramid() : monument{ BUILDING_MEDIUM_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800}, {RESOURCE_LIMESTONE, 1200} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000}, {RESOURCE_LIMESTONE, 1000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200}, {RESOURCE_LIMESTONE, 800} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400}, {RESOURCE_LIMESTONE, 600} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600}, {RESOURCE_LIMESTONE, 400} });
        for (int p = 7; p <= 31; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800}, {RESOURCE_LIMESTONE, 200} });
        }
        // Polish after height — phase numbers stay outside small's 24–25 band and
        // after medium height courses; draw uses completed ornaments for phase >= 32.
        constexpr int k_polish_phases = 12 / 4;
        for (int i = 0; i < k_polish_phases; ++i) {
            phases.push_back({ (uint8_t)(32 + i), monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        }
        phases.push_back({ 35, monument_phase_resource{RESOURCE_NONE, 0} }); // finish = set_phase(36)
    }
} g_monument_medium_pyramid;

// Mudbrick medium: true-medium shape, STONE→BRICKS.
// TODO(orig-data): Heaven totals M = 24000 bricks / 432 limestone.
struct monument_medium_mudbrick_pyramid : public monument {
    monument_medium_mudbrick_pyramid() : monument{ BUILDING_MEDIUM_MUDBRICK_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_BRICKS, 4800}, {RESOURCE_LIMESTONE, 1200} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_BRICKS, 4000}, {RESOURCE_LIMESTONE, 1000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_BRICKS, 3200}, {RESOURCE_LIMESTONE, 800} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_BRICKS, 2400}, {RESOURCE_LIMESTONE, 600} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_BRICKS, 1600}, {RESOURCE_LIMESTONE, 400} });
        for (int p = 7; p <= 31; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_BRICKS, 800}, {RESOURCE_LIMESTONE, 200} });
        }
        constexpr int k_polish_phases = 12 / 4;
        for (int i = 0; i < k_polish_phases; ++i) {
            phases.push_back({ (uint8_t)(32 + i), monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        }
        phases.push_back({ 35, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_medium_mudbrick_pyramid;

// Mudbrick large (16×16): height through 35, polish 36–39; terminal 40.
// TODO(orig-data): Heaven totals L = 67200 bricks / 768 limestone.
struct monument_large_mudbrick_pyramid : public monument {
    monument_large_mudbrick_pyramid() : monument{ BUILDING_LARGE_MUDBRICK_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_BRICKS, 4800}, {RESOURCE_LIMESTONE, 1200} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_BRICKS, 4000}, {RESOURCE_LIMESTONE, 1000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_BRICKS, 3200}, {RESOURCE_LIMESTONE, 800} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_BRICKS, 2400}, {RESOURCE_LIMESTONE, 600} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_BRICKS, 1600}, {RESOURCE_LIMESTONE, 400} });
        for (int p = 7; p <= 35; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_BRICKS, 800}, {RESOURCE_LIMESTONE, 200} });
        }
        constexpr int k_polish_phases = 16 / 4;
        for (int i = 0; i < k_polish_phases; ++i) {
            phases.push_back({ (uint8_t)(36 + i), monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        }
        phases.push_back({ 40, monument_phase_resource{RESOURCE_NONE, 0} }); // finish = set_phase(41)
    }
} g_monument_large_mudbrick_pyramid;

// Mudbrick complex/grand on-land = 20×20. Same band as true large, STONE→BRICKS.
// TODO(orig-data): Heaven complex = 144400 bricks / 1200 limestone; grand 24×24 later.
struct monument_mudbrick_pyramid_20 : public monument {
    monument_mudbrick_pyramid_20() : monument{ BUILDING_MUDBRICK_PYRAMID_COMPLEX } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_BRICKS, 4800}, {RESOURCE_LIMESTONE, 1200} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_BRICKS, 4000}, {RESOURCE_LIMESTONE, 1000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_BRICKS, 3200}, {RESOURCE_LIMESTONE, 800} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_BRICKS, 2400}, {RESOURCE_LIMESTONE, 600} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_BRICKS, 1600}, {RESOURCE_LIMESTONE, 400} });
        for (int p = 7; p <= 35; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_BRICKS, 800}, {RESOURCE_LIMESTONE, 200} });
        }
        constexpr int k_polish_phases = 20 / 4;
        for (int i = 0; i < k_polish_phases; ++i) {
            phases.push_back({ (uint8_t)(36 + i), monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        }
        phases.push_back({ 41, monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_mudbrick_pyramid_20;

// True large (20×20): height mirrors large stepped (courses through 35), then
// polish top-down (layers = 20/4 = 5); terminal 41.
struct monument_large_pyramid : public monument {
    monument_large_pyramid() : monument{ BUILDING_LARGE_PYRAMID } {
        phases.push_back({ 0, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 1, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ 2, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_STONE, 4800}, {RESOURCE_LIMESTONE, 1200} });
        phases.push_back({ 3, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 2000}, {RESOURCE_STONE, 4000}, {RESOURCE_LIMESTONE, 1000} });
        phases.push_back({ 4, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1600}, {RESOURCE_STONE, 3200}, {RESOURCE_LIMESTONE, 800} });
        phases.push_back({ 5, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 1200}, {RESOURCE_STONE, 2400}, {RESOURCE_LIMESTONE, 600} });
        phases.push_back({ 6, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 800}, {RESOURCE_STONE, 1600}, {RESOURCE_LIMESTONE, 400} });
        for (int p = 7; p <= 35; ++p) {
            phases.push_back({ (uint8_t)p, monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_TIMBER, 400}, {RESOURCE_STONE, 800}, {RESOURCE_LIMESTONE, 200} });
        }
        constexpr int k_polish_phases = 20 / 4;
        for (int i = 0; i < k_polish_phases; ++i) {
            phases.push_back({ (uint8_t)(36 + i), monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        }
        phases.push_back({ 41, monument_phase_resource{RESOURCE_NONE, 0} }); // finish = set_phase(42)
    }
} g_monument_large_pyramid;

template<typename T>
const building_pyramid::base_params &pyramid_base_params(const building_static_params &params) {
    using static_params = typename T::static_params;
    const auto &bparams = (const static_params &)params;
    return (const building_pyramid::base_params &)bparams;
}

tile2i building_pyramid::footprint_nw() const {
    // Orientation can put a corner/wall at the linked-list head — geometric NW is
    // the min (x,y) across the multipart chain, not main()->tile().
    int min_x = tile().x();
    int min_y = tile().y();
    for (const building *part = &main()->base; part; part = part->has_next() ? part->next() : nullptr) {
        min_x = std::min(min_x, part->tile.x());
        min_y = std::min(min_y, part->tile.y());
    }
    return tile2i(min_x, min_y);
}

bool building_pyramid::tile_in_monument_footprint(tile2i tile) const {
    const tile2i nw = footprint_nw();
    const vec2i sz = footprint_params().init_tiles;
    return tile.x() >= nw.x() && tile.y() >= nw.y()
        && tile.x() < nw.x() + sz.x && tile.y() < nw.y() + sz.y;
}

const building_pyramid::base_params &building_pyramid::footprint_params() const {
    e_building_type best_type = type();
    int best_area = 0;
    for (const building *part = &main()->base; part; part = part->has_next() ? part->next() : nullptr) {
        if (building_type_is_pyramid_complex(part->type)) {
            return params_for_type(part->type);
        }
        // Prefer largest init_tiles in the chain (COMPLEX filler beats LARGE wall).
        const vec2i tiles = params_for_type(part->type).init_tiles;
        const int area = tiles.x * tiles.y;
        if (area > best_area) {
            best_area = area;
            best_type = part->type;
        }
    }
    return params_for_type(best_type);
}

tile2i building_pyramid::center_point() const {
    const auto &itiles = footprint_params().init_tiles;
    tile2i tnw = footprint_nw();
    tile2i tend = tnw.shifted(itiles.x, itiles.y);
    tile2i ctile = tnw.add(tend).div(2);
    building* b = building_at(ctile);
    // Mid-footprint must be a pyramid part; fall back to NW tile if the map
    // was corrupted / mid-demolition so sleds don't null-deref.
    return b ? b->tile : tnw;
}

grid_area building_pyramid::get_area() const {
    // Sleds deliver when the load is inside this rect. Part buildings are 2×2;
    // using size()-1 made the area miss center_point() and drop cargo undelivered.
    const auto &itiles = footprint_params().init_tiles;
    tile2i begin = footprint_nw();
    tile2i end = begin.shifted(itiles.x - 1, itiles.y - 1);
    return { begin, end };
}

void building_pyramid::sync_visuals() {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_NONE) {
        return;
    }
    if (!is_main() || is_finished()) {
        return;
    }
    building *part = &base;
    while (part) {
        grid_tiles tiles = map_grid_get_tiles(part, 0);
        map_grid_area_foreach(tiles, [](tile2i t) { map_monuments_set_progress(t, 200); });
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_stepped_pyramid::sync_footprint_layers(int done_blocks, int total_blocks) {
    if (!is_main() || total_blocks <= 0) {
        return;
    }
    const int nlayers = footprint_params().init_tiles.x / 4;
    if (nlayers <= 1) {
        return;
    }
    const int blocks_per_ring = std::max(1, total_blocks / nlayers);
    // Ring currently under construction (0 = base only).
    const int ring = std::min(nlayers - 1, done_blocks / blocks_per_ring);

    int max_applied = 0;
    for (building *p = &base; p; p = p->has_next() ? p->next() : nullptr) {
        if (auto *m = p->dcast_monument()) {
            max_applied = std::max(max_applied, (int)m->runtime_data().layer);
        }
    }
    for (int L = max_applied + 1; L <= ring; L++) {
        auto area = get_layer_area(L);
        if (area.size.x > 0 && area.size.y > 0) {
            change_parts_types_in_layer(area.begin, area.size, (uint8_t)L);
        }
    }
}

void building_stepped_pyramid::sync_visuals() {
    building_pyramid::sync_visuals();
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_NONE || !is_main() || is_finished()) {
        return;
    }
    auto *ms = pyramid_main_state_get(id());
    if (!ms || ms->style == PYRAMID_STYLE_NONE || ms->style == PYRAMID_STYLE_MASTABA) {
        return;
    }
    // OG bent draws per-part via layout kind + bent_pixel_heights — remake rings
    // lift the tip twice and hollow the polish base.
    if (ms->style == PYRAMID_STYLE_BENT || pyramid_params().pyramide_type == PYRAMID_STYLE_BENT) {
        return;
    }
    const int total = g_monument_pyramid_engine.block_total(&base);
    const int done = total - (int)ms->remaining_blocks;
    sync_footprint_layers(done, total);
}

bool building_pyramid::run_block_day() {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_NONE) {
        return false;
    }
    if (!is_main() || phase() < 2) {
        return false;
    }

    auto *ms = pyramid_main_state_get(id());
    if (!ms || ms->style == PYRAMID_STYLE_NONE || ms->style == PYRAMID_STYLE_MASTABA) {
        pyramid_engine_init(&base);
        ms = pyramid_main_state_get(id());
    }
    if (!ms || ms->style == PYRAMID_STYLE_NONE || ms->style == PYRAMID_STYLE_MASTABA) {
        return false;
    }

    // OG: when masons have no frontier block work they build the next free
    // complex annex tile. Remake: advance one annex slot while block phase runs.
    if (building_type_is_pyramid_complex(type()) && ms->block_phase_active) {
        const auto &d = runtime_data();
        if (d.causeway_length >= 2) {
            const pyramid_causeway_probe probe = causeway_probe_from_runtime(
                tile(), pyramid_params().init_tiles, d.causeway_length, d.causeway_dir);
            if (complex_annex_has_free_slot(id(), probe)) {
                place_next_complex_annex(id(), probe);
            }
        }
    }

    if (ms->remaining_blocks == 0) {
        finish_block_construction();
        return true;
    }
    if (!ms->block_phase_active) {
        pyramid_engine_start_block_phase(&base);
    }
    return true;
}

void building_pyramid::finish_block_construction() {
    auto *ms = pyramid_main_state_get(id());
    if (!ms || !ms->force_show_ramps) {
        pyramid_engine_clear_all_ramps(&base);
    }
    building_impl *part = this;
    while (part) {
        if (auto *m = part->dcast_monument()) {
            m->runtime_data().phase = MONUMENT_FINISHED;
        }
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_stepped_pyramid::finish_block_construction() {
    if (!is_main()) {
        return;
    }

    // Rings should already be raised during sync_visuals; ensure full stack.
    // Bent stays flat in remake coords — OG part draw supplies bent_pixel_heights.
    auto *ms = pyramid_main_state_get(id());
    const e_pyramid_style finish_style = ms ? ms->style : pyramid_params().pyramide_type;
    const int total = ms ? g_monument_pyramid_engine.block_total(&base) : 0;
    if (total > 0 && finish_style != PYRAMID_STYLE_BENT) {
        sync_footprint_layers(total, total);
    }

    const int empty_img = building_static_params::get(type()).first_img("empty_land");
    building *part = &base;
    while (part) {
        grid_tiles tiles = map_grid_get_tiles(part, 0);
        map_grid_area_foreach(tiles, [](tile2i t) { map_monuments_set_progress(t, 200); });
        if (auto *m = part->dcast_monument()) {
            int img = 0;
            // OG: map_building_tiles_add(casing face) — footprint draws the base;
            // empty_land leaves a grey well under raised bent half-layers.
            if (finish_style == PYRAMID_STYLE_BENT) {
                if (auto* ps = pyramid_part_state_get(part->id)) {
                    img = bent_og_part_image(*part, *ps, true);
                }
            }
            if (img <= 0) {
                img = empty_img > 0 ? empty_img : m->building_image_get();
            }
            map_building_tiles_add(part->id, part->tile, part->size, img,
                                   TERRAIN_BUILDING | TERRAIN_CANAL);
        }
        part = part->has_next() ? part->next() : nullptr;
    }

    // OG completion waits until complex free tiles are gone — fill remaining annex.
    if (building_type_is_pyramid_complex(type())) {
        const auto &d = runtime_data();
        if (d.causeway_length >= 2) {
            const pyramid_causeway_probe probe = causeway_probe_from_runtime(
                tile(), pyramid_params().init_tiles, d.causeway_length, d.causeway_dir);
            place_all_complex_annex(id(), probe);
        }
    }

    building_pyramid::finish_block_construction();
}

bool building_pyramid::need_bricklayers() {
    // OG: bricklayers only on mudbrick main-material stage; true uses stonemasons.
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_MUDBRICK) {
        if (is_finished() || !is_main() || phase() < 2) {
            return false;
        }
        auto *ms = pyramid_main_state_get(id());
        if (ms && ms->style == PYRAMID_STYLE_MUDBRICK && ms->block_phase_active) {
            return ms->remaining_blocks > 0 && need_workers();
        }
    }
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_TRUE || pyramid_params().pyramide_type == PYRAMID_STYLE_STEPPED
        || pyramid_params().pyramide_type == PYRAMID_STYLE_BENT) {
        return false;
    }
    return building_monument::need_bricklayers();
}

bool building_pyramid::need_stonemason() {
    if (pyramid_params().pyramide_type != PYRAMID_STYLE_NONE) {
        if (is_finished() || !is_main()) {
            return false;
        }

        if (g_monument_pyramid_engine.block_phase_active(&base)) {
            return need_workers();
        }
        const int p = phase();
        if (p < 2 || p >= phases() - 1) {
            return false;
        }
        return need_workers();
    }
    return building_monument::need_stonemason();
}

bool building_pyramid::need_carpenter() {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_NONE) {
        return building_monument::need_carpenter();
    }
    if (is_finished() || !is_main()) {
        return false;
    }
    if (!pyramid_engine_has_ramp_work(&base)) {
        return false;
    }
    if (!has_free_worker_slot()) {
        return false;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        figure *f = wid > 0 ? figure_get(wid) : nullptr;
        if (f && f->type == FIGURE_CARPENTER) {
            return false;
        }
    }
    return true;
}

int building_pyramid::try_assign_bricklayer(figure_id fid) {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_MUDBRICK) {
        return pyramid_engine_try_assign_bricklayer(&base, fid);
    }
    return 0;
}

void building_pyramid::place_bricklayer_block(figure_id fid) {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_MUDBRICK) {
        pyramid_engine_place_block(id(), fid);
    }
}

bool building_pyramid::get_route_citizen_land_type(int grid_offset, int &land_result) const {
    if (is_finished()) {
        land_result = CITIZEN_N1_BLOCKED;
        return true;
    }

    if (phase() > 6) {
        const auto &itiles = footprint_params().init_tiles;
        tile2i maint = footprint_nw();
        tile2i end = maint.shifted(itiles.x, itiles.y);
        tile2i tile(grid_offset);
        land_result = (tile.x() == maint.x() || tile.y() == maint.y() || tile.x() == end.x()) ? CITIZEN_N1_BLOCKED : CITIZEN_2_PASSABLE_TERRAIN;
        return true;
    }

    land_result = CITIZEN_2_PASSABLE_TERRAIN;
    return true;
}

bool building_pyramid::target_route_tile_blocked(int grid_offset) const {
    return is_finished();
}

const building_pyramid::base_params &building_pyramid::params_for_type(e_building_type type) {
    const auto &params = building_static_params::get(type);

    switch (params.type) {
    case BUILDING_SMALL_STEPPED_PYRAMID:
    case BUILDING_SMALL_STEPPED_PYRAMID_CORNER:
    case BUILDING_SMALL_STEPPED_PYRAMID_CONE:
    case BUILDING_SMALL_STEPPED_PYRAMID_WALL:
        return pyramid_base_params<building_small_stepped_pyramid>(params);

    case BUILDING_MEDIUM_STEPPED_PYRAMID:
    case BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER:
    case BUILDING_MEDIUM_STEPPED_PYRAMID_CONE:
    case BUILDING_MEDIUM_STEPPED_PYRAMID_WALL:
        return pyramid_base_params<building_medium_stepped_pyramid>(params);

    case BUILDING_LARGE_STEPPED_PYRAMID:
    case BUILDING_LARGE_STEPPED_PYRAMID_CORNER:
    case BUILDING_LARGE_STEPPED_PYRAMID_CONE:
    case BUILDING_LARGE_STEPPED_PYRAMID_WALL:
        return pyramid_base_params<building_large_stepped_pyramid>(params);

    case BUILDING_STEPPED_PYRAMID_COMPLEX:
        return pyramid_base_params<building_stepped_pyramid_complex>(params);
    case BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX:
        return pyramid_base_params<building_grand_stepped_pyramid_complex>(params);

    case BUILDING_SMALL_BENT_PYRAMID:
    case BUILDING_SMALL_BENT_PYRAMID_CORNER:
    case BUILDING_SMALL_BENT_PYRAMID_CONE:
    case BUILDING_SMALL_BENT_PYRAMID_WALL:
        return pyramid_base_params<building_small_bent_pyramid>(params);

    case BUILDING_MEDIUM_BENT_PYRAMID:
    case BUILDING_MEDIUM_BENT_PYRAMID_CORNER:
    case BUILDING_MEDIUM_BENT_PYRAMID_CONE:
    case BUILDING_MEDIUM_BENT_PYRAMID_WALL:
        return pyramid_base_params<building_medium_bent_pyramid>(params);

    case BUILDING_SMALL_PYRAMID:
    case BUILDING_SMALL_PYRAMID_CORNER:
    case BUILDING_SMALL_PYRAMID_CONE:
    case BUILDING_SMALL_PYRAMID_WALL:
        return pyramid_base_params<building_small_pyramid>(params);

    case BUILDING_SMALL_MUDBRICK_PYRAMID:
    case BUILDING_SMALL_MUDBRICK_PYRAMID_CORNER:
    case BUILDING_SMALL_MUDBRICK_PYRAMID_CONE:
    case BUILDING_SMALL_MUDBRICK_PYRAMID_WALL:
        return pyramid_base_params<building_small_mudbrick_pyramid>(params);

    case BUILDING_MEDIUM_MUDBRICK_PYRAMID:
    case BUILDING_MEDIUM_MUDBRICK_PYRAMID_CORNER:
    case BUILDING_MEDIUM_MUDBRICK_PYRAMID_CONE:
    case BUILDING_MEDIUM_MUDBRICK_PYRAMID_WALL:
        return pyramid_base_params<building_medium_mudbrick_pyramid>(params);

    case BUILDING_LARGE_MUDBRICK_PYRAMID:
    case BUILDING_LARGE_MUDBRICK_PYRAMID_CORNER:
    case BUILDING_LARGE_MUDBRICK_PYRAMID_CONE:
    case BUILDING_LARGE_MUDBRICK_PYRAMID_WALL:
        return pyramid_base_params<building_large_mudbrick_pyramid>(params);

    case BUILDING_MUDBRICK_PYRAMID_COMPLEX:
        return pyramid_base_params<building_mudbrick_pyramid_complex>(params);
    case BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX:
        return pyramid_base_params<building_grand_mudbrick_pyramid_complex>(params);

    case BUILDING_MEDIUM_PYRAMID:
    case BUILDING_MEDIUM_PYRAMID_CORNER:
    case BUILDING_MEDIUM_PYRAMID_CONE:
    case BUILDING_MEDIUM_PYRAMID_WALL:
        return pyramid_base_params<building_medium_pyramid>(params);

    case BUILDING_LARGE_PYRAMID:
    case BUILDING_LARGE_PYRAMID_CORNER:
    case BUILDING_LARGE_PYRAMID_CONE:
    case BUILDING_LARGE_PYRAMID_WALL:
        return pyramid_base_params<building_large_pyramid>(params);

    case BUILDING_PYRAMID_COMPLEX:
        return pyramid_base_params<building_pyramid_complex>(params);

    case BUILDING_GRAND_PYRAMID_COMPLEX:
        return pyramid_base_params<building_grand_pyramid_complex>(params);
    }

    static building_pyramid::base_params dummy;
    return dummy;
}

static const building_pyramid::base_params &get_pyramid_params(e_building_type type) {
    return building_pyramid::params_for_type(type);
}

void building_stepped_pyramid::set_tile_progress(tile2i tile, int v) {
    building_pyramid::set_tile_progress(tile, v);
    if (phase() == 2) {
        map_terrain_add(tile, v > 0 ? TERRAIN_CANAL : TERRAIN_NONE);
        return;
    }

    if (phase() >= 3 && phase() < 7) {
        map_terrain_add(tile, TERRAIN_CANAL);
        return;
    }
}

void building_stepped_pyramid::preview_renderer::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &base_params = get_pyramid_params(planer.build_type);

    const vec2i init_tiles = base_params.init_tiles;

    switch (g_camera.orientation / 2) {
    case 0: planer.init_tiles(init_tiles.y, init_tiles.x); break;
    case 1: planer.init_tiles(init_tiles.x, init_tiles.y); break;
    case 2: planer.init_tiles(init_tiles.y, init_tiles.x); break;
    case 3: planer.init_tiles(init_tiles.x, init_tiles.y); break;
    }
}

void building_stepped_pyramid::preview_renderer::ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto &base_params = get_pyramid_params(planer.build_type);

    int image_id = params.base_img();
    const vec2i size_b = base_params.init_tiles;
    tile2i nw = pyramid_place_nw_from_cursor(end, size_b);

    auto get_image = [image_id] (tile2i tile, tile2i start, vec2i size) {
        if (tile == start) {
            return image_id;
        }

        if (tile == start.shifted(size.x - 1, 0)) {
            return image_id - 2;
        }

        if (tile == start.shifted(size.x - 1, size.y - 1)) {
            return image_id - 4;
        }

        if (tile == start.shifted(0, size.y - 1)) {
            return image_id - 6;
        }

        if (tile.y() == start.y()) { return image_id - 1; }
        if (tile.y() == start.y() + size.y - 1) { return image_id - 5; }
        if (tile.x() == start.x()) { return image_id - 7; }
        if (tile.x() == start.x() + size.x - 1) { return image_id - 3; }

        return (image_id + 5 + (tile.x() + tile.y()) % 7);
    };

    // Screen pixel of map-NW (cursor `end` may be a different corner under rotation).
    const vec2i pixel_nw = g_camera.lookup_tile_to_pixel(nw);

    for (int i = 0; i < size_b.x; ++i) {
        for (int j = 0; j < size_b.y; ++j) {
            vec2i p = pixel_nw + (vec2i(-30, 15) * i) + (vec2i(30, 15) * j);
            int tile_img = get_image(nw.shifted(i, j), nw, size_b);

            auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_full);
            command.image_id = tile_img;
            command.pixel = p;
            command.mask = COLOR_MASK_GREEN;
        }
    }

    if (building_type_is_pyramid_complex(planer.build_type)) {
        const bool east_only = building_type_is_grand_pyramid_complex(planer.build_type);
        pyramid_causeway_probe probe = map_pyramid_complex_find_causeway(nw, size_b, east_only);
        const bool causeway_ok = probe.ok;
        if (!causeway_ok) {
            probe.dir = 1;
            probe.length = 8;
            probe.origin = causeway_origin_on_face(nw, size_b, probe.dir, k_causeway_width);
        }
        draw_causeway_ghost(planer, ctx, probe, !causeway_ok || planer.can_be_placed() != CAN_PLACE);
    }
}

int building_stepped_pyramid::preview_renderer::can_place(build_planner &p, tile2i /*tile*/, tile2i end, int state) const {
    if (state != CAN_PLACE) {
        return state;
    }
    if (!building_type_is_pyramid_complex(p.build_type)) {
        return state;
    }
    const auto &base_params = get_pyramid_params(p.build_type);
    tile2i nw = pyramid_place_nw_from_cursor(end, base_params.init_tiles);
    const bool east_only = building_type_is_grand_pyramid_complex(p.build_type);
    const pyramid_causeway_probe probe = map_pyramid_complex_find_causeway(nw, base_params.init_tiles, east_only);
    if (!probe.ok) {
        p.set_warning("#causeway_needs_water");
        return CAN_NOT_PLACE;
    }
    return state;
}

int building_stepped_pyramid::preview_renderer::finalize_check(build_planner &p, tile2i tile, tile2i end, int state) const {
    state = building_planer_renderer::finalize_check(p, tile, end, state);
    return can_place(p, tile, end, state);
}

int building_stepped_pyramid::preview_renderer::construction_place(build_planner &planer, tile2i /*start*/, tile2i end, int orientation, int variant) const {
    const auto &base_params = get_pyramid_params(planer.build_type);
    const tile2i place = pyramid_place_nw_from_cursor(end, base_params.init_tiles);

    planer.last_created_building = nullptr;
    building *b = building_create(planer.build_type, place, orientation);
    game_undo_add_building(b);
    if (!b || b->id <= 0) {
        return 0;
    }

    add_building(b, orientation, variant);
    planer.last_created_building = b;
    return 1;
}

void map_pyramid_tiles_add(int building_id, tile2i tile, int size, int image_id, int terrain) {
    int x_leftmost, y_leftmost;
    switch (g_camera.orientation) {
    case DIR_0_TOP_RIGHT: x_leftmost = 0; y_leftmost = 1; break;
    case DIR_2_BOTTOM_RIGHT: x_leftmost = y_leftmost = 0; break;
    case DIR_4_BOTTOM_LEFT: x_leftmost = 1; y_leftmost = 0; break;
    case DIR_6_TOP_LEFT: x_leftmost = y_leftmost = 1; break;
    default:
        return;
    }

    if (!map_grid_is_inside(tile, size)) {
        return;
    }

    int x_proper = x_leftmost * (size - 1);
    int y_proper = y_leftmost * (size - 1);
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = tile.shifted(dx, dy).grid_offset();
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_terrain_add(grid_offset, terrain);
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_monuments_set_progress(tile2i(grid_offset), 0);
            if (image_id >= 0) {
                map_image_set(grid_offset, image_id);
            }
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == x_proper && dy == y_proper);
        }
    }
}

bool building_stepped_pyramid::need_workers() const {
    if (!is_main()) {
        return false;
    }

    const auto &w = runtime_data().workers;
    return std::find(w.begin(), w.end(), 0) != w.end();
}

void building_stepped_pyramid::finalize(building *b, const vec2i size_b) {
    building *part = b;
    building *main = b->main();

    while (!!part) {
        auto monument = part->dcast_monument();
        monument->runtime_data().phase = MONUMENT_FINISHED;
        part = part->has_next() ? part->next() : nullptr;
    }
}

void building_stepped_pyramid::remove_worker(figure_id fid) {
    // Worker list lives on the chain head (guilds / work camps always target
    // is_main, but parts may still receive remove_worker via destination_bid).
    if (!is_main()) {
        main()->remove_worker(fid);
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == fid) {
            wid = 0;
            return;
        }
    }
}

void building_stepped_pyramid::add_workers(figure_id fid) {
    if (!is_main()) {
        main()->add_workers(fid);
        return;
    }
    auto &d = runtime_data();
    for (auto &wid : d.workers) {
        if (wid == 0) {
            wid = fid;
            return;
        }
    }
}

int building_stepped_pyramid::get_image(const building_static_params& params, int orientation, tile2i tile, tile2i start, tile2i end) {
    int image_id = params.base_img();
    int base_image_id = image_id - 7;
    bool insidex = (tile.x() > start.x() && tile.x() < end.x());
    bool insidey = (tile.y() > start.y() && tile.y() < end.y());
    int random = params.first_img(animkeys().ground_phase_0) + ((tile.x() + tile.y()) % 7);
    int result = random;
    if (tile == start) { // top corner
        result = image_id;
    } else if (tile == tile2i(start.x(), end.y())) {
        result = image_id - 2;
    } else if (tile == end) {
        result = image_id - 4;
    } else if (tile == tile2i(end.x(), start.y())) {
        result = image_id - 6;
    } else if (tile.x() == start.x()) {
        result = image_id - 1;
    } else if (tile.y() == end.y()) {
        result = image_id - 3;
    } else if (tile.y() == start.y()) {
        result = (insidex || insidey) ? image_id - 7 : random;
    } else if (tile.x() == end.x()) {
        result = image_id - 5;
    }

    if (result < random) {
        int offset = result - base_image_id;
        result = (base_image_id + (offset + (8 - g_camera.orientation)) % 8);
        return result;
    }

    return result;
}

int building_stepped_pyramid::get_channel_image(int orientation, tile2i tile, tile2i start, tile2i end, int channel_base_id) {  
    bool north = map_terrain_is(tile.shifted(0, -1), TERRAIN_CANAL);
    bool east  = map_terrain_is(tile.shifted(1, 0), TERRAIN_CANAL);
    bool south = map_terrain_is(tile.shifted(0, 1), TERRAIN_CANAL);
    bool west  = map_terrain_is(tile.shifted(-1, 0), TERRAIN_CANAL);

    int neighbors_count = (north ? 1 : 0) + (east ? 1 : 0) + (south ? 1 : 0) + (west ? 1 : 0);

    // 0: zero tile left-corner 
    // 1-2: lines (vert or horz)
    // 3-4: corners (+ city orientation)
    // 5-7: T-corners (4 directions)
    // 8 - cross

    int variant = 0;
    int orientation_offset = (g_camera.orientation / 2) % 4;

    if (neighbors_count == 0) {
        variant = 0;
    } else if (neighbors_count == 1) {
        variant = 0;
    } else if (neighbors_count == 2) {
        if (north && south) {
            variant = (orientation_offset % 2 == 0) ? 1 : 2;
        } else if (east && west) {
            variant = (orientation_offset % 2 == 0) ? 2 : 1;
        } else {
            // corners
            if (north && east) {
                variant = 0 + (orientation_offset % 4);
            } else if (east && south) {
                variant = 1 + (orientation_offset % 4);
            } else if (south && west) {
                variant = 2 + (orientation_offset % 4);
            } else if (west && north) {
                variant = 3 + (orientation_offset % 4);
            }
        }
    } else if (neighbors_count == 3) {
        // T-corners
        if (!north) {
            variant = 5 + ((0 + orientation_offset) % 4);
        } else if (!east) {
            variant = 5 + ((1 + orientation_offset) % 4);
        } else if (!south) {
            variant = 5 + ((2 + orientation_offset) % 4);
        } else { // !west
            variant = 5 + ((3 + orientation_offset) % 4);
        }
    } else {
        variant = 8;
    }

    return channel_base_id + variant;
}

void building_stepped_pyramid::on_create(int orientation) {
    runtime_data().stair_index = 0xff;
}

void building_stepped_pyramid::assign_stair() {
    tile2i mtile = footprint_nw();
    tile2i btile = tile();
    const auto &stairs = footprint_params().stairs;
    auto it = std::find_if(stairs.begin(), stairs.end(), [&] (auto &it) { return mtile.shifted(it.part) == btile; });
    runtime_data().stair_index = (it != stairs.end())
                                    ? (uint8_t)std::distance(stairs.begin(), it)
                                    : 0xff;
}

void building_stepped_pyramid::on_post_load() {
    building_monument::on_post_load();

    assign_stair();
}

void building_stepped_pyramid::on_destroy() {
    // Only COMPLEX/GRAND TYPE claims the strip (walls store length/dir copies).
    // Use tile() as pyramid NW — footprint_nw() walks the part chain and can
    // collapse toward (0,0) once building_update_state has zeroed siblings.
    const auto &d = runtime_data();
    if (d.causeway_length == 0 || !building_type_is_pyramid_complex(type())) {
        return;
    }
    const auto &pi_params = pyramid_params();
    const pyramid_causeway_probe probe = causeway_probe_from_runtime(
        tile(), pi_params.init_tiles, d.causeway_length, d.causeway_dir);
    clear_causeway_tiles(id(), probe);
}

void building_stepped_pyramid::on_config_reload() {
    // stairs[] is reloaded from pyramid.js on --mixed / reload_scripts, but each
    // part keeps a cached stair_index from place/load — rebind so part/tex/offset
    // edits apply without restarting the mission.
    assign_stair();
}

bool building_stepped_pyramid::draw_unfinished_height_ornaments(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    // Complex causeway tiles are owned by the main building but are outside the
    // 20×20 core — OG only ORs TERRAIN_MONUMENT there, so no pyramid bricks.
    if (!tile_in_monument_footprint(tile)) {
        return true;
    }
    if (pyramid_params().pyramide_type != PYRAMID_STYLE_NONE && phase() >= 2) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, tiles_size);
    }

    if (phase() == 6 && runtime_data().alt_image > 0) {
        auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
        command.image_id = runtime_data().alt_image;
        command.pixel = point;
        command.mask = color_mask;
        command.use_sort_pixel = true;
        command.sort_pixel = point + vec2i(0, 1);
        command.location = SOURCE_LOCATION;
    }

    // Flat view: keep light construction cues only — no tall height_impl tiers.
    if (city_flat_should_flatten_building(base)) {
        return true;
    }

    if (phase() < 6) {
        return false;
    }

    return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, tiles_size);
}

bool building_stepped_pyramid::draw_ornaments_and_animations_flat_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {

    if (!tile_in_monument_footprint(tile)) {
        return false;
    }
    if (is_finished()) {
        return false;
    }
    // OG square block engine owns construction from phase 2 — remake ditch/flat
    // ornaments fight sync_visuals(progress=200) and produce black voids.
    if (pyramid_params().pyramide_type != PYRAMID_STYLE_NONE && phase() >= 2) {
        return false;
    }

    if (is_main()) {
        auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
        command.image_id = first_img(animkeys().enter);
        command.pixel = g_camera.lookup_tile_to_pixel(access_point());
        command.use_sort_pixel = true;
        command.sort_pixel = command.pixel + vec2i(0, 1);
        command.location = SOURCE_LOCATION;
    }

    int clear_land_id = first_img(animkeys().clear_land);
    int image_grounded = first_img(animkeys().base_grounded);
    tile2i fnw = footprint_nw();
    color_mask = (color_mask ? color_mask : 0xffffffff);

    auto &monumentd = base.dcast_monument()->runtime_data();
    if (monumentd.phase == 0) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = g_camera.lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);

                if (progress > 0 && progress <= 200) {
                    auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
                    command.image_id = image_grounded + ((dy * 4 + dx) & 7);
                    command.pixel = offset;
                    command.mask = ((0xff * progress / 200) << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff);
                    command.flags = ImgFlag_Alpha;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;
                }
            }
        }

        int image_stick = current_params().first_img(animkeys().image_stick);
        const image_t *img = image_get(image_stick);
        tile2i left_top = base.tile.shifted(0, 0);
        if (left_top == fnw && map_monuments_get_progress(left_top) == 0) {
            vec2i offset = g_camera.lookup_tile_to_pixel(left_top);
            auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }

        tile2i right_top = base.tile.shifted(1, 0);
        if (right_top == fnw.shifted(tiles_size.y - 1, 0) && map_monuments_get_progress(right_top) == 0) {
            vec2i offset = g_camera.lookup_tile_to_pixel(right_top);
            auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }

        tile2i left_bottom = base.tile.shifted(0, 1);
        if (left_bottom == fnw.shifted(0, tiles_size.x - 1) && map_monuments_get_progress(left_bottom) == 0) {
            vec2i offset = g_camera.lookup_tile_to_pixel(left_bottom);
            auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }

        tile2i right_bottom = base.tile.shifted(1, 1);
        if (right_bottom == fnw.shifted(tiles_size.y - 1, tiles_size.x - 1) && map_monuments_get_progress(right_bottom) == 0) {
            vec2i offset = g_camera.lookup_tile_to_pixel(right_bottom);
            auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
            command.image_id = image_stick;
            command.pixel = offset;
            command.mask = color_mask;
            command.use_sort_pixel = true;
            command.sort_pixel = offset + vec2i(0, 1);
            command.location = SOURCE_LOCATION;
        }
    } else if (monumentd.phase == 1) {
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = g_camera.lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
                    command.image_id = image_grounded + ((dy * 4 + dx) & 7);
                    command.pixel = offset;
                    command.mask = color_mask;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;
                }

                if (progress > 0 && progress <= 200) {
                    int img = get_image(current_params(), base.orientation, base.tile.shifted(dx, dy), fnw, fnw.shifted(tiles_size.y - 1, tiles_size.x - 1));

                    auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
                    command.image_id = img;
                    command.pixel = offset;
                    command.mask = ((0xff * progress / 200) << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff);
                    command.flags = ImgFlag_Alpha;
                    command.location = SOURCE_LOCATION;
                }
            }
        }
    } else if (monumentd.phase == 2) {
        const xstring& base_key = animkeys().ditches_phase_1;
        int channel_base_id = current_params().animations[base_key].first_img();
        for (int dy = 0; dy < base.size; dy++) {
            for (int dx = 0; dx < base.size; dx++) {
                tile2i ntile = base.tile.shifted(dx, dy);
                vec2i offset = g_camera.lookup_tile_to_pixel(ntile);
                uint32_t progress = map_monuments_get_progress(ntile);
                if (progress < 200) {
                    int img = get_image(current_params(), base.orientation, base.tile.shifted(dx, dy), fnw, fnw.shifted(tiles_size.y - 1, tiles_size.x - 1));

                    auto& command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
                    command.image_id = img;
                    command.pixel = offset;
                    command.mask = color_mask;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;

                    int channel_img = get_channel_image(base.orientation, ntile, fnw, fnw.shifted(tiles_size.y - 1, tiles_size.x - 1), channel_base_id);
                    if (channel_img > 0 && progress > 0) {

                        auto &channel_command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
                        channel_command.image_id = channel_img;
                        channel_command.pixel = offset;

                        const uint8_t alpha = (0xff * progress / 200);
                        channel_command.mask = ((alpha << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff));
                        channel_command.flags = (progress < 200) ? ImgFlag_Alpha : 0;
                        channel_command.location = SOURCE_LOCATION;
                    }
                } else {
                    int channel_img = get_channel_image(base.orientation, ntile, fnw, fnw.shifted(tiles_size.y - 1, tiles_size.x - 1), channel_base_id);
                    auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
                    command.image_id = channel_img;
                    command.pixel = offset;
                    command.mask = color_mask;
                    command.use_sort_pixel = true;
                    command.sort_pixel = offset + vec2i(0, 1);
                    command.location = SOURCE_LOCATION;
                }
            }
        }
    } else if (monumentd.phase == 3) {
        const xstring &base_key_1 = animkeys().ditches_phase_1;
        const xstring &base_key_2 = animkeys().ditches_phase_2;
        int channel_base_id_1 = current_params().animations[base_key_1].first_img();
        int channel_base_id_2 = current_params().animations[base_key_2].first_img();
        draw_phase_3_5_tile(ctx, color_mask, channel_base_id_1, channel_base_id_2, tiles_size);
    } else if (monumentd.phase == 4) {
        const xstring &base_key_2 = animkeys().ditches_phase_2;
        const xstring &base_key_3 = animkeys().ditches_phase_3;
        int channel_base_id_2 = current_params().animations[base_key_2].first_img();
        int channel_base_id_3 = current_params().animations[base_key_3].first_img();
        draw_phase_3_5_tile(ctx, color_mask, channel_base_id_2, channel_base_id_3, tiles_size);
    } else if (monumentd.phase == 5) {
        const xstring &base_key_3 = animkeys().ditches_phase_3;
        const xstring &base_key_4 = animkeys().ditches_phase_4;
        int channel_base_id_3 = current_params().animations[base_key_3].first_img();
        int channel_base_id_4 = current_params().animations[base_key_4].first_img();
        draw_phase_3_5_tile(ctx, color_mask, channel_base_id_3, channel_base_id_4, tiles_size);
    }

    return true;
}

void building_stepped_pyramid::setup_phase_6_basement() {
    if (!is_main()) {
        return;
    }

    tile2i ctile = center_point();

    int image_basement = current_params().animations["basement"].first_img();
    {
        tile2i left_top = ctile.shifted(-2, 0);
        auto m = building_at(left_top)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement + 1;
    }

    {
        tile2i right_top = ctile.shifted(0, 0);
        auto m = building_at(right_top)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement + 3;
    }

    {
        tile2i left_bottom = ctile.shifted(-2, -2);
        auto m = building_at(left_bottom)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement + 2;
    }

    {
        tile2i right_bottom = ctile.shifted(0, -2);
        auto m = building_at(right_bottom)->dcast_monument();
        auto &md = m->runtime_data();
        md.alt_image = image_basement;
    }
}

void building_stepped_pyramid::setup_phase_6_tiles() {
    const auto &itiles = footprint_params().init_tiles;

    tile2i fnw = footprint_nw();
    tile2i end = fnw.shifted(itiles.y - 1, itiles.x - 1);

    const xstring &base_key_4 = animkeys().ditches_phase_4;
    int channel_base_id_4 = current_params().animations[base_key_4].first_img();

    for (int dy = 0; dy < size(); dy++) {
        for (int dx = 0; dx < size(); dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            int base_img = get_channel_image(base.orientation, ntile, fnw, end, channel_base_id_4);
            map_image_set(ntile, base_img);
        }
    }    
}

void building_stepped_pyramid::draw_phase_3_5_tile(painter& ctx, color color_mask, int channel_base_id_1, int channel_base_id_2, const vec2i tiles_size) {
    tile2i fnw = footprint_nw();
    tile2i end = fnw.shifted(tiles_size.y - 1, tiles_size.x - 1);

    for (int dy = 0; dy < base.size; dy++) {
        for (int dx = 0; dx < base.size; dx++) {
            tile2i ntile = base.tile.shifted(dx, dy);
            vec2i offset = g_camera.lookup_tile_to_pixel(ntile);
            uint32_t progress = map_monuments_get_progress(ntile);
            if (progress < 200) {
                int ditch_empty_img = get_channel_image(base.orientation, ntile, fnw, end, channel_base_id_1);

                auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
                command.image_id = ditch_empty_img;
                command.pixel = offset;
                command.mask = color_mask;
                command.use_sort_pixel = true;
                command.sort_pixel = offset + vec2i(0, 1);
                command.location = SOURCE_LOCATION;

                int ditch_water_img = get_channel_image(base.orientation, ntile, fnw, end, channel_base_id_2);
                if (ditch_water_img > 0 && progress > 0) {

                    auto &channel_command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile);
                    channel_command.image_id = ditch_water_img;
                    channel_command.pixel = offset;

                    const uint8_t alpha = (0xff * progress / 200);
                    channel_command.mask = ((alpha << COLOR_BITSHIFT_ALPHA) | (color_mask & 0x00ffffff));
                    channel_command.flags = (progress < 200) ? ImgFlag_Alpha : 0;
                    channel_command.location = SOURCE_LOCATION;
                }
            } else {
                int channel_img = get_channel_image(base.orientation, ntile, fnw, end, channel_base_id_2);
                auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile);
                command.image_id = channel_img;
                command.pixel = offset;
                command.mask = color_mask;
                command.use_sort_pixel = true;
                command.sort_pixel = offset + vec2i(0, 1);
                command.location = SOURCE_LOCATION;
            }
        }
    }
}

int building_stepped_pyramid::get_bricks_image(int orientation, tile2i tile, tile2i start, tile2i end, int layer) {
    return get_masonry_image(orientation, tile, start, end, layer, false);
}

int building_stepped_pyramid::get_masonry_image(int orientation, tile2i tile, tile2i start, tile2i end, int layer, bool polished) {
    layer %= 6;

    // NW origin building is placed as filler_type but must use corner sprites.
    // Do not use is_main() — orientation can put a wall/corner first in the chain.
    const bool is_nw_origin = (base.tile == footprint_nw());
    const bool is_floor = building_type_any_of(type(), {
        BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID, BUILDING_LARGE_STEPPED_PYRAMID,
        BUILDING_STEPPED_PYRAMID_COMPLEX, BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX,
        BUILDING_SMALL_BENT_PYRAMID, BUILDING_MEDIUM_BENT_PYRAMID,
        BUILDING_SMALL_PYRAMID, BUILDING_SMALL_PYRAMID_CONE,
        BUILDING_MEDIUM_PYRAMID, BUILDING_MEDIUM_PYRAMID_CONE,
        BUILDING_LARGE_PYRAMID, BUILDING_LARGE_PYRAMID_CONE,
        BUILDING_PYRAMID_COMPLEX, BUILDING_GRAND_PYRAMID_COMPLEX,
        BUILDING_SMALL_MUDBRICK_PYRAMID, BUILDING_SMALL_MUDBRICK_PYRAMID_CONE,
        BUILDING_MEDIUM_MUDBRICK_PYRAMID, BUILDING_MEDIUM_MUDBRICK_PYRAMID_CONE,
        BUILDING_LARGE_MUDBRICK_PYRAMID, BUILDING_LARGE_MUDBRICK_PYRAMID_CONE,
        BUILDING_MUDBRICK_PYRAMID_COMPLEX, BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX
    });
    // True polish casing is the outer slope only — flat filler tops read as
    // ledges and leak through the ridge once draw-tile order changes on rotate.
    if (is_floor && !is_nw_origin) {
        if (polished) {
            return 0;
        }
        return current_params().first_img("base_bricks") + layer;
    }

    tile = building_at(tile)->tile;
    start = building_at(start)->tile;
    end = building_at(end)->tile;

    const bool is_corner = building_type_any_of(type(), {
        BUILDING_SMALL_STEPPED_PYRAMID_CORNER, BUILDING_MEDIUM_STEPPED_PYRAMID_CORNER, BUILDING_LARGE_STEPPED_PYRAMID_CORNER,
        BUILDING_SMALL_BENT_PYRAMID_CORNER, BUILDING_MEDIUM_BENT_PYRAMID_CORNER,
        BUILDING_SMALL_PYRAMID_CORNER, BUILDING_MEDIUM_PYRAMID_CORNER,
        BUILDING_LARGE_PYRAMID_CORNER,
        BUILDING_SMALL_MUDBRICK_PYRAMID_CORNER,
        BUILDING_MEDIUM_MUDBRICK_PYRAMID_CORNER,
        BUILDING_LARGE_MUDBRICK_PYRAMID_CORNER
    });
    // OG pyramid_images.rotated_kind: face index += view (orientation/2), wrap in 0..3.
    const int view = (g_camera.orientation / 2) & 3;

    if (is_corner || is_nw_origin) {
        const xstring corner_key = polished && current_params().first_img("corner_polish") > 0
            ? "corner_polish" : "corner_bricks";
        int image_corner_bricks = current_params().first_img(corner_key) + (layer * 8);
        // 2×2 part may not sit on the exact remapped corner tile — use touch.
        const bool at_min_x = (tile.x() <= start.x());
        const bool at_min_y = (tile.y() <= start.y());
        const bool at_max_x = (tile.x() >= end.x());
        const bool at_max_y = (tile.y() >= end.y());
        int face = 0;
        if (at_min_x && at_min_y) face = 0;
        else if (at_min_x && at_max_y) face = 1;
        else if (at_max_x && at_max_y) face = 2; // visual bottom → stepped_pyramid_00043 at layer 5
        else if (at_max_x && at_min_y) face = 3;
        return image_corner_bricks + ((face + view) & 3);
    }

    const bool is_wall = building_type_any_of(type(), {
        BUILDING_SMALL_STEPPED_PYRAMID_WALL, BUILDING_MEDIUM_STEPPED_PYRAMID_WALL, BUILDING_LARGE_STEPPED_PYRAMID_WALL,
        BUILDING_SMALL_BENT_PYRAMID_WALL, BUILDING_MEDIUM_BENT_PYRAMID_WALL,
        BUILDING_SMALL_PYRAMID_WALL, BUILDING_MEDIUM_PYRAMID_WALL,
        BUILDING_LARGE_PYRAMID_WALL,
        BUILDING_SMALL_MUDBRICK_PYRAMID_WALL,
        BUILDING_MEDIUM_MUDBRICK_PYRAMID_WALL,
        BUILDING_LARGE_MUDBRICK_PYRAMID_WALL
    });
    if (is_wall) {
        const xstring wall_key = polished && current_params().first_img("wall_polish") > 0
            ? "wall_polish" : "wall_bricks";
        int image_wall_bricks = current_params().first_img(wall_key) + (layer * 8);
        int face = 0;
        if (tile.x() <= start.x()) face = 0;
        else if (tile.y() <= start.y()) face = 3;
        else if (tile.x() >= end.x()) face = 2;
        else if (tile.y() >= end.y()) face = 1;
        return image_wall_bricks + ((face + view) & 3);
    }

    return 0;
}

void building_stepped_pyramid::draw_ornaments_and_animations_stairs_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    // phase() is uint8_t: MONUMENT_FINISHED (-1) becomes 255, which would match every stair.
    if (is_finished()) {
        return;
    }
    // Remake stairs[] are decorative phase sprites — OG square engine uses carpenter
    // ramps (monument_pyramid_ramp). Drawing them on the complex SE edge looks serrated.
    if (pyramid_params().pyramide_type != PYRAMID_STYLE_NONE) {
        return;
    }

    auto &d = runtime_data();
    const auto &stairs = footprint_params().stairs;
    if (d.stair_index == 0xff || d.stair_index >= stairs.size()) {
        return;
    }

    const auto &stair = stairs[d.stair_index];
    if (phase() >= stair.phase) {
        auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
        command.image_id = stair.tex.first_img();
        command.pixel = point + stair.offset;
        command.mask = color_mask;
    }
}

bool building_stepped_pyramid::draw_ornaments_and_animations_hight_impl(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    if (!tile_in_monument_footprint(tile)) {
        return true;
    }
    color_mask = (color_mask ? color_mask : 0xffffffff);
    const auto &d = runtime_data();
    const int ph = phase();
    const int nlayers = std::max(1, footprint_params().init_tiles.x / 4);
    // Last schedule index = RESOURCE_NONE terminal (stepped S24/M32/L36; true adds polish first).
    const int terminal_phase = phases() - 1;

    auto fill_tiles_height = [](painter & /*ctx*/, tile2i tile, int img) {
        const image_t *image = image_get(img);
        if (!image) {
            return;
        }
        int iso_size = image->isometric_size() - 1;
        grid_tiles tiles = map_grid_get_tiles(tile, tile.shifted(iso_size, iso_size));
        for (auto &t : tiles) {
            map_building_height_set(t.grid_offset(), image->isometric_top_height);
        }
    };

    // Finished / terminal marker — not mid-band phase numbers (24 on large is L3 work).
    if (is_finished() || ph == terminal_phase) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, tiles_size);
    }

    if (ph < 6 || nlayers <= 0) {
        return true;
    }

    // Brick bands: 6–11 → L0, 12–17 → L1, … ; building_L = ph/6 - 1.
    // Padding after the last real tier (medium 24–31, small 18–23): building_L >= nlayers
    // so every part draws as a finished lower tier.
    const int building_L = ph / 6 - 1;
    const int L = d.layer;

    tile2i anchor = base.tile;
    switch (g_camera.orientation) {
    case DIR_0_TOP_RIGHT: anchor = base.tile.shifted(0, 1); break;
    case DIR_4_BOTTOM_LEFT: anchor = base.tile.shifted(1, 0); break;
    case DIR_6_TOP_LEFT: anchor = base.tile.shifted(1, 1); break;
    default: break;
    }
    const vec2i anchor_px = g_camera.lookup_tile_to_pixel(anchor);

    if (L < building_L) {
        if (L >= 0 && L < nlayers) {
            auto layer_area = get_layer_area(L);
            int img = get_bricks_image(base.orientation, tile, layer_area.begin, layer_area.end, 5);
            auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
            command.image_id = img;
            command.pixel = anchor_px - vec2i{0, TILE_HEIGHT_PIXELS * 3 * L};
            command.mask = color_mask;
            fill_tiles_height(ctx, anchor, img);
        }
    } else if (building_L >= 0 && building_L < nlayers) {
        uint32_t progress = map_monuments_get_progress(tile);
        const int band_start = 6 * (building_L + 1);

        // Upper tiers sit on a flat underlay at the previous ledge (L0 has none).
        if (building_L >= 1) {
            int layer_img = current_params().first_img("base_bricks") + 5;
            auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
            command.image_id = layer_img;
            command.pixel = anchor_px - vec2i{0, TILE_HEIGHT_PIXELS * 3 * (building_L - 1)};
            command.mask = color_mask;
        }

        // course = (ph - band_start) when tile incomplete; +1 when progress >= 200.
        // Equiv. to old phase==6 / 6–12 / 12–18 … base_level formulas.
        int base_level = (ph - band_start) + ((progress >= 200) ? 1 : 0);
        if (base_level > 0) {
            auto layer_area = get_layer_area(building_L);
            int img = get_bricks_image(base.orientation, tile, layer_area.begin, layer_area.end, base_level - 1);
            auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
            command.image_id = img;
            command.pixel = anchor_px - vec2i{0, TILE_HEIGHT_PIXELS * 3 * building_L};
            command.mask = color_mask;
            fill_tiles_height(ctx, anchor, img);
        }
    }

    if (ph > 6) {
        draw_ornaments_and_animations_stairs_impl(ctx, point, tile, color_mask, tiles_size);
    }

    return true;
}

bool building_stepped_pyramid::draw_completed_height_ornaments(painter &ctx, vec2i point, tile2i tile, color color_mask, const vec2i tiles_size) {
    if (!tile_in_monument_footprint(tile)) {
        return true;
    }

    color_mask = (color_mask ? color_mask : 0xffffffff);
    const auto &d = runtime_data();
    const e_pyramid_style style = pyramid_params().pyramide_type;
    const int L = d.layer;

    const vec2i footprint = footprint_params().init_tiles;
    const int nlayers = std::max(1, footprint.x / 4);

    building* head = base.main();
    auto* ms = pyramid_main_state_get(head ? head->id : 0);
    auto* ps = pyramid_part_state_get(base.id);

    auto fill_tiles_height = [](painter & /*ctx*/, tile2i tile, int img) {
        const image_t *image = image_get(img);
        if (!image) {
            return;
        }
        int iso_size = image->isometric_size() - 1;
        grid_tiles tiles = map_grid_get_tiles(tile, tile.shifted(iso_size, iso_size));
        for (auto &t : tiles) {
            map_building_height_set(t.grid_offset(), image->isometric_top_height);
        }
    };

    // Anchor to the orientation draw-tile of this 2×2 part (same as map_building_tiles_add),
    // not whatever city pass `point` is — keeps casing joined across rotates.
    tile2i anchor = base.tile;
    switch (g_camera.orientation) {
    case DIR_0_TOP_RIGHT: anchor = base.tile.shifted(0, 1); break;
    case DIR_4_BOTTOM_LEFT: anchor = base.tile.shifted(1, 0); break;
    case DIR_6_TOP_LEFT: anchor = base.tile.shifted(1, 1); break;
    default: break;
    }
    const vec2i anchor_px = g_camera.lookup_tile_to_pixel(anchor);

    // OG bent pyramid_part_draw (city_without_overlay draws pyramids only here):
    //   height = bent_pixel_heights[layer]
    //   draw_x/y = city tile + (half_w+1, -half_h) - height
    //   height!=0 → image_draw + isometric_top; height==0 → isometric_top only
    //   (footprint pass already drew the map image base — set on finish).
    if (style == PYRAMID_STYLE_BENT && ps) {
        const int img = bent_og_part_image(base, *ps, is_finished());
        if (img <= 0) {
            return true;
        }
        const int size_variant = (int)ps->size_variant;
        const int lift = g_monument_pyramid_engine.bent_layer_pixel_height(size_variant, (int)ps->layer);
        // OG's (+half_w+1, -half_h) draw shift is already folded into drawtile here.
        const vec2i pixel = anchor_px - vec2i{0, lift};
        if (lift != 0) {
            auto& full = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
            full.image_id = img;
            full.pixel = pixel;
            full.mask = color_mask;
        } else {
            // Map footprint already drew ert_drawtile base — only the top here.
            auto& top = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_top);
            top.image_id = img;
            const image_t* im = image_get(img);
            const int offset_y = im ? image_iso_top_offset_y(im) : 0;
            top.pixel = pixel - vec2i{0, offset_y};
            top.mask = color_mask;
        }
        fill_tiles_height(ctx, anchor, img);
        pyramid_engine_update_part_ramp_image(base.id);
        const vec2i ramp_origin = pixel + vec2i{HALF_TILE_WIDTH_PIXELS + 1, -HALF_TILE_HEIGHT_PIXELS};
        pyramid_ramp_draw_part(ctx, base, ramp_origin, color_mask);
        return true;
    }

    bool polished = use_polish_sprites_for_layer(L);

    int course = 5;
    if (style != PYRAMID_STYLE_NONE) {
        if (ms && ms->style != PYRAMID_STYLE_NONE && ms->style != PYRAMID_STYLE_MASTABA) {
            const int total = g_monument_pyramid_engine.block_total(&base);
            if (polished) {
                if (!is_finished() && ms->block_phase_active && ms->remaining_blocks > 0) {
                    const int done = total - (int)ms->remaining_blocks;
                    course = std::clamp(done * 6 / std::max(1, total), 0, 5);
                } else {
                    course = 5;
                }
            } else {
                const int done = is_finished() ? total : (total - (int)ms->remaining_blocks);
                const int blocks_per_ring = std::max(1, total / nlayers);
                const int ring_start = L * blocks_per_ring;
                const int ring_done = std::clamp(done - ring_start, 0, blocks_per_ring);
                course = std::clamp(ring_done * 6 / blocks_per_ring, 0, 5);
            }
        }
    }

    if (L < 0 || L >= nlayers) {
        return true;
    }

    // Stepped/brick: ledge underlay fills the raised ring. True casing must
    // stay a continuous slope — the flat ledge reads as extra steps.
    if (L >= 1 && !polished) {
        int under_img = current_params().first_img("base_bricks") + course;
        if (under_img > course) {
            auto &under = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
            under.image_id = under_img;
            under.pixel = anchor_px - vec2i{0, TILE_HEIGHT_PIXELS * 3 * (L - 1)};
            under.mask = color_mask;
        }
    }

    auto layer_area = get_layer_area(L);
    int img = get_masonry_image(base.orientation, tile, layer_area.begin, layer_area.end, course, polished);
    if (img <= 0) {
        return true;
    }

    const int lift = TILE_HEIGHT_PIXELS * 3 * L;
    const vec2i pixel = anchor_px - vec2i{0, lift};

    auto &command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_full);
    command.image_id = img;
    command.pixel = pixel;
    command.mask = color_mask;

    fill_tiles_height(ctx, anchor, img);
    pyramid_engine_update_part_ramp_image(base.id);
    // pyramid_part_draw: draw_x = x + tile_half_width+1, draw_y = y - tile_half_height - layer.
    // Akhenaten tile pixel + layer lift maps to (x, y - layer); add the half-tile shift so
    // ramp_base/ramp_offsets land on the same origin image_draw used.
    const vec2i ramp_origin = pixel + vec2i{HALF_TILE_WIDTH_PIXELS + 1, -HALF_TILE_HEIGHT_PIXELS};
    pyramid_ramp_draw_part(ctx, base, ramp_origin, color_mask);
    return true;
}

span_const<uint16_t> building_stepped_pyramid::active_workers() const {
    auto &monumentd = runtime_data();
    return span_const<uint16_t>(monumentd.workers);
}

void building_stepped_pyramid::update_day(const vec2i tiles_size) {
    auto &monumentd = runtime_data();
    // Callers also guard, but keep a local bail — after FINISHED, phase() as
    // uint8_t is 255 and must not re-enter promote / ring logic.
    if (is_finished()) {
        return;
    }

    grid_tiles tiles = map_grid_get_tiles(&base, 0);
    tile2i tile2works = map_grid_area_first(tiles, [] (tile2i tile) { return map_monuments_get_progress(tile) < 200; });
    bool all_tiles_finished = (tile2works == tile2i{ -1, -1 });
    building_impl *part = this;
    if (!is_main()) {
        return;
    }

    if (all_tiles_finished) {
        int curr_phase = phase();
        const int nphases = phases();
        // Last schedule index is a terminal marker (RESOURCE_NONE) — same pattern as
        // mastaba phase 8. Keep tiles at 200 when entering it so the next day can
        // advance past size → FINISHED. Clearing here left progress at 0 forever
        // (no mason work on an empty terminal) and natural finish never happened.
        const bool entering_terminal = (curr_phase + 1 >= nphases - 1);
        const bool finishing = (curr_phase + 1 >= nphases);
        if (!entering_terminal) {
            map_grid_area_foreach(tiles, [] (tile2i tile) { map_monuments_set_progress(tile, 0); });
        }
        while (part) {
            verify_no_crash(part->dcast_monument());
            part->dcast_monument()->set_phase(curr_phase + 1);
            part = part->has_next() ? part->next() : nullptr;
        }
        // set_phase(phases()) stores FINISHED immediately — the old
        // `phase() >= phases()` head-check never saw a live phase==size and
        // congrats never fired on natural completion. Post them here once.
        if (finishing) {
            // Use schedule btype (shared by corner/wall parts), not the part's
            // building type — orientation can make a corner the is_main() head.
            const e_building_type mon_type = config().btype;
            const bool is_bent = (mon_type == BUILDING_SMALL_BENT_PYRAMID
                || mon_type == BUILDING_MEDIUM_BENT_PYRAMID);
            const bool is_mudbrick = (mon_type == BUILDING_SMALL_MUDBRICK_PYRAMID
                || mon_type == BUILDING_MEDIUM_MUDBRICK_PYRAMID
                || mon_type == BUILDING_LARGE_MUDBRICK_PYRAMID
                || mon_type == BUILDING_MUDBRICK_PYRAMID_COMPLEX
                || mon_type == BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX);
            const bool is_true = (mon_type == BUILDING_SMALL_PYRAMID
                || mon_type == BUILDING_MEDIUM_PYRAMID
                || mon_type == BUILDING_LARGE_PYRAMID
                || mon_type == BUILDING_PYRAMID_COMPLEX
                || mon_type == BUILDING_GRAND_PYRAMID_COMPLEX);
            pcstr congrats = is_mudbrick ? "mudbrick_pyramid_congratulations"
                : (is_true ? "pyramid_congratulations"
                : (is_bent ? "bent_pyramid_congratulations" : "stepped_pyramid_congratulations"));
            city_message &message = city_message_post_with_popup_delay(MESSAGE_CAT_MONUMENTS, true, congrats, type(), tile().grid_offset());
            message.hide_img = true;
            return;
        }
    }

    // Resource gate: claimed tiles (progress 1) become workable (2) once enough
    // materials are on-site. Mastaba uses phase >= 2; using >= 6 here left phases
    // 2–5 with masons stuck on progress 1 forever (need_stonemason starts at 2).
    if (phase() >= 2) {
        int minimal_percent = 100;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            bool need_resource = needs_resource(r);
            if (need_resource) {
                minimal_percent = std::min<int>(minimal_percent, monumentd.resources_pct[r]);
            }
        }
        minimal_percent = std::clamp(minimal_percent, 0, 100);

        grid_tiles tiles = map_grid_get_tiles(&base, 0);
        tiles.resize(tiles.size() * minimal_percent / 100);

        for (auto &tile : tiles) {
            int progress = map_monuments_get_progress(tile);
            if (progress == 1) {
               set_tile_progress(tile, 2);
            }
        }
    }
}

void building_stepped_pyramid::on_place_checks() {
    const tile2i tiles_to_check[] = { tile(), tile().shifted(1, 0), tile().shifted(0, 1), tile().shifted(1, 1) };
    bool has_water = false;
    for (const auto &t : tiles_to_check) {
        has_water |= map_terrain_is(t, TERRAIN_GROUNDWATER);
    }

    construction_warnings warnings;
    warnings.add_if(!has_water, "#needs_groundwater");

    assign_stair();
}

void building_stepped_pyramid::update_count() const {
    if (!is_main()) {
        return;
    }

    building_monument::update_count();
}

void building_stepped_pyramid::update_month() {
    if (!is_main()) {
        return;
    }

    auto &monumentd = runtime_data();
    for (uint16_t &w_id : monumentd.workers) {
        figure* f = figure_get(w_id);
        if (!f || !f->is_alive() || f->destination() != &base) {
            w_id = 0;
        }
    }
}

void building_stepped_pyramid::update_map_orientation(int map_orientation) {
    if (is_finished()) {
        map_building_tiles_add(id(), tile(), base.size, building_image_get(), TERRAIN_BUILDING);
    }

    if (is_main() && building_type_is_pyramid_complex(type())) {
        refresh_complex_causeway_orientation(base);
    }
}

bool building_stepped_pyramid::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    if (is_finished()) {
        return false;
    }
    if (!tile_in_monument_footprint(tile)) {
        return false;
    }

    return (phase() < 7);
}

void building_stepped_pyramid::bind_dynamic(io_buffer *iob, size_t version) {
    auto &monumentd = runtime_data();

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind_u8(monumentd.burial_stock[i]);
    }
    iob->bind_u16(monumentd.alt_image);
    iob->bind_u8(base.orientation);
    for (int i = 0; i < 5; i++) {
        iob->bind_u16(monumentd.workers[i]);
    }
    iob->bind_i8(monumentd.phase);
    iob->bind_u8(monumentd.layer);
    iob->bind_u8(monumentd.stair_index);
    iob->bind_u8(monumentd.variant);

    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind_u8(monumentd.resources_pct[i]);
    }

    // funeral_done appended (mastaba reclaims a former skip byte instead).
    if (version >= 179) {
        iob->bind_u8(monumentd.funeral_done);
    } else {
        monumentd.funeral_done = 0;
    }
    // Preexisting sealed tomb flag.
    if (version >= 180) {
        iob->bind_u8(monumentd.preexisting);
    } else {
        monumentd.preexisting = 0;
    }
    if (version >= 182) {
        iob->bind_u8(monumentd.causeway_length);
        iob->bind_u8(monumentd.causeway_dir);
    } else {
        monumentd.causeway_length = 0;
        monumentd.causeway_dir = 0;
    }
}

int building_small_stepped_pyramid::building_image_get() const {
    switch (runtime_data().phase) {
    case MONUMENT_START:
        return building_static_params::get(BUILDING_SMALL_STEPPED_PYRAMID).base_img();
    default:
        return building_static_params::get(BUILDING_SMALL_STEPPED_PYRAMID).base_img() + 1;
    }

    return 0;
}

void building_small_stepped_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

bool building_small_stepped_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_small_stepped_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_small_stepped_pyramid::config() const {
    return g_monument_small_stepped_pyramid;
}

// Helper function to check if a block is a corner block (by block index)
bool is_corner_block(int block_x, int block_y, int blocks_x, int blocks_y) {
    return (block_x == 0 && block_y == 0) ||                                  // top-left
        (block_x == blocks_x - 1 && block_y == 0) ||                       // top-right
        (block_x == blocks_x - 1 && block_y == blocks_y - 1) ||            // bottom-right
        (block_x == 0 && block_y == blocks_y - 1);                         // bottom-left
}

// Helper function to check if a block is on the perimeter (by block index)
bool is_on_perimeter_block(int block_x, int block_y, int blocks_x, int blocks_y) {
    return block_x == 0 || block_x == blocks_x - 1 ||
        block_y == 0 || block_y == blocks_y - 1;
}

void building_stepped_pyramid::change_parts_types_in_layer(tile2i begin, const vec2i layer_size, uint8_t layer) {
    hvector<pyramid_part, 256> parts;

    // Parts are 2x2 tiles, so calculate number of blocks in each dimension
    const int part_size = 2;
    int blocks_x = layer_size.x / part_size;  // e.g., 10/2 = 5
    int blocks_y = layer_size.y / part_size;  // e.g., 10/2 = 5

    const auto &pi_params = pyramid_params();

    // Fill pyramid parts for the first layer
    // Iterate through blocks (each block is 2x2 tiles)
    for (int block_y = 0; block_y < blocks_y; block_y++) {
        for (int block_x = 0; block_x < blocks_x; block_x++) {
            // Calculate tile offset for this block (top-left corner of 2x2 block)
            int tile_x = block_x * part_size;
            int tile_y = block_y * part_size;
            tile2i part_tile = begin.shifted(tile_x, tile_y);

            // Skip only the real NW building of layer 0. Inner layers' NW
            // corner is a normal part — skipping it leaves the apex 4×4 with a
            // stale filler at layer-1 and a hollow/L-shaped top.
            // Use footprint_nw (not list head): orientation can make a wall is_main.
            if (part_tile == footprint_nw()) {
                continue;
            }

            // Determine part type based on block position
            e_building_type part_type;
            if (is_on_perimeter_block(block_x, block_y, blocks_x, blocks_y)) {
                // Block is on perimeter
                if (is_corner_block(block_x, block_y, blocks_x, blocks_y)) {
                    part_type = pi_params.corner_type;
                } else {
                    part_type = pi_params.wall_type;
                }
            } else {
                // Block is interior (filler)
                part_type = pi_params.filler_type;
            }

            parts.push_back({ part_type, {tile_x, tile_y}, building_at(part_tile) });
        }
    }

    for (auto &part : parts) {
        part.b->clear_impl();
        part.b->type = part.type;
        auto *mon = part.b->dcast_monument();
        mon->runtime_data().layer = layer;
        mon->runtime_data().stair_index = 0xff;
    }

    // clear_impl resets stair_index — rebind ramps for the new ring types.
    for (building *b = base.main(); b; b = b->has_next() ? b->next() : nullptr) {
        if (building_pyramid *pyr = b->dcast_pyramid()) {
            static_cast<building_stepped_pyramid *>(pyr)->assign_stair();
        }
    }
}

building_stepped_pyramid::layer_area building_stepped_pyramid::get_layer_area(int layer) const {
    vec2i layer_size = footprint_params().init_tiles;
    layer_size -= vec2i{ layer * 4, layer * 4 };
    tile2i begin_tile = footprint_nw().shifted(layer * 2, layer * 2);
    tile2i end_tile = begin_tile.shifted(layer_size - vec2i{1, 1});

    return { begin_tile, end_tile, layer_size };
}

void building_stepped_pyramid::on_place(int orientation, int variant) {
    building_pyramid::on_place(orientation, variant);

    base.prev_part_building_id = 0;
    map_pyramid_tiles_add(id(), tile(), base.size, -1, TERRAIN_BUILDING);

    hvector<pyramid_part, 256> parts;

    // Get pyramid size from params
    const auto &pi_params = pyramid_params();
    vec2i pyramid_size = pi_params.init_tiles;

    // Parts are 2x2 tiles, so calculate number of blocks in each dimension
    const int part_size = 2;
    int blocks_x = pyramid_size.x / part_size;  // e.g., 10/2 = 5
    int blocks_y = pyramid_size.y / part_size;  // e.g., 10/2 = 5

    // Fill pyramid parts for the first layer
    // Iterate through blocks (each block is 2x2 tiles)
    for (int block_y = 0; block_y < blocks_y; block_y++) {
        for (int block_x = 0; block_x < blocks_x; block_x++) {
            // Calculate tile offset for this block (top-left corner of 2x2 block)
            int tile_x = block_x * part_size;
            int tile_y = block_y * part_size;

            // Skip the main building position (top-left block)
            if (block_x == 0 && block_y == 0) {
                continue;
            }

            // Determine part type based on block position
            e_building_type part_type;
            if (is_on_perimeter_block(block_x, block_y, blocks_x, blocks_y)) {
                // Block is on perimeter
                if (is_corner_block(block_x, block_y, blocks_x, blocks_y)) {
                    part_type = pi_params.corner_type;
                } else {
                    part_type = pi_params.wall_type;
                }
            } else {
                // Block is interior (filler)
                part_type = pi_params.filler_type;
            }

            parts.push_back({part_type, {tile_x, tile_y}, nullptr});
        }
    }

    // Create all part buildings
    for (auto &part : parts) {
        part.b = building_create(part.type, tile().shifted(part.offset), 0);
        game_undo_add_building(part.b);
        tile2i btile_add = tile().shifted(part.offset);
        map_pyramid_tiles_add(part.b->id, btile_add, part.b->size, -1, TERRAIN_BUILDING);
    }

    // Add main building to parts list
    pyramid_part main{type(), {0, 0}, &base};
    switch (orientation) {
    case 0: parts.insert(parts.begin(), main); break;
    case 1: parts.insert(parts.begin() + 1, main); break;
    case 2: parts.push_back(main); break;
    case 3: parts.push_back(main); break;
    }

    // Link all parts together
    building* prev_part = nullptr;
    for (auto &part : parts) {
        part.b->prev_part_building_id = prev_part ? prev_part->id : 0;
        if (prev_part) {
            prev_part->next_part_building_id = part.b->id;
        }
        prev_part = part.b;
    }

    // Bind ramp sprites to the matching 2×2 parts. Without this, stair_index stays 0
    // and every part draws stairs[0] at ground level along the edge.
    for (auto &part : parts) {
        if (building_pyramid *pyr = part.b->dcast_pyramid()) {
            static_cast<building_stepped_pyramid *>(pyr)->assign_stair();
        }
    }

    if (building_type_is_pyramid_complex(type())) {
        // tile() is the NW place anchor for the 20×20 core.
        const bool east_only = building_type_is_grand_pyramid_complex(type());
        const pyramid_causeway_probe probe = map_pyramid_complex_find_causeway(tile(), pyramid_size, east_only);
        for (building *part = base.main(); part; part = part->has_next() ? part->next() : nullptr) {
            if (auto *mon = part->dcast_monument()) {
                auto &d = mon->runtime_data();
                d.causeway_length = probe.ok ? (uint8_t)probe.length : 0;
                d.causeway_dir = probe.ok ? (uint8_t)probe.dir : 0;
            }
        }

        if (probe.ok) {
            claim_causeway_tiles(id(), probe);
        }
    }
}

void building_stepped_pyramid::on_phase_changed(int old, int current) {
    if (current >= 2) {
        int terrain = TERRAIN_BUILDING;
        if (current >= 3) {
            terrain |= TERRAIN_CANAL;
        }
        map_building_tiles_add(id(), tile(), size(), this->building_image_get(), terrain);
    }

    if (current == 6) {
        setup_phase_6_tiles();
        setup_phase_6_basement();
    }

    // Raise ring L at phase 6*(L+1): L1@12, L2@18, L3@24, L4@30, …
    // Skip zero-size rings (small/medium past their footprint).
    if (is_main() && current >= 12 && current % 6 == 0) {
        const int L = current / 6 - 1;
        auto area = get_layer_area(L);
        if (area.size.x > 0 && area.size.y > 0) {
            change_parts_types_in_layer(area.begin, area.size, (uint8_t)L);
        }
    }

    if (current != MONUMENT_FINISHED) {
        auto &d = runtime_data();
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }
}

void building_medium_stepped_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_medium_stepped_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_medium_stepped_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_medium_stepped_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_medium_stepped_pyramid::config() const {
    return g_monument_medium_stepped_pyramid;
}

// --- Large stepped pyramid (20×20) ---------------------------------------------
// Thin per-type wrappers around the shared stepped machinery, keyed on their own
// current_params() (init_tiles [20,20]).

void building_large_stepped_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_large_stepped_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_large_stepped_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_large_stepped_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_large_stepped_pyramid::config() const {
    return g_monument_large_stepped_pyramid;
}

// --- Stepped pyramid complex (20×20, on-land) -----------------------------------
// Same wrappers as large (TYPE-keyed current_params). Phase schedule shared with large.

void building_stepped_pyramid_complex::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_stepped_pyramid_complex::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_stepped_pyramid_complex::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_stepped_pyramid_complex::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_stepped_pyramid_complex::config() const {
    // Same cadence as large until causeway/temples land; keep btype = COMPLEX for any
    // schedule readers.
    static monument m = [] {
        monument copy = g_monument_large_stepped_pyramid;
        copy.btype = BUILDING_STEPPED_PYRAMID_COMPLEX;
        return copy;
    }();
    return m;
}

void building_grand_stepped_pyramid_complex::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_grand_stepped_pyramid_complex::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_grand_stepped_pyramid_complex::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_grand_stepped_pyramid_complex::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_grand_stepped_pyramid_complex::config() const {
    static monument m = [] {
        monument copy = g_monument_large_stepped_pyramid;
        copy.btype = BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX;
        return copy;
    }();
    return m;
}

// --- Bent pyramids -------------------------------------------------------------
// Thin per-type wrappers around the shared stepped machinery. Each keys on its own
// current_params() (TYPE = BENT), so the rendered art comes from PACK_BENT_PYRAMID.

void building_small_bent_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_small_bent_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_small_bent_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_small_bent_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_small_bent_pyramid::use_polish_sprites_for_layer(int /*layer*/) const {
    // Like true: continuous limestone slope (no stepped ledge underlay).
    if (is_finished()) {
        return true;
    }
    // OG finishing phase — remaining_blocks counts down through casing_total.
    building* head = base.main();
    auto* ms = pyramid_main_state_get(head ? head->id : 0);
    if (!ms || !ms->block_phase_active || ms->remaining_blocks == 0) {
        return false;
    }
    const int casing = g_monument_pyramid_engine.casing_total(head);
    return casing > 0 && (int)ms->remaining_blocks <= casing;
}

const monument &building_small_bent_pyramid::config() const {
    return g_monument_small_bent_pyramid;
}

void building_medium_bent_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_medium_bent_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_medium_bent_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_medium_bent_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_ornaments_and_animations_hight_impl(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_medium_bent_pyramid::use_polish_sprites_for_layer(int /*layer*/) const {
    if (is_finished()) {
        return true;
    }
    building* head = base.main();
    auto* ms = pyramid_main_state_get(head ? head->id : 0);
    if (!ms || !ms->block_phase_active || ms->remaining_blocks == 0) {
        return false;
    }
    const int casing = g_monument_pyramid_engine.casing_total(head);
    return casing > 0 && (int)ms->remaining_blocks <= casing;
}

const monument &building_medium_bent_pyramid::config() const {
    return g_monument_medium_bent_pyramid;
}

// --- True (smooth) small pyramid (polish phases) --------------------------------

void building_small_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_small_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_small_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_small_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }

    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_small_pyramid::need_stonemason() {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_TRUE) {
        return building_pyramid::need_stonemason();
    }
    if (is_finished() || !is_main()) {
        return false;
    }

    const int p = phase();
    if (p < 2 || p >= phases() - 1) {
        return false;
    }

    return need_workers();
}

void building_small_pyramid::on_phase_changed(int old, int current) {
    if (current == k_polish_phase_begin || current == 30) {
        if (current >= 2) {
            int terrain = TERRAIN_BUILDING;
            if (current >= 3) {
                terrain |= TERRAIN_CANAL;
            }
            map_building_tiles_add(id(), tile(), size(), building_image_get(), terrain);
        }
        if (current != MONUMENT_FINISHED) {
            auto &d = runtime_data();
            for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
                d.resources_pct[resource] = 0;
            }
        }
        return;
    }
    building_stepped_pyramid::on_phase_changed(old, current);
}

bool building_small_pyramid::use_polish_sprites_for_layer(int layer) const {
    if (is_finished()) {
        return true;
    }
    const int p = phase();
    // Top-down: first polish phase covers upper layers, second covers base.
    if (p >= k_polish_phase_begin + 1) {
        return true;
    }
    if (p >= k_polish_phase_begin) {
        return layer >= 1;
    }
    return false;
}

const monument &building_small_pyramid::config() const {
    return g_monument_small_pyramid;
}

// --- Mudbrick (brick-core) small pyramid (polish phases) ------------------------

void building_small_mudbrick_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_small_mudbrick_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_small_mudbrick_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_small_mudbrick_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }

    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

void building_small_mudbrick_pyramid::on_phase_changed(int old, int current) {
    // Same as true small: phases 24–25 are polish (skip stepped ring-raise path).
    if (current == k_polish_phase_begin || current == 30) {
        if (current >= 2) {
            int terrain = TERRAIN_BUILDING;
            if (current >= 3) {
                terrain |= TERRAIN_CANAL;
            }
            map_building_tiles_add(id(), tile(), size(), building_image_get(), terrain);
        }
        if (current != MONUMENT_FINISHED) {
            auto &d = runtime_data();
            for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
                d.resources_pct[resource] = 0;
            }
        }
        return;
    }
    building_stepped_pyramid::on_phase_changed(old, current);
}

bool building_small_mudbrick_pyramid::use_polish_sprites_for_layer(int layer) const {
    // OG block finish = brick core only; limestone casing is a later stage.
    if (is_finished()) {
        return false;
    }
    const int p = phase();
    if (p >= k_polish_phase_begin + 1) {
        return true;
    }
    if (p >= k_polish_phase_begin) {
        return layer >= 1;
    }
    return false;
}

const monument &building_small_mudbrick_pyramid::config() const {
    return g_monument_small_mudbrick_pyramid;
}

// --- Mudbrick (brick-core) medium pyramid (polish after height) ------------------

void building_medium_mudbrick_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_medium_mudbrick_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_medium_mudbrick_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_medium_mudbrick_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_medium_mudbrick_pyramid::use_polish_sprites_for_layer(int layer) const {
    if (is_finished()) {
        return false;
    }
    const int p = phase();
    // Top-down across 3 layers (0..2): 32→top, 33→mid+, 34+→all.
    if (p >= k_polish_phase_begin + 2) {
        return true;
    }
    if (p >= k_polish_phase_begin + 1) {
        return layer >= 1;
    }
    if (p >= k_polish_phase_begin) {
        return layer >= 2;
    }
    return false;
}

const monument &building_medium_mudbrick_pyramid::config() const {
    return g_monument_medium_mudbrick_pyramid;
}

// --- Mudbrick (brick-core) large pyramid (16×16, polish after height 35) ---------

void building_large_mudbrick_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_large_mudbrick_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_large_mudbrick_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_large_mudbrick_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

void building_large_mudbrick_pyramid::on_phase_changed(int old, int current) {
    // Same as true large: polish begins at 36, which collides with stepped 6*(L+1).
    if (current >= k_polish_phase_begin) {
        if (current >= 2) {
            int terrain = TERRAIN_BUILDING;
            if (current >= 3) {
                terrain |= TERRAIN_CANAL;
            }
            map_building_tiles_add(id(), tile(), size(), building_image_get(), terrain);
        }
        if (current != MONUMENT_FINISHED) {
            auto &d = runtime_data();
            for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
                d.resources_pct[resource] = 0;
            }
        }
        return;
    }
    building_stepped_pyramid::on_phase_changed(old, current);
}

bool building_large_mudbrick_pyramid::use_polish_sprites_for_layer(int layer) const {
    if (is_finished()) {
        return false;
    }
    const int p = phase();
    if (p < k_polish_phase_begin) {
        return false;
    }
    // Top-down across 4 layers (0..3): phase 36→top … 39+→all.
    const int polish_i = p - k_polish_phase_begin;
    if (polish_i >= k_polish_layers - 1) {
        return true;
    }
    return layer >= (k_polish_layers - 1 - polish_i);
}

const monument &building_large_mudbrick_pyramid::config() const {
    return g_monument_large_mudbrick_pyramid;
}

// --- Mudbrick complex / grand (20×20 on-land + causeway; annex later) -----------

void building_mudbrick_pyramid_complex::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_mudbrick_pyramid_complex::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_mudbrick_pyramid_complex::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_mudbrick_pyramid_complex::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_mudbrick_pyramid_complex::use_polish_sprites_for_layer(int layer) const {
    if (is_finished()) {
        return false;
    }
    const int p = phase();
    if (p < k_polish_phase_begin) {
        return false;
    }
    const int polish_i = p - k_polish_phase_begin;
    if (polish_i >= k_polish_layers - 1) {
        return true;
    }
    return layer >= (k_polish_layers - 1 - polish_i);
}

const monument &building_mudbrick_pyramid_complex::config() const {
    static monument m = [] {
        monument copy = g_monument_mudbrick_pyramid_20;
        copy.btype = BUILDING_MUDBRICK_PYRAMID_COMPLEX;
        return copy;
    }();
    return m;
}

void building_grand_mudbrick_pyramid_complex::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_grand_mudbrick_pyramid_complex::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_grand_mudbrick_pyramid_complex::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_grand_mudbrick_pyramid_complex::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_grand_mudbrick_pyramid_complex::use_polish_sprites_for_layer(int layer) const {
    if (is_finished()) {
        return false;
    }
    const int p = phase();
    if (p < k_polish_phase_begin) {
        return false;
    }
    const int polish_i = p - k_polish_phase_begin;
    if (polish_i >= k_polish_layers - 1) {
        return true;
    }
    return layer >= (k_polish_layers - 1 - polish_i);
}

const monument &building_grand_mudbrick_pyramid_complex::config() const {
    static monument m = [] {
        monument copy = g_monument_mudbrick_pyramid_20;
        copy.btype = BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX;
        return copy;
    }();
    return m;
}

void building_medium_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_medium_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_medium_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_medium_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    // Polish/terminal: full-height casing. Height courses use 24/30 as brick bands —
    // only divert once polish begins (phase >= 32).
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_medium_pyramid::need_stonemason() {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_TRUE) {
        return building_pyramid::need_stonemason();
    }
    if (is_finished() || !is_main()) {
        return false;
    }
    const int p = phase();
    if (p < 2 || p >= phases() - 1) {
        return false;
    }
    return need_workers();
}

bool building_medium_pyramid::use_polish_sprites_for_layer(int layer) const {
    if (is_finished()) {
        return true;
    }
    const int p = phase();
    // Top-down across 3 layers (0..2): 32→top, 33→mid+, 34+→all.
    if (p >= k_polish_phase_begin + 2) {
        return true;
    }
    if (p >= k_polish_phase_begin + 1) {
        return layer >= 1;
    }
    if (p >= k_polish_phase_begin) {
        return layer >= 2;
    }
    return false;
}

const monument &building_medium_pyramid::config() const {
    return g_monument_medium_pyramid;
}

// --- True (smooth) large pyramid (C3b + C3.4 polish after height) --------------

void building_large_pyramid::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_large_pyramid::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_large_pyramid::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_large_pyramid::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    // Polish/terminal only — height still uses unfinished bands through phase 35.
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

bool building_large_pyramid::need_stonemason() {
    if (pyramid_params().pyramide_type == PYRAMID_STYLE_TRUE) {
        return building_pyramid::need_stonemason();
    }
    if (is_finished() || !is_main()) {
        return false;
    }
    const int p = phase();
    if (p < 2 || p >= phases() - 1) {
        return false;
    }
    return need_workers();
}

void building_large_pyramid::on_phase_changed(int old, int current) {
    // Polish/terminal start at 36 (= 6*6) — stepped ring-raise would target L5.
    if (current >= k_polish_phase_begin) {
        if (current >= 2) {
            int terrain = TERRAIN_BUILDING;
            if (current >= 3) {
                terrain |= TERRAIN_CANAL;
            }
            map_building_tiles_add(id(), tile(), size(), building_image_get(), terrain);
        }
        if (current != MONUMENT_FINISHED) {
            auto &d = runtime_data();
            for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
                d.resources_pct[resource] = 0;
            }
        }
        return;
    }
    building_stepped_pyramid::on_phase_changed(old, current);
}

bool building_large_pyramid::use_polish_sprites_for_layer(int layer) const {
    if (is_finished()) {
        return true;
    }
    const int p = phase();
    if (p < k_polish_phase_begin) {
        return false;
    }
    // Top-down across 5 layers (0..4): phase 36→top … 40+→all.
    const int polish_i = p - k_polish_phase_begin;
    if (polish_i >= k_polish_layers - 1) {
        return true;
    }
    return layer >= (k_polish_layers - 1 - polish_i);
}

const monument &building_large_pyramid::config() const {
    return g_monument_large_pyramid;
}

// --- True pyramid complex / grand (C3c, on-land = large) ----------------------

void building_pyramid_complex::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_pyramid_complex::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_pyramid_complex::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_pyramid_complex::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_pyramid_complex::config() const {
    static monument m = [] {
        monument copy = g_monument_large_pyramid;
        copy.btype = BUILDING_PYRAMID_COMPLEX;
        return copy;
    }();
    return m;
}

void building_grand_pyramid_complex::update_day() {
    building_impl::update_day();

    if (is_finished()) {
        return;
    }
    if (run_block_day()) {
        return;
    }

    building_stepped_pyramid::update_day(current_params().init_tiles);
}

int building_grand_pyramid_complex::building_image_get() const {
    switch (phase()) {
    case MONUMENT_START:
        return current_params().base_img();
    default:
        return current_params().base_img() + 1;
    }

    return 0;
}

bool building_grand_pyramid_complex::draw_ornaments_and_animations_flat(painter &ctx, vec2i point, tile2i tile, color mask) {
    return draw_ornaments_and_animations_flat_impl(ctx, point, tile, mask, current_params().init_tiles);
}

bool building_grand_pyramid_complex::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    if (is_finished()) {
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    if (phase() >= k_polish_phase_begin) {
        if (city_flat_should_flatten_building(base)) {
            return true;
        }
        return draw_completed_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
    }
    return draw_unfinished_height_ornaments(ctx, point, tile, color_mask, current_params().init_tiles);
}

const monument &building_grand_pyramid_complex::config() const {
    static monument m = [] {
        monument copy = g_monument_large_pyramid;
        copy.btype = BUILDING_GRAND_PYRAMID_COMPLEX;
        return copy;
    }();
    return m;
}