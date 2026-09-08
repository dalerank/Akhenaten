#include "building_well.h"

#include "grid/water_supply.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_well);

void building_well::update_animation() {
    const e_well_status status = map_water_supply_is_well_unnecessary(id(), current_params().unnecessary_range_check);
    base.play_animation = (status == WELL_NECESSARY);
    es(__func__);
}
