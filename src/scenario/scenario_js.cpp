#include "scenario/scenario.h"

#include "building/building.h"
#include "building/building_storage_yard.h"
#include "building/building_type.h"
#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_resource.h"
#include "core/encoding.h"
#include "game/game_environment.h"
#include "game/resource.h"
#include "scenario/criteria.h"

#include "js/js_game.h"
#include "core/variant.h"

#include "core/profiler.h"
#include <algorithm>

ANK_GLOBAL_OBJECT(g_scenario, __scenario,
    start_year,
    climate,
    image_id,
    kingdom_supplies_grain,
    campaign_scenario_id,
    is_open_play,
    subtitle,
    scmode,
    player_rank,
    campaign_mission_rank,
    has_won,
    continue_months_left,
    continue_months_chosen,
    scenario_name
    );

ANK_GLOBAL_OBJECT(g_scenario.settings, __scenario_settings,
    starting_kingdom
    );

ANK_GLOBAL_OBJECT(g_scenario.map, __scenario_map,
    width,
    height
    );

ANK_GLOBAL_OBJECT(g_scenario.monuments, __scenario_monuments,
    first,
    second,
    third
    );

static int burial_yards_available(e_resource resource) {
    int total = 0;
    buildings_valid_do([&](building &b) {
        building_storage_yard *yard = b.dcast_storage_yard();
        if (yard && yard->is_valid()) {
            total += yard->amount(resource);
        }
    });
    return total;
}

int __scenario_burial_provisions_count() {
    int n = 0;
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; r++) {
        if (g_scenario.monuments.burial_provisions[r].required > 0) {
            n++;
        }
    }
    return n;
}
ANK_FUNCTION(__scenario_burial_provisions_count)

int __scenario_burial_provisions_resource_at(int index) {
    if (index < 0) {
        return RESOURCE_NONE;
    }
    int n = 0;
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; r++) {
        if (g_scenario.monuments.burial_provisions[r].required <= 0) {
            continue;
        }
        if (n == index) {
            return r;
        }
        n++;
    }
    return RESOURCE_NONE;
}
ANK_FUNCTION_1(__scenario_burial_provisions_resource_at)

int __scenario_burial_provisions_required(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    return g_scenario.monuments.burial_provisions[resource].required;
}
ANK_FUNCTION_1(__scenario_burial_provisions_required)

int __scenario_burial_provisions_dispatched(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    return g_scenario.monuments.burial_provisions[resource].dispatched;
}
ANK_FUNCTION_1(__scenario_burial_provisions_dispatched)

int __scenario_burial_provisions_remaining(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    const auto &bp = g_scenario.monuments.burial_provisions[resource];
    return std::max(0, bp.required - bp.dispatched);
}
ANK_FUNCTION_1(__scenario_burial_provisions_remaining)

bool __scenario_burial_provisions_complete() {
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; r++) {
        const auto &bp = g_scenario.monuments.burial_provisions[r];
        if (bp.dispatched < bp.required) {
            return false;
        }
    }
    return true;
}
ANK_FUNCTION(__scenario_burial_provisions_complete)

// Returns amount actually dispatched, or negative:
//   -1 not enough goods in storage yards
//   -2 commodity already fulfilled / nothing required
//   -3 invalid args
int __scenario_burial_provisions_dispatch(int resource, int amount) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || amount <= 0) {
        return -3;
    }
    auto &bp = g_scenario.monuments.burial_provisions[resource];
    const int remaining = bp.required - bp.dispatched;
    if (remaining <= 0) {
        return -2;
    }

    const e_resource res = static_cast<e_resource>(resource);
    const int available = burial_yards_available(res);
    if (available <= 0) {
        return -1;
    }

    const int take = std::min({amount, remaining, available});
    event_storageyards_remove_resource ev{res, take, /*staffed_only*/ false};
    city_storageyards_remove_resource(ev);
    const int removed = take - ev.amount;
    if (removed <= 0) {
        return -1;
    }

    // City counter = win/UI SoT; tomb ledger gets the stealable stock (prefer emptiest).
    if (building *tomb = burial_provisions_pick_dispatch_tomb()) {
        if (auto *m = tomb->dcast_monument()) {
            m->add_burial_stock(res, removed);
        }
    }
    bp.dispatched += removed;
    city_resource().calculate_stocks();
    return removed;
}
ANK_FUNCTION_2(__scenario_burial_provisions_dispatch)

int __scenario_criteria_max_year() {
    return scenario_criteria_max_year();
}
ANK_FUNCTION(__scenario_criteria_max_year)

xstring __scenario_event_msg_text(int title_id, int index) {
    return g_scenario.events.msg_text(title_id, index);
}
ANK_FUNCTION_2(__scenario_event_msg_text)

bool __scenario_building_allowed(int btype) {
    return scenario_building_allowed((e_building_type)btype);
}
ANK_FUNCTION_1(__scenario_building_allowed)

void __scenario_building_allow(int type, bool enabled) {
    scenario_building_allow((e_building_type)type, enabled);
}
ANK_FUNCTION_2(__scenario_building_allow)

bvariant_map __scenario_vars() {
    bvariant_map result;
    g_scenario.vars.foreach_vars([&](xstring name, const setting_variant &var) {
        switch (var.index()) {
        case setting_bool:
            result[name] = bvariant(std::get<bool>(var));
            break;
        case setting_float:
            result[name] = bvariant(std::get<float>(var));
            break;
        case setting_vec2i:
            result[name] = bvariant(std::get<vec2i>(var));
            break;
        case setting_string:
            result[name] = bvariant(std::get<xstring>(var));
            break;
        default:
            break;
        }
    });
    return result;
}
ANK_FUNCTION(__scenario_vars)


