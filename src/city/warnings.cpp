#include "warnings.h"

#include "building/building.h"
#include "building/count.h"
#include "building/model.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/population.h"
#include "city/resource.h"
#include "city/warning.h"
#include "city/buildings.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"

bool g_has_warning = false;

void building_construction_warning_reset() {
    g_has_warning = false;
}

bool building_construction_has_warning() {
    return g_has_warning;
}

void building_construction_warning_show(int warning) {
    city_warning_show(warning);
    g_has_warning = true;
}

static void check_road_access(building *b, tile2i tile, int size, int orientation) {
    bool has_road = false;
    if (building_is_large_temple(b->type)) {
        has_road =  map_has_road_access_temple_complex(tile, orientation, true, nullptr);
        if (!has_road) {
            building_construction_warning_show(WARNING_ROAD_ACCESS_NEEDED);
        }
    }
}

static void check_water(int type, int x, int y) {
    if (!g_has_warning) {
        if (type == BUILDING_MENU_BEAUTIFICATION || type == BUILDING_MENU_MONUMENTS) {
            int grid_offset = MAP_OFFSET(x, y);
            int has_water = 0;
            if (map_terrain_is(grid_offset, TERRAIN_GROUNDWATER))
                has_water = 1;
            else if (type == BUILDING_MENU_MONUMENTS) {
                if (map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_GROUNDWATER)
                    || map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_GROUNDWATER)
                    || map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_GROUNDWATER)) {
                    has_water = 1;
                }
            }
            if (!has_water)
                building_construction_warning_show(WARNING_WATER_PIPE_ACCESS_NEEDED);
        }
    }
}

static void check_weapons_access(int type) {
    if (!g_has_warning && type == BUILDING_RECRUITER) {
        if (city_resource_count(RESOURCE_WEAPONS) <= 0)
            building_construction_warning_show(WARNING_WEAPONS_NEEDED);
    }
}

static void check_wall(int type, int x, int y, int size) {
    if (!g_has_warning && type == BUILDING_MUD_TOWER) {
        if (!map_terrain_is_adjacent_to_wall(x, y, size))
            building_construction_warning_show(WARNING_SENTRIES_NEED_WALL);
    }
}

void building_construction_warning_generic_checks(building *b, tile2i tile, int size, int orientation) {
    if (!b) {
        return;
    }

    e_building_type type = b->type;
    building_construction_warning_check_food_stocks(type);

    check_weapons_access(type);

    check_wall(type, tile.x(), tile.y(), size);
    check_water(type, tile.x(), tile.y());

    check_road_access(b, tile, size, orientation);
    b->dcast()->on_place_checks();
}

void building_construction_warning_check_food_stocks(int type) {
    if (!g_has_warning && type == BUILDING_HOUSE_VACANT_LOT) {
        if (city_population() >= 200 && !scenario_property_kingdom_supplies_grain()) {
            if (city_resource_food_percentage_produced() <= 95)
                building_construction_warning_show(WARNING_MORE_FOOD_NEEDED);
        }
    }
}

