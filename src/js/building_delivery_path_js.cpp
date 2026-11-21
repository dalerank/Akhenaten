#include "city/city_recorded_paths.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "building/construction/build_planner.h"
#include "city/city_figures.h"
#include "core/bstring.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/variant.h"
#include "figure/figure.h"
#include "figure/figure_type.h"
#include "game/game.h"
#include "graphics/color.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "js/js_game.h"

namespace {

constexpr int k_path_dot_img_offset = 3;
constexpr int k_buyer_path_x_offset = 5;

static void draw_recorded_path_tiles(painter &ctx, const recorded_path_tiles_t &tiles, color mask, int base_img,
                                     vec2i pixel_offset = {0, 0}) {
    if (tiles.empty()) {
        return;
    }

    tile2i start((int)tiles[0]);
    if (start.valid()) {
        vec2i pixel = g_camera.lookup_tile_to_pixel(start) + pixel_offset;
        ghost_draw::draw_building_ghost(ctx, base_img + k_path_dot_img_offset, pixel, mask);
    }

    for (size_t t = 1; t < tiles.size(); t++) {
        tile2i from((int)tiles[t - 1]);
        tile2i to((int)tiles[t]);
        if (!from.valid() || !to.valid()) {
            continue;
        }
        int img_index = 10;
        switch (calc_general_direction(from, to)) {
        case DIR_0_TOP_RIGHT:
        case DIR_4_BOTTOM_LEFT:
            img_index = 0;
            break;
        case DIR_2_BOTTOM_RIGHT:
        case DIR_6_TOP_LEFT:
            img_index = 1;
            break;
        default:
            break;
        }
        vec2i pixel = g_camera.lookup_tile_to_pixel(to) + pixel_offset;
        ghost_draw::draw_building_ghost(ctx, base_img + img_index, pixel, mask);
    }
}

static void draw_recorded_path_dots(painter &ctx, const recorded_path_tiles_t &tiles, color mask, int base_img,
                                    vec2i pixel_offset = {0, 0}) {
    const int dot_img = base_img + k_path_dot_img_offset;
    for (size_t t = 0; t < tiles.size(); t++) {
        tile2i tile((int)tiles[t]);
        if (!tile.valid()) {
            continue;
        }
        vec2i pixel = g_camera.lookup_tile_to_pixel(tile) + pixel_offset;
        ghost_draw::draw_building_ghost(ctx, dot_img, pixel, mask);
    }
}

static bool is_hunter_figure_type(e_figure_type ftype) {
    return ftype == FIGURE_OSTRICH_HUNTER || ftype == FIGURE_ANTELOPE_HUNTER || ftype == FIGURE_BIRDS_HUNTER;
}

static void draw_bazaar_path(painter &ctx, int path_id, int base_img, e_figure_type ftype) {
    if (!path_id) {
        return;
    }
    const auto &tiles = g_recorded_paths.tiles(path_id);
    if (ftype == FIGURE_MARKET_BUYER) {
        draw_recorded_path_dots(ctx, tiles, COLOR_MASK_RED, base_img, {k_buyer_path_x_offset, 0});
    } else if (ftype == FIGURE_MARKET_TRADER) {
        draw_recorded_path_dots(ctx, tiles, COLOR_MASK_GREEN, base_img);
    } else {
        draw_recorded_path_tiles(ctx, tiles, COLOR_MASK_AMBER, base_img);
    }
}

static void draw_hunting_lodge_path(painter &ctx, int path_id, int base_img, e_figure_type ftype) {
    if (!path_id) {
        return;
    }
    const auto &tiles = g_recorded_paths.tiles(path_id);
    if (is_hunter_figure_type(ftype)) {
        draw_recorded_path_tiles(ctx, tiles, COLOR_MASK_RED, base_img);
    } else if (ftype == FIGURE_CART_PUSHER) {
        draw_recorded_path_tiles(ctx, tiles, COLOR_MASK_GREEN, base_img);
    } else {
        draw_recorded_path_tiles(ctx, tiles, COLOR_MASK_AMBER, base_img);
    }
}

} // namespace

void building_draw_usable_paths(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building *main = b->main();
    const int mid = main ? main->id : bid;
    const bool is_bazaar = main && main->dcast_bazaar();
    const bool is_hunting_lodge = main && main->type == BUILDING_HUNTING_LODGE;

    static const color path_colors[BUILDING_RECORDED_PATHS] = {
        COLOR_MASK_AMBER,
        COLOR_MASK_GREEN,
        COLOR_MASK_BLUE,
        COLOR_MASK_RED,
    };
    const int base_img = image_id_from_group(PACK_CUSTOM, 1);
    painter ctx = game.painter();

    for (int i = 0; i < BUILDING_RECORDED_PATHS; i++) {
        const int path_id = g_recorded_paths.building_path_at(mid, i);
        if (!path_id) {
            continue;
        }
        const e_figure_type ftype = (e_figure_type)g_recorded_paths.figure_type(path_id);
        if (is_bazaar) {
            draw_bazaar_path(ctx, path_id, base_img, ftype);
        } else if (is_hunting_lodge) {
            draw_hunting_lodge_path(ctx, path_id, base_img, ftype);
        } else {
            draw_recorded_path_tiles(ctx, g_recorded_paths.tiles(path_id), path_colors[i], base_img);
        }
    }

    for (figure *f : map_figures()) {
        if (!f || f->is_dead() || f->trail_path_id <= 0) {
            continue;
        }
        bool linked = false;
        building *dest = f->destination();
        if (dest && dest->is_valid()) {
            building *dest_main = dest->main();
            linked = dest_main && dest_main->id == mid;
        }
        if (!linked) {
            building *home = f->home();
            if (home && home->is_valid()) {
                building *home_main = home->main();
                linked = home_main && home_main->id == mid;
            }
        }
        if (!linked) {
            continue;
        }
        if (is_bazaar) {
            draw_bazaar_path(ctx, f->trail_path_id, base_img, f->type);
        } else if (is_hunting_lodge) {
            draw_hunting_lodge_path(ctx, f->trail_path_id, base_img, f->type);
        } else {
            draw_recorded_path_tiles(ctx, g_recorded_paths.tiles(f->trail_path_id), COLOR_MASK_NONE, base_img);
        }
    }
}

static void __building_draw_usable_paths(int bid) {
    building_draw_usable_paths(bid);
}
ANK_FUNCTION_1(__building_draw_usable_paths)
