#include "building_jewels_workshop.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_jewels_workshop);

void building_jewels_workshop::update_animation() {
    building_industry::update_animation();
    if (base.stored_amount(RESOURCE_GEMS) < 100) {
        base.play_animation = false;
    }
}
