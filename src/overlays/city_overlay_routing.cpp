#include "city_overlay_routing.h"

#include "city_overlay.h"

#include "building/model.h"
#include "building/building.h"
#include "figure/figure.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "grid/image.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "game/state.h"

static int get_tooltip_routing(tooltip_context* c, const building* b) {
    if (building_is_farm(b->type)) {
        map_point tile = b->tile;
        int fertility = 0;
        if (fertility > 80)
            return 63;
        else if (fertility > 60)
            return 62;
        else if (fertility > 40)
            return 61;
        else if (fertility > 20)
            return 60;
        else if (fertility > 10)
            return 59;
        else {
            return 58;
        }
    }
    return 58;
}

static int terrain_on_routing_overlay() {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP  | TERRAIN_RUBBLE | TERRAIN_CANAL | TERRAIN_WALL;
}

static bool building_on_routing_overlay(e_building_type type) {
    return type == BUILDING_FERRY || type == BUILDING_PLAZA || type == BUILDING_BOOTH || type == BUILDING_ROAD;
}

struct city_overlay_routing : public city_overlay {
    city_overlay_routing() {
        type = OVERLAY_ROUTING;
        column_type = COLUMN_TYPE_RISK;

        get_column_height = get_column_height_none;
        get_tooltip_for_building = get_tooltip_routing;   
    }

    bool show_figure(const figure* f) const override {
        if (f->type != FIGURE_IMMIGRANT) {
            return false;
        }

        return true;
    }

    void draw_custom_top(vec2i pixel, map_point point, painter &ctx) const override {
        int grid_offset = point.grid_offset();

        color color_mask = 0;
        bool drawn = false;
        int image_id = image_id_from_group(GROUP_TERRAIN_DESIRABILITY);
        if (map_terrain_is(grid_offset, terrain_on_routing_overlay()) && !map_terrain_is(grid_offset, TERRAIN_BUILDING) ) {
            drawn = true;
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), pixel, color_mask);
        }

        if (!drawn && map_terrain_is(grid_offset, TERRAIN_WATER)) {
             drawn = true;
            if (map_terrain_is(grid_offset, TERRAIN_FERRY_ROUTE)) {
                int offset = 4;
                ImageDraw::isometric_from_drawtile(ctx, image_id + offset, pixel, color_mask);
            } else if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
                int offset = 5;
                ImageDraw::isometric_from_drawtile(ctx, image_id + offset, pixel, color_mask);
            } else {
                ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), pixel, color_mask);
            }
        }
        
        if (!drawn) {
            if (map_terrain_is(grid_offset, TERRAIN_BUILDING) || map_terrain_is(grid_offset, TERRAIN_WATER)) {
                building *b = building_at(grid_offset);
                int offset = 2;

                if (b && !building_on_routing_overlay(b->type)) {
                    ImageDraw::isometric_from_drawtile(ctx, image_id + offset, pixel, color_mask);
                    drawn = true;
                }
            }
        }
        
        building *b = building_at(grid_offset);
        if (!drawn) {
            bool road = map_terrain_is(grid_offset, TERRAIN_ROAD);
            bool building_road = b && building_on_routing_overlay(b->type);

            if (road || building_road) {
                int offset = 5;
                drawn = true;
                ImageDraw::isometric_from_drawtile(ctx, image_id + offset, pixel, color_mask);
            }
        }

        if (!drawn) {
            ImageDraw::isometric_from_drawtile(ctx, map_image_at(grid_offset), pixel, color_mask);
        }
    }

    bool show_building(const building* b) const override {
        return /*b->type == BUILDING_FERRY ||*/ b->type == BUILDING_PLAZA || b->type == BUILDING_BOOTH;
    }
};

city_overlay_routing g_city_overlay_routing;

city_overlay* city_overlay_for_routing() {
    return &g_city_overlay_routing;
}
