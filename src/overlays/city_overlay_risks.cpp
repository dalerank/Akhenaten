#include "city_overlay_risks.h"

#include "game/state.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/building.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "figure/figure.h"
#include "city/city_buildings.h"
#include "figuretype/figure_cartpusher.h"

city_overlay_problems g_city_overlay_problems;
city_overlay_native g_city_overlay_native;

static int is_problem_cartpusher(figure *fig) {
    if (fig->id > 0) {
        return fig->action_state == ACTION_20_CARTPUSHER_INITIAL && fig->min_max_seen;
    } else {
        return 0;
    }
}

void overlay_problems_prepare_building(building* b) {
    auto house = b->dcast_house();

    if (house) {
        return;
    }

    if (b->type == BUILDING_MENU_BEAUTIFICATION || b->type == BUILDING_MENU_MONUMENTS) {
        if (!b->has_water_access)
            b->show_on_problem_overlay = 1;
    } else if (b->type >= BUILDING_BARLEY_FARM && b->type <= BUILDING_CLAY_PIT) {
        if (is_problem_cartpusher(b->get_figure(0)))
            b->show_on_problem_overlay = 1;
    } else if (b->is_workshop()) {
        if (is_problem_cartpusher(b->get_figure(0)))
            b->show_on_problem_overlay = 1;
        else if (!b->workshop_has_resources())
            b->show_on_problem_overlay = 1;
    } else if (b->state == BUILDING_STATE_MOTHBALLED)
        b->show_on_problem_overlay = 1;
}


static int terrain_on_native_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE;
}

bool city_overlay_problems::show_figure(const figure *f) const {
    if (f->type == FIGURE_LABOR_SEEKER) {
        return ((figure *)f)->home()->show_on_problem_overlay;
    } else if (f->type == FIGURE_CART_PUSHER) {
        return f->action_state == ACTION_20_CARTPUSHER_INITIAL || f->min_max_seen;
    } 

    return false;
}

int city_overlay_problems::get_column_height(const building *b) const {
    return COLUMN_TYPE_NONE;
}

void city_overlay_problems::draw_building_top(vec2i pixel, tile2i tile, painter &ctx) const {
    building *b = building_at(tile);
    overlay_problems_prepare_building(b);
    city_overlay::draw_building_top(pixel, tile, ctx);
}

bool city_overlay_problems::show_building(const building *b) const {
    return b->show_on_problem_overlay;
}

void city_overlay_native::draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile))
        return;

    if (map_terrain_is(tile, terrain_on_native_overlay())) {
        if (!map_terrain_is(tile, TERRAIN_BUILDING)) {
            color color_mask = 0;
            if (map_property_is_deleted(tile) && map_property_multi_tile_size(tile) == 1)
                color_mask = COLOR_MASK_RED;

            //            ImageDraw::isometric_top_from_drawtile(map_image_at(grid_offset), x, y, color_mask,
            //            city_view_get_scale_float());
        }
    } else if (map_building_at(tile)) {
        city_overlay::draw_building_top(pixel, tile, ctx);
    }
}

bool city_overlay_native::draw_custom_footprint(vec2i pixel, tile2i tile, painter &ctx) const {
    if (!map_property_is_draw_tile(tile))
        return true;

    if (map_terrain_is(tile, terrain_on_native_overlay())) {
        if (map_terrain_is(tile, TERRAIN_BUILDING))
            city_overlay::draw_building_footprint(ctx, pixel, tile, 0);
        else {
            auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
            command.image_id = map_image_at(tile);
            command.pixel = pixel;
            command.mask = COLOR_MASK_NONE;
        }
    } else if (map_terrain_is(tile, TERRAIN_CANAL | TERRAIN_WALL)) {
        // display groundwater
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(tile) & 7);
        command.pixel = pixel;
        command.mask = COLOR_MASK_NONE;
    } else if (map_terrain_is(tile, TERRAIN_BUILDING)) {
        city_overlay::draw_building_footprint(ctx, pixel, tile, 0);
    } else {
        int image_id = 0;
        if (map_property_is_native_land(tile)) {
            image_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY) + 1;
        } else {
            image_id = map_image_at(tile);
        }

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = COLOR_MASK_NONE;
    }

    return true;
}

int city_overlay_native::get_column_height(const building *b) const {
    return COLUMN_TYPE_NONE;
}

bool city_overlay_native::show_building(const building *b) const {
    return b->type == BUILDING_UNUSED_NATIVE_HUT_88 || b->type == BUILDING_UNUSED_NATIVE_MEETING_89 || b->type == BUILDING_RESERVER_MISSION_POST_80;
}

