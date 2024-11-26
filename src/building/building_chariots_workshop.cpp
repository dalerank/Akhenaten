#include "building_chariots_workshop.h"

#include "building/count.h"
#include "js/js_game.h"
#include "city/labor.h"

buildings::model_t<building_chariots_workshop> chariots_workshop_m;

void building_chariots_workshop::update_count() const {
    building_increase_industry_count(RESOURCE_CHARIOTS, num_workers() > 0);
}

bool building_chariots_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    return true;
}
