#include "building_roadblock.h"

#include "building/building_roadblock.h"

#include "graphics/elements/ui.h"
#include "graphics/window.h"
#include "window/building/common.h"
#include "window/window_building_info.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_roadblock);

void building_roadblock::on_place_checks() {
    /*nothing*/
}

bool building_roadblock::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    /*nothing*/
    return true;
}

bool building_roadblock::force_draw_top_tile(painter& ctx, tile2i tile, vec2i pixel, color mask) {
    return false;
}

void building_roadblock::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT8, &d.exceptions);
}

void building_roadblock::set_permission(e_permission p) {
    const int permission_bit = 1 << p;
    runtime_data().exceptions ^= permission_bit;
}

bool building_roadblock::get_permission(e_permission p) {
    const int permission_bit = 1 << p;
    return (runtime_data().exceptions & permission_bit);
}
