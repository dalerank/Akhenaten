#include "city_overlay_risks.h"

#include "building/industry.h"
#include "building/model.h"
#include "game/state.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/building.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "figure/figure.h"

static int is_problem_cartpusher(figure *fig) {
    if (fig->id > 0) {
        return fig->action_state == FIGURE_ACTION_20_CARTPUSHER_INITIAL && fig->min_max_seen;
    } else {
        return 0;
    }
}

void overlay_problems_prepare_building(building* b) {
    if (b->house_size)
        return;

    if (b->type == BUILDING_MENU_BEAUTIFICATION || b->type == BUILDING_MENU_MONUMENTS) {
        if (!b->has_water_access)
            b->show_on_problem_overlay = 1;
    } else if (b->type >= BUILDING_BARLEY_FARM && b->type <= BUILDING_CLAY_PIT) {
        if (is_problem_cartpusher(b->get_figure(0)))
            b->show_on_problem_overlay = 1;
    } else if (building_is_workshop(b->type)) {
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

city_overlay *city_overlay_for_problems() {
    static city_overlay_problems overlay;
    return &overlay;
}

bool city_overlay_problems::show_figure(const figure *f) const {
    if (f->type == FIGURE_LABOR_SEEKER) {
        return ((figure *)f)->home()->show_on_problem_overlay;
    } else if (f->type == FIGURE_CART_PUSHER) {
        return f->action_state == FIGURE_ACTION_20_CARTPUSHER_INITIAL || f->min_max_seen;
    } 

    return false;
}

int city_overlay_problems::get_column_height(const building *b) const {
    return NO_COLUMN;
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
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pixel, 0);
        }
    } else if (map_terrain_is(tile, TERRAIN_CANAL | TERRAIN_WALL)) {
        // display groundwater
        int image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(tile) & 7);
        ImageDraw::isometric_from_drawtile(ctx, image_id, pixel, 0);
    } else if (map_terrain_is(tile, TERRAIN_BUILDING))
        city_overlay::draw_building_footprint(ctx, pixel, tile, 0);
    else {
        if (map_property_is_native_land(tile)) {
            ImageDraw::isometric_from_drawtile(ctx, image_id_from_group(GROUP_TERRAIN_DESIRABILITY) + 1, pixel, 0);
        } else {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(tile), pixel, 0);
        }
    }

    return true;
}

int city_overlay_native::get_column_height(const building *b) const {
    return NO_COLUMN;
}

bool city_overlay_native::show_building(const building *b) const {
    return b->type == BUILDING_UNUSED_NATIVE_HUT_88 || b->type == BUILDING_UNUSED_NATIVE_MEETING_89 || b->type == BUILDING_RESERVER_MISSION_POST_80;
}

city_overlay* city_overlay_for_native() {
    static city_overlay_native overlay;
    return &overlay;
}

