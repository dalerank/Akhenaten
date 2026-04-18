#include "game/game_events.h"
#include "city/city_maintenance.h"
#include "city/city_finance.h"
#include "js/js_events.h"

#include "game/mission.h"
#include "building/building_granary.h"
#include "building/building_storage_yard.h"
#include "city/city_migration.h"
#include "city/city_health.h"
#include "city/city_festival.h"
#include "city/city_resource.h"
#include "scenario/scenario.h"
#include "city/victory.h"
#include "city/city_animals.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "building/building_palace.h"
#include "content/mods.h"
#include "game/game.h"
#include "js/js_game.h"

#include <cmath>
#include <type_traits>
#include <unordered_map>

static std::unordered_map<xstring, js_script_emit_handler> g_script_emit_handlers;

void js_register_script_emit_handler(pcstr event_name, js_script_emit_handler handler) {
    if (!event_name || !handler) {
        return;
    }

    g_script_emit_handlers[event_name] = handler;
}

ANK_SCRIPT_EVENT(event_population_changed, value)
ANK_SCRIPT_EVENT(event_fire_damage, bid)
ANK_SCRIPT_EVENT(event_mission_start, id)
ANK_SCRIPT_EVENT(event_collase_damage, bid)
ANK_SCRIPT_EVENT(event_granary_resource_added, bid, r, amount)
ANK_SCRIPT_EVENT(event_migration_update, population)
ANK_SCRIPT_EVENT(event_update_victory_state, population)
ANK_SCRIPT_EVENT(event_advance_day, year, month, mday, abdday, years_since_start)
ANK_SCRIPT_EVENT(event_advance_week, year, month, mday, abdday, years_since_start)
ANK_SCRIPT_EVENT(event_advance_month, year, month, mday, abdday, years_since_start)
ANK_SCRIPT_EVENT(event_building_create, bid)
ANK_SCRIPT_EVENT(event_city_disease, absday)
ANK_SCRIPT_EVENT(event_warehouse_filled, bid)
ANK_SCRIPT_EVENT(event_update_mission_goal, mid)
ANK_SCRIPT_EVENT(event_register_mission_animals, mid)
ANK_SCRIPT_EVENT(event_finance_changed, value)
ANK_SCRIPT_EVENT(event_show_advisor, advisor)
ANK_SCRIPT_EVENT(event_building_place_checks, bid)
ANK_SCRIPT_EVENT(event_finance_change_wages, value)
ANK_SCRIPT_EVENT(event_finance_request, type, deben)
ANK_SCRIPT_EVENT(event_festival_hold, god, type)
ANK_SCRIPT_EVENT(event_storageyards_remove_resource, resource, amount)
ANK_SCRIPT_EVENT(event_mods_info_updated, count)
ANK_SCRIPT_EVENT(event_toggle_industry_mothballed, resource)

int js_emit_script_event(pcstr event_name, const bvariant_map &args) {
    auto it = g_script_emit_handlers.find(event_name);
    if (it == g_script_emit_handlers.end()) {
        logs::info("JS: emit unknown event '%s' (ignored)", event_name);
        return 0;
    }

    it->second(args);
    return 0;
}

int js_game_emit(js_State *J, pcstr event_name) {
    // js_game_emit is a js_Emit callback called directly from the VM loop
    // without resetting BOT, so negative stack indices shift after js_pushiterator.
    // Use an absolute BOT-relative index to pin the payload regardless of TOP changes.
    int payload_idx = js_gettop(J) - 1;
    bvariant_map args = js_helpers::js_object_to_bvariant_map(J, payload_idx);
    return js_emit_script_event(event_name, args);
}
