#include "building/building_physician.h"

#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_physician)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_physician);

void building_physician::update_month() {
    building_impl::update_month();
    runtime_data().residents_served_this_month = 0;
}
