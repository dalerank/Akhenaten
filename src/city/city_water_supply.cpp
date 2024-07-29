#include "city/city.h"

#include "core/profiler.h"
#include "grid/water.h"
#include "grid/moisture.h"
#include "grid/building.h"
#include "config/config.h"
#include "grid/canals.h"
#include "building/building_well.h"

void city_buildings_t::mark_well_access(building *well) {
    int radius = 1;
    if (config_get(CONFIG_GP_CH_WELL_RADIUS_DEPENDS_MOISTURE)) {
        radius = (map_moisture_get(well->tile.grid_offset()) / 40);
        radius = std::clamp(radius, 1, 4);
    }

    grid_area area = map_grid_get_area(well->tile, 1, radius);

    map_grid_area_foreach(area.tmin, area.tmax, [] (tile2i tile) {
        int building_id = map_building_at(tile.grid_offset());

        if (building_id) {
            building_get(building_id)->has_well_access = true;
        }

        map_terrain_add(tile.grid_offset(), TERRAIN_FOUNTAIN_RANGE);
    });
}

void city_buildings_t::update_wells_range() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Wells Range Update");
    map_terrain_remove_all(TERRAIN_FOUNTAIN_RANGE);
    buildings_valid_do<building_well>([](building_well *b) {
        map_terrain_add_with_radius(b->tile(), 1, 3, TERRAIN_FOUNTAIN_RANGE);
    });
}

void city_buildings_t::update_water_supply_houses() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Well Access Update");
    svector<building *, 512> wells;
    buildings_valid_do([&] (building &b) {
        if (b.type == BUILDING_WELL) {
            wells.push_back(&b);
        } else if (b.house_size) {
            b.has_water_access = false;
            b.has_well_access = 0;
            if (b.data.house.water_supply|| map_terrain_exists_tile_in_area_with_type(b.tile, b.size, TERRAIN_FOUNTAIN_RANGE)) {
                b.has_water_access = true;
            }
        }
    });

    for (const auto& w : wells) {
        mark_well_access(w);
    }
}

void city_buildings_t::update_canals_from_water_lifts() {
    // cached grid offsets for water lift outputs
    const int OUTPUT_OFFSETS[4][2] = {{GRID_OFFSET(0, 2), GRID_OFFSET(1, 2)},
                                      {GRID_OFFSET(-1, 0), GRID_OFFSET(-1, 1)},
                                      {GRID_OFFSET(0, -1), GRID_OFFSET(1, -1)},
                                      {GRID_OFFSET(2, 0), GRID_OFFSET(2, 1)}};
    const int INPUT_OFFSETS[4][2] = {{GRID_OFFSET(0, -1), GRID_OFFSET(1, -1)},
                                     {GRID_OFFSET(2, 0), GRID_OFFSET(2, 1)},
                                     {GRID_OFFSET(0, 2), GRID_OFFSET(1, 2)},
                                     {GRID_OFFSET(-1, 0), GRID_OFFSET(-1, 1)}};

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_WATER_LIFT) {
            // check if has access to water
            b->has_water_access = false;
            int input_offset_0 = b->tile.grid_offset() + INPUT_OFFSETS[b->data.industry.orientation][0];
            int input_offset_1 = b->tile.grid_offset() + INPUT_OFFSETS[b->data.industry.orientation][1];
            if (map_canal_at(input_offset_0) || map_terrain_is(input_offset_0, TERRAIN_WATER))
                b->has_water_access = true;

            if (map_canal_at(input_offset_1) || map_terrain_is(input_offset_1, TERRAIN_WATER))
                b->has_water_access = true;

            // checks done, update
            if (b->has_water_access) {
                map_canal_fill_from_offset(b->tile.grid_offset() + OUTPUT_OFFSETS[b->data.industry.orientation][0]);
                map_canal_fill_from_offset(b->tile.grid_offset() + OUTPUT_OFFSETS[b->data.industry.orientation][1]);
                map_terrain_add_with_radius(b->tile, 2, 2, TERRAIN_IRRIGATION_RANGE);
            }
        }
    }
}