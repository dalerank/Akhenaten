#include "building_library.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_library)

bool building_library::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    draw_normal_anim(ctx, point, tile, mask);
    return true;
}
