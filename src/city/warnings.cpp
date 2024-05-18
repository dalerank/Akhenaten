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

static void check_barracks(int type) {
    if (!g_has_warning) {
        if (building_is_fort(type) && building_count_active(BUILDING_RECRUITER) <= 0)
            building_construction_warning_show(WARNING_BUILD_BARRACKS);
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

static void check_musician_access(int type) {
    if (!g_has_warning && type == BUILDING_BANDSTAND) {
        if (building_count_active(BUILDING_CONSERVATORY) <= 0)
            building_construction_warning_show(WARNING_BUILD_GLADIATOR_SCHOOL);
    }
}

static void check_dancers_access(int type) {
    if (!g_has_warning && type == BUILDING_PAVILLION) {
        if (building_count_active(BUILDING_DANCE_SCHOOL) <= 0)
            building_construction_warning_show(WARNING_BUILD_DANCERS_SCHOOL);
    }
}

static void check_olives_access(int type) {
    if (type == BUILDING_WEAVER_WORKSHOP && building_count_industry_active(RESOURCE_STRAW) <= 0) {
        if (city_resource_count(RESOURCE_MEAT) <= 0 && city_resource_count(RESOURCE_STRAW) <= 0) {
            building_construction_warning_show(WARNING_OLIVES_NEEDED);
            if (empire_can_produce_resource(RESOURCE_STRAW, true))
                building_construction_warning_show(WARNING_BUILD_OLIVE_FARM);
            else if (!empire_can_import_resource(RESOURCE_STRAW, true))
                building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
            else if (city_resource_trade_status(RESOURCE_STRAW) != TRADE_STATUS_IMPORT)
                building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
        }
    }
}

static void check_timber_access(int type) {
    if (type == BUILDING_JEWELS_WORKSHOP && building_count_industry_active(RESOURCE_GEMS) <= 0) {
        if (city_resource_count(RESOURCE_LUXURY_GOODS) <= 0 && city_resource_count(RESOURCE_GEMS) <= 0) {
            building_construction_warning_show(WARNING_TIMBER_NEEDED);
            if (empire_can_produce_resource(RESOURCE_GEMS, true))
                building_construction_warning_show(WARNING_BUILD_TIMBER_YARD);
            else if (!empire_can_import_resource(RESOURCE_GEMS, true))
                building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
            else if (city_resource_trade_status(RESOURCE_GEMS) != TRADE_STATUS_IMPORT)
                building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
        }
    }
}

static void check_clay_access(int type) {
    if (type == BUILDING_POTTERY_WORKSHOP && building_count_industry_active(RESOURCE_CLAY) <= 0) {
        if (city_resource_count(RESOURCE_POTTERY) <= 0 && city_resource_count(RESOURCE_CLAY) <= 0) {
            building_construction_warning_show(WARNING_CLAY_NEEDED);
            if (empire_can_produce_resource(RESOURCE_CLAY, true))
                building_construction_warning_show(WARNING_BUILD_CLAY_PIT);
            else if (!empire_can_import_resource(RESOURCE_CLAY, true))
                building_construction_warning_show(WARNING_OPEN_TRADE_TO_IMPORT);
            else if (city_resource_trade_status(RESOURCE_CLAY) != TRADE_STATUS_IMPORT)
                building_construction_warning_show(WARNING_TRADE_IMPORT_RESOURCE);
        }
    }
}

void building_construction_warning_generic_checks(building *b, tile2i tile, int size, int orientation) {
    if (!b) {
        return;
    }

    e_building_type type = b->type;
    building_construction_warning_check_food_stocks(type);
    check_musician_access(type);
    check_dancers_access(type);

    check_barracks(type);
    check_weapons_access(type);

    check_wall(type, tile.x(), tile.y(), size);
    check_water(type, tile.x(), tile.y());

    check_olives_access(type);
    check_timber_access(type);
    check_clay_access(type);

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

void building_construction_warning_check_reservoir(int type) {
    if (!g_has_warning && type == BUILDING_WATER_LIFT) {
        if (building_count_active(BUILDING_WATER_LIFT))
            building_construction_warning_show(WARNING_CONNECT_TO_RESERVOIR);
        else
            building_construction_warning_show(WARNING_PLACE_RESERVOIR_NEXT_TO_WATER);
    }
}
