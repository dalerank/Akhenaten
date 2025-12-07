#include "city/city.h"

#include "core/profiler.h"
#include "grid/water.h"
#include "grid/moisture.h"
#include "grid/building.h"
#include "game/game_config.h"
#include "grid/canals.h"
#include "building/building_well.h"
#include "building/building_house.h"
#include "building/building_water_lift.h"

void city_buildings_t::mark_well_access(building *well) {
    int radius = 1;
    if (!!game_features::gameplay_change_well_radius_depends_moisture) {
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
        } else if (auto house = b.dcast_house(); !!house) {
            b.has_water_access = false;
            b.has_well_access = 0;
            if (b.dcast_house()->runtime_data().water_supply|| map_terrain_exists_tile_in_area_with_type(b.tile, b.size, TERRAIN_FOUNTAIN_RANGE)) {
                b.has_water_access = true;
            }
        }
    });

    for (const auto& w : wells) {
        mark_well_access(w);
    }
}

void city_buildings_t::update_canals_from_water_lifts() {
    OZZY_PROFILER_SECTION("Game/Update/Canals From Water Lifts");
    
    // do nothing
}