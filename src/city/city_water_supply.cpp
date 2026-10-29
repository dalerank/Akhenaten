#include "city/city.h"

#include "core/profiler.h"
#include "grid/water.h"
#include "grid/moisture.h"
#include "grid/building.h"
#include "grid/terrain.h"
#include "game/game_config.h"
#include "grid/canals.h"
#include "building/building_house.h"
#include "building/building_water_lift.h"

void city_buildings_t::mark_well_access(building *well) {
    int radius = 1;
    if (!!game_features::gameplay_change_well_radius_depends_moisture) {
        radius = (map_moisture_get(well->tile.grid_offset()) / 40);
        radius = std::clamp(radius, 1, 4);
    }

    grid_area area = map_grid_get_area(well->tile, 1, radius);

    map_grid_area_foreach(area, [] (tile2i tile) {
        int building_id = map_building_at(tile.grid_offset());

        if (building_id) {
            building_get(building_id)->has_well_access = true;
        }

        map_terrain_add(tile.grid_offset(), TERRAIN_FOUNTAIN_RANGE);
    });
}

void city_buildings_t::update_wells_range() {
    OZZY_PROFILER_FUNCTION();
    map_terrain_remove_all(TERRAIN_FOUNTAIN_RANGE);
    buildings_valid_do([](building &b) {
        map_terrain_add_with_radius(b.tile, 1, 3, TERRAIN_FOUNTAIN_RANGE);
    }, BUILDING_WELL);
}

void city_buildings_t::update_water_supply_houses() {
    OZZY_PROFILER_FUNCTION();
    svector<building *, 512> wells;
    buildings_valid_do([&] (building &b) {
        if (b.type == BUILDING_WELL) {
            wells.push_back(&b);
            b.has_water_access = map_terrain_exists_tile_in_area_with_type(b.tile, b.size, TERRAIN_GROUNDWATER);
        } else if (b.type == BUILDING_WATER_SUPPLY) {
            b.has_water_access = map_terrain_exists_tile_in_area_with_type(b.tile, b.size, TERRAIN_GROUNDWATER);
        } else if (auto house = b.dcast_house(); !!house) {
            b.has_water_access = false;
            b.has_well_access = 0;
            if (b.dcast_house()->runtime_data().water_supply
                || map_terrain_exists_tile_in_area_with_type(b.tile, b.size, TERRAIN_FOUNTAIN_RANGE)) {
                b.has_water_access = true;
            }
        }
    });

    for (const auto& w : wells) {
        mark_well_access(w);
    }
}

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
