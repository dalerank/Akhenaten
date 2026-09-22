#include "building_quarry.h"

#include "js/js_game.h"
#include "grid/sandstone.h"
#include "grid/stone.h"
#include "grid/limestone.h"
#include "grid/granite.h"
#include "grid/grid.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_sandstone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_stone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_limestone_quarry);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_granite_quarry);

void building_sandstone_quarry::update_production() {
    update_production_with_resource_depletion(
        [](tile2i t) { return map_get_sandstone(t); },
        [](tile2i t, int amount) { map_sandstone_deplete(t, amount); }
    );
}

void building_stone_quarry::update_production() {
    update_production_with_resource_depletion(
        [](tile2i t) { return map_get_stone(t); },
        [](tile2i t, int amount) { map_stone_deplete(t, amount); }
    );
}

void building_stone_quarry::update_day() {
    building_quarry::update_day();

    base.anims[work_2] = anim(worker_percentage() > 50 ? animkeys().work_2 : animkeys().none);
}

void building_limestone_quarry::update_production() {
    update_production_with_resource_depletion(
        [](tile2i t) { return map_get_limestone(t); },
        [](tile2i t, int amount) { map_limestone_deplete(t, amount); }
    );
}

void building_granite_quarry::update_production() {
    update_production_with_resource_depletion(
        [](tile2i t) { return map_get_granite(t); },
        [](tile2i t, int amount) { map_granite_deplete(t, amount); }
    );
}
