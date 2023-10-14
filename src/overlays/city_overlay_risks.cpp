#include "city_overlay_risks.h"

#include "city_overlay.h"
#include "building/industry.h"
#include "building/model.h"
#include "game/state.h"
#include "graphics/boilerplate.h"
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
        else if (b->stored_full_amount <= 0)
            b->show_on_problem_overlay = 1;
    } else if (b->state == BUILDING_STATE_MOTHBALLED)
        b->show_on_problem_overlay = 1;
}

static int show_building_problems(const building* b) {
    return b->show_on_problem_overlay;
}

static int show_building_native(const building* b) {
    return b->type == BUILDING_NATIVE_HUT || b->type == BUILDING_NATIVE_MEETING || b->type == BUILDING_MISSION_POST;
}

static int show_figure_problems(const figure* f) {
    if (f->type == FIGURE_LABOR_SEEKER)
        return ((figure*)f)->home()->show_on_problem_overlay;
    else if (f->type == FIGURE_CART_PUSHER)
        return f->action_state == FIGURE_ACTION_20_CARTPUSHER_INITIAL || f->min_max_seen;
    else {
        return 0;
    }
}

static int show_figure_native(const figure* f) {
    return f->type == FIGURE_INDIGENOUS_NATIVE || f->type == FIGURE_MISSIONARY;
}

city_overlay* city_overlay_for_problems() {
    static city_overlay overlay = {
        OVERLAY_PROBLEMS,
        COLUMN_TYPE_RISK,
        show_building_problems,
        show_figure_problems,
        get_column_height_none,
        0,
        0,
        0,
        0
    };
    return &overlay;
}

static int terrain_on_native_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE;
}

static void draw_footprint_native(vec2i pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    if (!map_property_is_draw_tile(grid_offset))
        return;
    if (map_terrain_is(grid_offset, terrain_on_native_overlay())) {
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING))
            city_with_overlay_draw_building_footprint(x, y, grid_offset, 0);
        else {
            ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, 0);
        }
    } else if (map_terrain_is(grid_offset, TERRAIN_CANAL | TERRAIN_WALL)) {
        // display groundwater
        int image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7);
        ImageDraw::isometric_from_drawtile(image_id, x, y, 0);
    } else if (map_terrain_is(grid_offset, TERRAIN_BUILDING))
        city_with_overlay_draw_building_footprint(x, y, grid_offset, 0);
    else {
        if (map_property_is_native_land(grid_offset))
            ImageDraw::isometric_from_drawtile(image_id_from_group(GROUP_TERRAIN_DESIRABILITY) + 1, x, y, 0);
        else {
            ImageDraw::isometric_from_drawtile(map_image_at(grid_offset), x, y, 0);
        }
    }
}
static void draw_top_native(vec2i pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    if (!map_property_is_draw_tile(grid_offset))
        return;
    if (map_terrain_is(grid_offset, terrain_on_native_overlay())) {
        if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            color color_mask = 0;
            if (map_property_is_deleted(grid_offset) && map_property_multi_tile_size(grid_offset) == 1)
                color_mask = COLOR_MASK_RED;

            //            ImageDraw::isometric_top_from_drawtile(map_image_at(grid_offset), x, y, color_mask,
            //            city_view_get_scale_float());
        }
    } else if (map_building_at(grid_offset))
        city_with_overlay_draw_building_top(pixel, point);
}

city_overlay* city_overlay_for_native() {
    static city_overlay overlay = {
        OVERLAY_NATIVE,
        COLUMN_TYPE_RISK,
        show_building_native,
        show_figure_native,
        get_column_height_none,
        0,
        0,
        draw_footprint_native,
        draw_top_native
    };
    return &overlay;
}
