#include "city_warnings.h"

#include "building/building.h"
#include "building/count.h"
#include "building/model.h"
#include "city/constants.h"
#include "city/city.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "city/buildings.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "scenario/scenario.h"
#include "game/settings.h"

city_warning_manager g_warning_manager;

#define MAX_WARNINGS 5
#define TIMEOUT_MS 15000

city_warning_manager::warning* city_warning_manager::new_warning() {
    if (warnings.full()) {
        return nullptr;
    }
        
    warnings.push_back({});
    return &warnings.back();
}

bool city_warning_manager::has_warnings() {
    return !warnings.empty();
}

pcstr city_warning_manager::get_warning(int id) {
    if (id < warnings.size())
        return warnings[id].text.c_str();

    return "";
}

void city_warning_manager::clear_all() {
    warnings.clear();
}

void city_warning_manager::clear_outdated() {
    std::erase_if(warnings, [] (const warning &w) {
        return time_get_millis() - w.time > TIMEOUT_MS;
    });
}

void city_warning_manager::show_console(pcstr warning_text) {
    warning *w = new_warning();
    if (!w) {
        return;
    }

    w->time = time_get_millis();
    w->text = warning_text;
}

void city_warning_manager::init() {
    has_warning = false;

    events::subscribe([this] (event_construction_warning ev) {
        show(ev.id.c_str());
    });

    events::subscribe([this] (event_city_warning ev) {
        show(ev.id.c_str());
    });
}

void city_warning_manager::show_custom(pcstr text) {
    if (!g_settings.warnings) {
        return;
    }

    warning *w = new_warning();
    if (!w) {
        return;
    }

    w->time = time_get_millis();
    w->text = text;
}

void city_warning_manager::show(pcstr type) {
    xstring text = lang_text_from_key(type);
    show_custom(text.c_str());
}

construction_warnings::~construction_warnings() {
    for (const xstring &id : warnings) {
        //g_warning_manager.has_warning = false;
        events::emit(event_construction_warning{ id });
    }
}
