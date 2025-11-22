#include "city_overlay_fertility.h"

#include "grid/floodplain.h"
#include "building/building.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "grid/image.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/point.h"
#include "game/state.h"


static int terrain_on_fertility_overlay(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_ROAD
            | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE | TERRAIN_CANAL | TERRAIN_WALL;
}

static int get_fertility_image_offset(int fertilty) {
    return (fertilty / 10);
}

city_overlay_fertility g_city_overlay_fertility;

inline bool city_overlay_fertility::show_figure(const figure *f) const {
    if (f->type != FIGURE_CART_PUSHER) {
        return false;
    }

    if (f->sender_building_id == 0) {
        return false;
    }

    building *b = building_get(f->sender_building_id);
    return b && building_is_farm(b->type);
}

inline void city_overlay_fertility::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    int grid_offset = point.grid_offset();

    color color_mask = 0;
    if (map_terrain_is(grid_offset, terrain_on_fertility_overlay()) && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(grid_offset);
        command.pixel = pixel;
        command.mask = color_mask;
    } else if (map_terrain_is(grid_offset, TERRAIN_BUILDING) || map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        int fertility = map_get_fertility(grid_offset, FERT_WITH_MALUS);
        int offset = get_fertility_image_offset(fertility);

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY) + offset;
        command.pixel = pixel;
        command.mask = color_mask;

    } else {
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(grid_offset);
        command.pixel = pixel;
        command.mask = color_mask;
    }
}

xstring city_overlay_fertility::get_tooltip(tooltip_context *c, tile2i) const {
    return {};
}

xstring city_overlay_fertility::get_tooltip_for_building(tooltip_context *c, const building *b) {
    if (building_is_farm(b->type)) {
        tile2i tile = b->tile;
        int fertility = map_get_fertility_for_farm(tile.grid_offset());
        if (fertility > 80)
            return ui::str(66, 63);
        else if (fertility > 60)
            return ui::str(66, 62);
        else if (fertility > 40)
            return ui::str(66, 61);
        else if (fertility > 20)
            return ui::str(66, 60);
        else if (fertility > 10)
            return ui::str(66, 59);
        else {
            return ui::str(66, 58);
        }
    }
    return ui::str(66, 58);
}

int city_overlay_fertility::get_column_height(const building *b) const {
    return COLUMN_TYPE_NONE;
}

inline bool city_overlay_fertility::show_building(const building *b) const {
    return false;// building_is_farm(b->type);
}
