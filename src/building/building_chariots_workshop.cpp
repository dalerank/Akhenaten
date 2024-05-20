#include "building_chariots_workshop.h"

#include "building/count.h"

void building_chariots_workshop::on_create(int orientation) {
    data.industry.first_material_id = RESOURCE_TIMBER;
    data.industry.second_material_id = RESOURCE_WEAPONS;
    base.output_resource_first_id = RESOURCE_CHARIOTS;
}

void building_chariots_workshop::update_count() const {
    building_increase_industry_count(RESOURCE_CHARIOTS, num_workers() > 0);
}

bool building_chariots_workshop::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    return true;
}
