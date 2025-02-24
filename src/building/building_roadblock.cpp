#include "building_roadblock.h"

#include "building/building_roadblock.h"

#include "city/labor.h"
#include "graphics/elements/ui.h"
#include "graphics/window.h"
#include "window/building/common.h"
#include "window/window_building_info.h"

buildings::model_t<building_roadblock> roadblock_m;

void building_roadblock::on_place_checks() {
    /*nothing*/
}

bool building_roadblock::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    /*nothing*/
    return true;
}

void building_roadblock::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT8, &data.roadblock.exceptions);
}

void building_roadblock::set_permission(e_permission p) {
    const int permission_bit = 1 << p;
    data.roadblock.exceptions ^= permission_bit;
}

bool building_roadblock::get_permission(e_permission p) {
    const int permission_bit = 1 << p;
    return (data.roadblock.exceptions & permission_bit);
}
