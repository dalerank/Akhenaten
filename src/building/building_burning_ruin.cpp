#include "building_burning_ruin.h"

#include "game/undo.h"
#include "city/labor.h"
#include "core/random.h"
#include "grid/building_tiles.h"
#include "building/maintenance.h"
#include "building/destruction.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "scenario/scenario.h"
#include "js/js_game.h"
#include "grid/road_access.h"

buildings::model_t<building_burning_ruin> burning_ruin_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_burning_ruin);
void config_load_building_burning_ruin() {
    burning_ruin_m.load();
}

tile2i building_burning_ruin::can_be_accessed() {
    int base_offset = tile().grid_offset();
    offsets_array offsets;
    map_grid_adjacent_offsets(1, offsets);
    for (const auto &tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;

        if (road_tile_valid_access(grid_offset)
            || (building_at(grid_offset)->type == BUILDING_BURNING_RUIN
            && building_at(grid_offset)->fire_duration <= 0)) {
            return tile2i(grid_offset);
        }
    }

    return tile2i::invalid;
}

bool building_burning_ruin::update() {
    if (base.fire_duration < 0) {
        base.fire_duration = 0;
    }

    base.fire_duration++;
    if (base.fire_duration > 32) {
        game_undo_disable();
        base.state = BUILDING_STATE_RUBBLE;
        map_building_tiles_set_rubble(id(), tile(), size());
        return true;
    }

    if (base.has_plague) {
        return false;
    }

    int climate = scenario_property_climate();
    if (climate == CLIMATE_DESERT) {
        if (base.fire_duration & 3) { // check spread every 4 ticks
            return false;
        }
    } else {
        if (base.fire_duration & 7) { // check spread every 8 ticks
            return false;
        }
    }

    if ((base.map_random_7bit & 3) != (random_byte() & 3)) {
        return false;
    }

    int fire_spread_direction = building_maintenance_fire_direction();
    int dir1 = ((fire_spread_direction - 1) + 8) % 8;
    int dir2 = (fire_spread_direction + 1) % 8;

    int directions[] = {fire_spread_direction, dir1, dir2};
    for (const auto &dir : directions) {
        int grid_offset = tile().grid_offset();
        int next_building_id = map_building_at(grid_offset + map_grid_direction_delta(dir));
        if (next_building_id && !building_get(next_building_id)->fire_proof) {
            building_destroy_by_fire(building_get(next_building_id));
            return true;
        }
    }

    return false;
}
