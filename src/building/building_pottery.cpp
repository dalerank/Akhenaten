#include "building/building_pottery.h"

#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_pottery);

void building_pottery::update_animation() {
    building_industry::update_animation();
    auto &d = runtime_data();
    if (base.stored_amount(RESOURCE_POTTERY) < 100 && d.progress == 0) {
        base.play_animation = false;
    }
}