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

construction_warnings::~construction_warnings() {
    for (const xstring &id : warnings) {
        //g_warning_manager.has_warning = false;
        g_city_events.enqueue(event_construction_warning{ id });
    }
}
