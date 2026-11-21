#include "app/app.h"
#include "dev/debug.h"

#include "building/building.h"
#include "building/construction/build_planner.h"
#include "core/string.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"

static void draw_building_ids_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    const int x = pixel.x + 15;
    const int y = pixel.y;
    const int x0 = pixel.x + 8;
    char str[64];

    const int b_id = map_building_at(grid_offset);
    building *b = building_get(b_id);
    if (!b_id || !b) {
        return;
    }

    if (b->tile.grid_offset() == grid_offset) {
        ghost_draw::draw_building_ghost(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, {x - 15, y},
          COLOR_MASK_GREEN_30);
    }

    if (map_property_is_draw_tile(grid_offset)) {
        const bool red = !map_terrain_is(grid_offset, TERRAIN_BUILDING);
        debug_text(ctx, str, x0, y + 0, 0, "", b_id, red ? COLOR_LIGHT_RED : COLOR_WHITE);
        debug_text(ctx, str, x0, y + 10, 0, "", b->type, red ? COLOR_LIGHT_RED : COLOR_LIGHT_BLUE);
        if (!b->is_main()) {
            text_draw(ctx, (uint8_t *)string_from_ascii("sub"), x0, y - 10, FONT_SMALL_OUTLINED, COLOR_RED);
        }
    }
}

static void draw_tilesize_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    const int x = pixel.x + 15;
    const int y = pixel.y;
    const int x1 = pixel.x + 8 + 30;
    char str[64];

    if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        if (map_property_is_draw_tile(grid_offset)) {
            building *b = building_get(map_building_at(grid_offset));
            debug_text(ctx, str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_GREEN);
            if (b) {
                debug_text(ctx, str, x1, y + 10, 0, "", b->size, COLOR_WHITE);
            }
        } else {
            debug_text(ctx, str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_RED);
        }
    } else if (!map_property_is_draw_tile(grid_offset)) {
        debug_text(ctx, str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_BLUE);
    }
}

void ANK_REGISTER_APPLICATION_MODULE(register_building_ids_debug) {
    g_debug.add_tile_render_handler("building", draw_building_ids_tile);
    g_debug.add_tile_render_handler("tilesize", draw_tilesize_tile);
}
