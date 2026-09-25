#include "building_roadblock.h"

#include "graphics/elements/ui.h"
#include "graphics/window.h"
#include "window/building/common.h"
#include "window/window_building_info.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_roadblock);

bool building_roadblock::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    /*nothing*/
    return true;
}

bool building_roadblock::force_draw_top_tile(painter& ctx, tile2i tile, vec2i pixel, color mask) {
    return false;
}

void building_roadblock::set_permission(e_permission p) {
    const uint32_t permission_bit = 1u << p;
    base.exceptions ^= permission_bit;
}

bool building_roadblock::get_permission(e_permission p) {
    const uint32_t permission_bit = 1u << p;
    return (base.exceptions & permission_bit) != 0;
}

bool building_roadblock::target_route_tile_blocked(int grid_offset) const {
    return false;
}
