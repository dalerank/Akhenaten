#include "app/app.h"
#include "dev/debug.h"

#include "building/building.h"
#include "building/construction/build_planner.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/road_network.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"

static void draw_roads_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    const int x = pixel.x + 15;
    const int y = pixel.y;
    const int x0 = pixel.x + 8;
    char str[64];

    const int b_id = map_building_at(grid_offset);
    building *b = building_get(b_id);
    if (b_id && b && map_property_is_draw_tile(grid_offset)) {
        debug_text(ctx, str, x0, y + 5, 0, "", b->road_access.x(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
        debug_text(ctx, str, x0, y + 15, 0, "", b->road_access.y(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
        if (b->has_road_access) {
            auto tile_coords = g_camera.lookup_tile_to_pixel(b->road_access);
            ghost_draw::draw_building_ghost(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, tile_coords,
              COLOR_MASK_GREEN);
        }
    }

    if (map_terrain_is(grid_offset, TERRAIN_ROAD) || map_terrain_is(grid_offset, TERRAIN_FERRY_ROUTE)) {
        const int d = map_road_network_get(grid_offset);
        debug_text(ctx, str, x, y + 10, 10, "R", d, COLOR_WHITE);
    } else if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD)) {
        const int d = map_road_network_get(grid_offset);
        debug_text(ctx, str, x, y + 10, 10, "R", d, COLOR_LIGHT_BLUE);
    }
}

static void draw_routing_value_tile(vec2i pixel, tile2i point, painter &ctx, int value, bool positive_only) {
    char str[64];
    const bool ok = positive_only ? (value > 0) : (value >= 0);
    debug_text(ctx, str, pixel.x + 15, pixel.y + 10, 0, "", value, ok ? COLOR_WHITE : COLOR_LIGHT_RED);
}

static void draw_routing_dist_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_routing_value_tile(pixel, point, ctx, map_routing_distance(point.grid_offset()), true);
}

static void draw_routing_grid_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_routing_value_tile(pixel, point, ctx, map_citizen_grid(point.grid_offset()), false);
}

static void draw_routing_noncitizen_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_routing_value_tile(pixel, point, ctx, map_noncitizen_grid(point.grid_offset()), false);
}

static void draw_routing_amphibia_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_routing_value_tile(pixel, point, ctx, map_amphibia_grid(point.grid_offset()), false);
}

static void draw_routing_water_tile(vec2i pixel, tile2i point, painter &ctx) {
    draw_routing_value_tile(pixel, point, ctx, map_water_grid(point.grid_offset()), false);
}

void ANK_REGISTER_APPLICATION_MODULE(register_roads_debug) {
    g_debug.add_tile_render_handler("roads", draw_roads_tile);
    g_debug.add_tile_render_handler("routing_dist", draw_routing_dist_tile);
    g_debug.add_tile_render_handler("routing_grid", draw_routing_grid_tile);
    g_debug.add_tile_render_handler("routing_noncitizen", draw_routing_noncitizen_tile);
    g_debug.add_tile_render_handler("routing_amphibia", draw_routing_amphibia_tile);
    g_debug.add_tile_render_handler("routing_water", draw_routing_water_tile);
}
