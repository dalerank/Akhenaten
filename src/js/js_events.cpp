#include "core/bstring.h"
#include "core/app.h"
#include "game/game_events.h"
#include "city/city_maintenance.h"
#include "city/city_finance.h"
#include "js/js_events.h"

#include "input/hotkey.h"
#include "building/construction/build_planner.h"
#include "game/mission.h"
#include "building/building_granary.h"
#include "building/building_storage_yard.h"
#include "figuretype/figure_rioter.h"
#include "city/city_migration.h"
#include "city/city_health.h"
#include "city/city_festival.h"
#include "city/city_victory.h"
#include "city/city_religion.h"
#include "city/city_resource.h"
#include "scenario/scenario.h"
#include "city/city_kingdome_relations.h"
#include "city/city_population.h"
#include "dev/debug.h"
#include "building/building_palace.h"
#include "content/mods.h"
#include "game/game.h"
#include "js/js_game.h"
#include "window/autoconfig_window.h"

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
ANK_SCRIPT_EVENT(event_mission_won, scenario_id, next_scenario_id)
ANK_SCRIPT_EVENT(event_level_post_load, session_kind, scenario_id)
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
ANK_SCRIPT_EVENT(event_mission_briefing_show_after_load, scenario_id)
ANK_SCRIPT_EVENT(event_finance_changed, value)
ANK_SCRIPT_EVENT(event_show_advisor, advisor)
ANK_SCRIPT_EVENT(event_building_place_checks, bid)
ANK_SCRIPT_EVENT(event_finance_change_wages, value)
ANK_SCRIPT_EVENT(event_finance_change_tax, value)
ANK_SCRIPT_EVENT(event_finance_donation, amount)
ANK_SCRIPT_EVENT(event_finance_request, type, deben)
ANK_SCRIPT_EVENT(event_festival_hold, god, type)
ANK_SCRIPT_EVENT(event_storageyards_remove_resource, resource, amount)
ANK_SCRIPT_EVENT(event_mods_info_updated, count)
ANK_SCRIPT_EVENT(event_toggle_industry_mothballed, resource)
ANK_SCRIPT_EVENT(event_toggle_pause, value)
ANK_SCRIPT_EVENT(event_app_close_requested, reserved)
ANK_SCRIPT_EVENT(event_save_city, value)
ANK_SCRIPT_EVENT(event_change_gamespeed, increase)
ANK_SCRIPT_EVENT(event_update_game_tick_timer, reserved)
ANK_SCRIPT_EVENT(event_change_scroll_speed, increase)
ANK_SCRIPT_EVENT(event_change_middle_mouse_pan_speed, increase)
ANK_SCRIPT_EVENT(event_change_clouds_speed, increase)
ANK_SCRIPT_EVENT(event_send_gift_to_kingdome, gift_size)
ANK_SCRIPT_EVENT(event_kingdome_update_gifts, personal_savings)
ANK_SCRIPT_EVENT(event_report_bug_result, ok, url, error)
ANK_SCRIPT_EVENT(event_draw_debug_properties, reserved)
ANK_SCRIPT_EVENT(event_rioter_created, id)
ANK_SCRIPT_EVENT(event_rotate_map, value)
ANK_SCRIPT_EVENT(event_rotate_map_reset, value)
ANK_SCRIPT_EVENT(event_rotate_building, value)
ANK_SCRIPT_EVENT(event_change_building_variant, value)
ANK_SCRIPT_EVENT(event_city_building_mode, value)
ANK_SCRIPT_EVENT(event_building_change_mode, pack, id, offset)
ANK_SCRIPT_EVENT(event_build_menu_submenu_changed, submenu)
ANK_SCRIPT_EVENT(event_building_menu_update, stage)
ANK_SCRIPT_EVENT(event_building_menu_changed, temp)
ANK_SCRIPT_EVENT(event_use_building, type, en)
ANK_SCRIPT_EVENT(event_religion_god_status_update, god, status)
ANK_SCRIPT_EVENT(event_set_bookmark, value)
ANK_SCRIPT_EVENT(event_goto_bookmark, value)
ANK_SCRIPT_EVENT(event_show_main_menu, play_intro)
ANK_SCRIPT_EVENT(event_copy_build_from_cursor, value)

int js_emit_script_event(pcstr event_name, const bvariant_map &args) {
    auto it = g_script_emit_handlers.find(event_name);
    if (it == g_script_emit_handlers.end()) {
        logs::info("JS: emit unknown event '%s' (ignored)", event_name);
        return 0;
    }

    it->second(args);
    return 0;
}

int js_game_emit_es(xstring es, xstring sub_event, bvariant_map args) {
    autoconfig_window *w = autoconfig_window::find(es);
    if (!w) {
        logs::info("JS: emit window '%s' not found (ignored)", es.c_str());
        return 0;
    }

    w->enqueue_event(sub_event, std::move(args));
    return 0;
}

int js_game_emit(js_State *J, pcstr event_name) {
    int payload_idx = js_gettop(J) - 1;
    bvariant_map args = js_helpers::js_object_to_bvariant_map(J, payload_idx);

    const char *dot = strchr(event_name, '.');
    if (dot && dot != event_name && dot[1]) {
        bstring128 es_name;
        es_name.ncat(event_name, static_cast<size_t>(dot - event_name));
        return js_game_emit_es(es_name.c_str(), xstring(dot + 1), std::move(args));
    }

    return js_emit_script_event(event_name, std::move(args));
}
