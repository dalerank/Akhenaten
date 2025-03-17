#include "city_warnings.h"

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

city_warning_manager g_warning_manager;

void city_warning_manager::init() {
    has_warning = false;

    g_city_events.subscribe([this] (event_construction_warning ev) {
        city_warning_show(ev.id.c_str());
        //has_warning = true;
    });
}

void building_construction_check_road_access(building *b, tile2i tile, int size, int orientation) {
    if (!building_is_temple_complex(b->type)) {
        return;
    }

    const bool has_road =  map_has_road_access_temple_complex(tile, orientation, true, nullptr);
    if (!has_road) {
        g_city_events.enqueue(event_construction_warning{ "#needs_road_access" });
    }
}

void building_construction_check_wall(int type, int x, int y, int size) {
    if (!g_warning_manager.has_warning && type == BUILDING_MUD_TOWER) {
        if (!map_terrain_is_adjacent_to_wall(x, y, size)) {
            g_city_events.enqueue(event_construction_warning{ "#must_be_next_to_wall_for_patrol" });
        }
    }
}

void building_construction_warning_generic_checks(building *b, tile2i tile, int size, int orientation) {
    if (!b) {
        return;
    }

    e_building_type type = b->type;
    building_construction_check_wall(type, tile.x(), tile.y(), size);

    building_construction_check_road_access(b, tile, size, orientation);
    b->dcast()->on_place_checks();
}

construction_warnings::~construction_warnings() {
    for (const xstring &id : warnings) {
        //g_warning_manager.has_warning = false;
        g_city_events.enqueue(event_construction_warning{ id });
    }
}
