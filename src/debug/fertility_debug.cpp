#include "app/app.h"
#include "dev/debug.h"

#include "grid/building.h"
#include "grid/canals.h"
#include "grid/floodplain.h"
#include "grid/terrain.h"

static void draw_grass_soil_depletion_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    int d = map_get_fertility(grid_offset, FERT_WITH_MALUS);
    if (!d)
        return;

    char str[64];
    const int x = pixel.x + 15;
    const int y = pixel.y;
    const int n = map_get_fertility(grid_offset, FERT_NO_MALUS);
    if (d == n || map_terrain_is(grid_offset, TERRAIN_MEADOW))
        debug_text(ctx, str, x, y + 5, 0, "", d, COLOR_LIGHT_GREEN);
    else {
        debug_text(ctx, str, x, y + 5, 0, "", d, COLOR_LIGHT_BLUE);
        d = map_get_fertility(grid_offset, FERT_ONLY_MALUS);
        debug_text(ctx, str, x, y + 15, 0, "", d, COLOR_LIGHT_RED);
    }
}

static void draw_grass_flood_flags_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    const int d = map_terrain_is(grid_offset, TERRAIN_BUILDING);
    const int x = pixel.x + 15;
    const int y = pixel.y;
    char str[64];

    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
            if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD))
                debug_text(ctx, str, x, y + 10, 0, "", d, 0xff777777);
            else if (map_building_at(grid_offset) > 0)
                debug_text(ctx, str, x, y + 10, 0, "", d, 0xff550000);
        } else {
            if (map_terrain_is(grid_offset, TERRAIN_ROAD))
                debug_text(ctx, str, x, y + 10, 0, "", d, 0xffffffff);
            else if (map_building_at(grid_offset) > 0)
                debug_text(ctx, str, x, y + 10, 0, "", d, 0xffaa0000);
        }
    }

    if (map_terrain_is(grid_offset, TERRAIN_CANAL)) {
        const int a = map_canal_at(grid_offset);
        if (map_terrain_is(grid_offset, TERRAIN_WATER))
            debug_text(ctx, str, x, y + 10, 0, "", a, 0xff557777);
        else
            debug_text(ctx, str, x, y + 10, 0, "", a, 0xff5577ff);
    } else if (map_terrain_is(grid_offset, TERRAIN_IRRIGATION_RANGE)) {
        if (map_terrain_is(grid_offset, TERRAIN_WATER))
            debug_text(ctx, str, x, y + 10, 0, "", d, 0xff007777);
        else
            debug_text(ctx, str, x, y + 10, 0, "", d, 0xff00ffff);
    }
}

void ANK_REGISTER_APPLICATION_MODULE(register_fertility_debug) {
    g_debug.add_tile_render_handler("grass_soil_depletion", draw_grass_soil_depletion_tile);
    g_debug.add_tile_render_handler("grass_flood_flags", draw_grass_flood_flags_tile);
}
