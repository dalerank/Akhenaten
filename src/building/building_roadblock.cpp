#include "building_roadblock.h"

void building_roadblock_set_permission(int p, building* b) {
    if (b->type == BUILDING_ROADBLOCK) {
        int permission_bit = 1 << p;
        b->subtype.roadblock_exceptions ^= permission_bit;
    }
}

int building_roadblock_get_permission(int p, building* b) {
    if (b->type != BUILDING_ROADBLOCK)
        return 0;

    int permission_bit = 1 << p;
    return (b->subtype.roadblock_exceptions & permission_bit);
}

void building_roadblock::on_place_checks() {
    /*nothing*/
}

bool building_roadblock::force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) {
    /*nothing*/
    return true;
}
