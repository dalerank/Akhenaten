#include "city/city.h"

#include "core/profiler.h"
#include "grid/water.h"
#include "grid/terrain.h"
#include "grid/canals.h"
#include "building/building_water_lift.h"

void city_buildings_t::update_canals_from_water_lifts() {
    OZZY_PROFILER_FUNCTION();

    // OG: each lift starts at has_water 2 (river intake) or 0.
    buildings_valid_do<building_water_lift>([](building_water_lift *lift) {
        lift->update_inout_tiles();
        const auto &d = lift->runtime_data();
        const bool river = map_terrain_is(d.input_tiles[0], TERRAIN_WATER)
            || map_terrain_is(d.input_tiles[1], TERRAIN_WATER);
        lift->base.has_water_access = river ? 2 : 0;
    });

    pump_water_lifts_iterative();
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
            const int fill_level = lift->current_params().canal_fill_water_level;
            if (map_terrain_is(d.output_tiles[0], TERRAIN_CANAL)) {
                map_canal_fill_from_offset(tile2i(d.output_tiles[0]), fill_level);
            }
            if (map_terrain_is(d.output_tiles[1], TERRAIN_CANAL)) {
                map_canal_fill_from_offset(tile2i(d.output_tiles[1]), fill_level);
            }
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
