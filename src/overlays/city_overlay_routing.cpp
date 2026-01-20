#include "city_overlay_routing.h"

#include "building/building.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/image.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "city/city_buildings.h"
#include "game/state.h"

city_overlay_routing g_city_overlay_routing;

static int terrain_on_routing_overlay() {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP  | TERRAIN_RUBBLE | TERRAIN_CANAL | TERRAIN_WALL;
}

static bool building_on_routing_overlay(e_building_type type) {
    return building_type_any_of(type, { BUILDING_FERRY, BUILDING_PLAZA, BUILDING_BOOTH, BUILDING_ROAD });
}

inline bool city_overlay_routing::show_figure(const figure *f) const {
    return (f->type == FIGURE_IMMIGRANT);
}

int city_overlay_routing::get_column_height(const building *b) const {
    return COLUMN_TYPE_NONE;
}

inline void city_overlay_routing::draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
    int grid_offset = point.grid_offset();

    color color_mask = 0;
    bool drawn = false;
    int image_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY);
    if (map_terrain_is(grid_offset, terrain_on_routing_overlay()) && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        drawn = true;

        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(grid_offset);
        command.pixel = pixel;
        command.mask = color_mask;
    }

    if (!drawn && map_terrain_is(grid_offset, TERRAIN_WATER)) {
        drawn = true;
        if (map_terrain_is(grid_offset, TERRAIN_FERRY_ROUTE)) {
            image_id += 4;
        } else if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
            image_id += 5;
        } else {
            image_id = map_image_at(grid_offset);
        }
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = image_id;
        command.pixel = pixel;
        command.mask = color_mask;
    }

    if (!drawn) {
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING) || map_terrain_is(grid_offset, TERRAIN_WATER)) {
            building *b = building_at(grid_offset);
            int offset = 2;

            if (b && !building_on_routing_overlay(b->type)) {
                auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
                command.image_id = image_id + offset;
                command.pixel = pixel;
                command.mask = color_mask;
                drawn = true;
            }
        }
    }

    building *b = building_at(grid_offset);
    if (!drawn) {
        bool road = map_terrain_is(grid_offset, TERRAIN_ROAD);
        bool building_road = b && building_on_routing_overlay(b->type);

        if (road || building_road) {
            drawn = true;

            auto& command = ImageDraw::create_subcommand(render_command_t::ert_drawtile);
            command.image_id = image_id + 5;
            command.pixel = pixel;
            command.mask = color_mask;
        }
    }

    if (!drawn) {
        auto& command = ImageDraw::create_command(render_command_t::ert_drawtile);
        command.image_id = map_image_at(grid_offset);
        command.pixel = pixel;
        command.mask = color_mask;
    }
}

xstring city_overlay_routing::get_tooltip_for_building(tooltip_context *c, const building *b) {
    if (b->is_farm()) {
        tile2i tile = b->tile;
        int fertility = 0;
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

inline bool city_overlay_routing::show_building(const building *b) const {
    return /*b->type == BUILDING_FERRY ||*/ b->type == BUILDING_PLAZA || b->type == BUILDING_BOOTH;
}
