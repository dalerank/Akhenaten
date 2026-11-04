#include "building_bridge.h"

#include "building_ship_bridge.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "grid/bridge_grid.h"
#include "grid/property.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_low_bridge);

int bridge_span_max_length(bool is_ship_bridge) {
    if (is_ship_bridge) {
        const uint8_t v = building_ship_bridge::current_params().max_length;
        return v > 0 ? v : 40;
    }
    const uint8_t v = building_low_bridge::current_params().max_length;
    // OG BRIDGE_MAX_OPEN_WATER_TILES=4 → max total span 5 (start + 3 mid + end).
    return v > 0 ? v : 5;
}

int bridge_span_min_length(bool is_ship_bridge) {
    if (is_ship_bridge) {
        const uint8_t v = building_ship_bridge::current_params().min_length;
        return v > 0 ? v : 5;
    }
    const uint8_t v = building_low_bridge::current_params().min_length;
    return v > 0 ? v : 2;
}

static void enqueue_bridge_image(painter &ctx, int image_id, vec2i pixel, color color_mask) {
    auto &command = ImageDraw::create_command(ctx, render_command_t::ert_generic);
    command.image_id = image_id;
    command.pixel = pixel;
    command.mask = color_mask;
    command.scale = 1.f;
}

void city_draw_bridge(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    if (!map_terrain_is(grid_offset, TERRAIN_WATER)) {
        map_bridge_tile_clear(grid_offset);
        map_sprite_clear_tile(grid_offset);
        return;
    }
    if (map_terrain_is(grid_offset, TERRAIN_BUILDING))
        return;
    color color_mask = 0;
    if (map_property_is_deleted(grid_offset))
        color_mask = COLOR_MASK_RED;

    city_draw_bridge_tile(ctx, pixel.x, pixel.y, map_bridge_part_at(grid_offset), color_mask,
                          map_bridge_type_at(grid_offset));
}

void city_draw_bridge_tile(painter &ctx, int x, int y, int bridge_sprite_id, color color_mask, uint16_t bridge_type) {
    if (bridge_sprite_id >= 7) {
        city_draw_ship_bridge_tile(ctx, x, y, bridge_sprite_id, color_mask);
        return;
    }

    int img_offset = 0;
    vec2i pos;
    if (!bridge_style_part_draw(bridge_type, bridge_sprite_id, img_offset, pos)) {
        return;
    }

    const int image_id = bridge_style_image_base(bridge_type) + img_offset;
    enqueue_bridge_image(ctx, image_id, {x + pos.x, y + pos.y}, color_mask);
}
