#include "building_jewels_workshop.h"

#include "js/js_game.h"
#include "game/game_config.h"
#include "grid/building.h"
#include "grid/grid.h"
#include <set>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_jewels_workshop);

void building_jewels_workshop::update_animation() {
    building_industry::update_animation();
    if (base.stored_amount(RESOURCE_GEMS) < 100) {
        base.play_animation = false;
    }
}

int building_jewels_workshop::count_nearby_workshops() const {
    std::set<building_id> nearby_workshop_ids;
    const building_id current_main_id = base.main()->id;

    grid_tiles_sm adjacent_tiles = map_grid_get_adjacent_tiles_sm(&base, 1);
    for (const auto& tile : adjacent_tiles) {
        building_id bid = map_building_at(tile);
        if (bid > 0) {
            building* b = building_get(bid);
            if (b && b->state == BUILDING_STATE_VALID) {
                building* main_b = b->main();
                if (main_b && main_b->type == BUILDING_JEWELS_WORKSHOP && main_b->id != current_main_id) {
                    nearby_workshop_ids.insert(main_b->id);
                }
            }
        }
    }

    return nearby_workshop_ids.size();
}

short building_jewels_workshop::og_input_consumed(e_resource r) const {
    const short load = building_industry::og_input_consumed(r);
    if (!game_features::gameplay_change_jeweler_nearby_discount) {
        return load;
    }

    const int reduction = count_nearby_workshops() * current_params().material_reduction_per_nearby_workshop;
    return (short)std::max(load - reduction, 50);
}
