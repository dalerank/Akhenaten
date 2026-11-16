#include "city/city.h"

#include "core/profiler.h"
#include "grid/water.h"
#include "grid/terrain.h"
#include "grid/canals.h"
#include "building/building_water_lift.h"
#include "city/city_floods.h"
#include "grid/floodplain.h"

#include <algorithm>

static void fill_canal_at(int /*is_flooding*/, int grid_offset, int /*row*/) {
    if (map_terrain_is(grid_offset, TERRAIN_CANAL) && !map_canal_is_filled(grid_offset)) {
        map_canal_fill_from_offset(tile2i(grid_offset));
    }
}

// OG floods_fill_canals. OG flood list L is floodplain row 29 - L here; progress 30 (no flood) falls back
// to the shore row, so a canal on the shore row is wet all year.
static void fill_canals_from_flood() {
    const int progress = std::clamp(g_floods.flood_progress, 0, MAX_FLOODPLAIN_ROWS);
    const int front_list = std::min(progress, MAX_FLOODPLAIN_ROWS - 1);
    foreach_floodplain_row(0, MAX_FLOODPLAIN_ROWS - 1 - front_list, fill_canal_at);
    for (int i = 1; i <= 2; i++) {
        if (progress + i >= MAX_FLOODPLAIN_ROWS) {
            continue;
        }
        foreach_floodplain_row(0, MAX_FLOODPLAIN_ROWS - 1 - (progress + i), fill_canal_at);
    }
}

// OG map_water_supply_update_reservoir_fountain, canal and lift half; every canal is recomputed from dry.
void city_buildings_t::update_water_supply() {
    OZZY_PROFILER_FUNCTION();

    map_canals_reset_water_supply();

    buildings_valid_do<building_water_lift>([](building_water_lift *lift) {
        lift->update_inout_tiles();
        const auto &d = lift->runtime_data();
        const bool river = map_terrain_is(d.input_tiles[0], TERRAIN_WATER)
            || map_terrain_is(d.input_tiles[1], TERRAIN_WATER);
        lift->base.has_water_access = river ? 2 : 0;
    });

    fill_canals_from_flood();
    pump_water_lifts_iterative();
    stamp_water_lift_irrigation();
}

void city_buildings_t::pump_water_lifts_iterative() {
    OZZY_PROFILER_FUNCTION();

    // OG do-while: lifts with has_water==2 and workers become 1 and fill canals
    // from the back; fill wakes adjacent dry lifts to 2 for the next round.
    bool changed = true;
    while (changed) {
        changed = false;
        buildings_valid_do<building_water_lift>([&](building_water_lift *lift) {
            if (lift->base.has_water_access != 2 || lift->num_workers() <= 0) {
                return;
            }

            lift->base.has_water_access = 1;
            changed = true;

            const auto &d = lift->runtime_data();
            map_canal_fill_from_offset(tile2i(d.output_tiles[0]));
            map_canal_fill_from_offset(tile2i(d.output_tiles[1]));
        });
    }
}

void city_buildings_t::stamp_water_lift_irrigation() {
    OZZY_PROFILER_FUNCTION();

    // OG: working lifts with water stamp IRRIGATION_RANGE size=2 radius=2.
    buildings_valid_do<building_water_lift>([](building_water_lift *lift) {
        if (lift->num_workers() <= 0 || !lift->base.has_water_access) {
            return;
        }

        const int radius = lift->current_params().irrigation_radius;
        map_add_irrigation_range(lift->tile(), lift->size(), radius);
    });
}
