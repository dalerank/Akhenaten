#include "city_overlay_architect_reach.h"

#include "building/building.h"
#include "city/city_buildings.h"
#include "figure/figure.h"
#include "figure/figure_static_params.h"
#include "game/game.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/architect_reach.h"
#include "grid/building.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "window/window_info.h"

#include <algorithm>

city_overlay_architect_reach g_city_overlay_architect_reach;

city_overlay_architect_reach::city_overlay_architect_reach() {
    es_name = "overlay_architect_reach";
}

void city_overlay_architect_reach::ensure_up_to_date() const {
    if (last_update_frame == game.frame) {
        return;
    }
    last_update_frame = game.frame;

    object_info &oi = common_info_window::get_object_info();

    bool selected = false;
    if (const int fid = oi.figure_get_id()) {
        figure *f = ::figure_get(fid);
        if (f && f->type == FIGURE_ARCHITECT && f->homeID()) {
            source_bid = f->homeID();
            selected = true;
        }
    }
    if (!selected && oi.bid) {
        building *b = building_get(oi.bid);
        if (b && b->type == BUILDING_ARCHITECT_POST) {
            source_bid = oi.bid;
        }
    }

    const auto &params = figure_static_params::get(FIGURE_ARCHITECT);
    const e_permission perm = params.permission;
    last_max_tiles = params.max_roam_length;

    tile2i origin;
    if (source_bid) {
        building *home = building_get(source_bid);
        if (home && home->type == BUILDING_ARCHITECT_POST && home->has_road_access) {
            origin = home->road_access;
        } else {
            source_bid = 0;
        }
    }

    if (!source_bid || !origin.valid()) {
        map_grid_clear(g_architect_reach_distance);
        return;
    }

    map_architect_reach_calculate(origin, perm, last_max_tiles);
}

static int reach_image_offset(int dist, int max_tiles) {
    if (max_tiles <= 0) {
        return 5;
    }
    // Near = green (9), far = red (0)
    const int band = (dist * 9) / max_tiles;
    return 9 - std::min(band, 9);
}

static bool is_road_like_tile(int grid_offset) {
    return map_terrain_is(grid_offset, TERRAIN_ROAD | TERRAIN_ACCESS_RAMP);
}

bool city_overlay_architect_reach::show_figure(const figure *f) const {
    if (f->type != FIGURE_ARCHITECT) {
        return false;
    }
    ensure_up_to_date();
    return source_bid && f->homeID() == source_bid;
}

int city_overlay_architect_reach::get_column_height(const building *b) const {
    return COLUMN_TYPE_NONE;
}

bool city_overlay_architect_reach::show_building(const building *b) const {
    if (!b) {
        return false;
    }
    ensure_up_to_date();
    if (b->type == BUILDING_ROADBLOCK) {
        return true;
    }
    if (b->type == BUILDING_ARCHITECT_POST) {
        return source_bid == 0 || b->id == source_bid;
    }
    return false;
}

void city_overlay_architect_reach::get_tooltip(tooltip_context *c, tile2i tile, xstring &tooltip) {
    ensure_up_to_date();
    if (!source_bid) {
        tooltip = "#overlay_architect_reach_hint";
        return;
    }

    const int dist = map_architect_reach_distance(tile);
    if (dist >= 0) {
        tooltip = "#overlay_architect_reach_tile";
    }
}

bool city_overlay_architect_reach::draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const {
    ensure_up_to_date();

    const int grid_offset = point.grid_offset();
    const color color_mask = map_property_is_deleted(grid_offset) ? COLOR_MASK_RED : COLOR_MASK_NONE;
    const int dist = map_architect_reach_distance(point);
    const bool road = is_road_like_tile(grid_offset);

    if (road && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        if (source_bid && dist >= 0) {
            const int img_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY)
                + reach_image_offset(dist, last_max_tiles);
            auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_full);
            command.image_id = img_id;
            command.pixel = pixel;
            command.mask = color_mask;
            command.location = SOURCE_LOCATION;
            return true;
        }

        if (source_bid) {
            // Unreachable road while a source is selected
            const int img_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY) + 2;
            auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_full);
            command.image_id = img_id;
            command.pixel = pixel;
            command.mask = color_mask;
            command.location = SOURCE_LOCATION;
            return true;
        }

        // No source: leave default road rendering
        return false;
    }

    // Reachable road under plaza / roadblock building tiles
    if (source_bid && dist >= 0 && map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        building *b = building_at(grid_offset);
        if (b && (b->type == BUILDING_PLAZA || b->type == BUILDING_ROAD || b->type == BUILDING_ROADBLOCK)) {
            const int img_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY)
                + reach_image_offset(dist, last_max_tiles);
            auto &command = ImageDraw::create_command(ctx, render_command_t::ert_drawtile_full);
            command.image_id = img_id;
            command.pixel = pixel;
            command.mask = color_mask;
            command.location = SOURCE_LOCATION;
            return true;
        }
    }

    return false;
}
