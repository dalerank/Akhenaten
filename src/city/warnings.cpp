#include "warnings.h"

#include "building/building.h"
#include "building/count.h"
#include "building/model.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/city_population.h"
#include "city/city_resource.h"
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
    if (building_is_temple_complex(b->type)) {
        has_road =  map_has_road_access_temple_complex(tile, orientation, true, nullptr);
        if (!has_road) {
            building_construction_warning_show(WARNING_ROAD_ACCESS_NEEDED);
        }
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
    check_wall(type, tile.x(), tile.y(), size);

    check_road_access(b, tile, size, orientation);
    b->dcast()->on_place_checks();
}

