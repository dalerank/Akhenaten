#include "scenario/scenario.h"

#include "building/building_type.h"
#include "core/encoding.h"
#include "game/game_environment.h"

#include "js/js_game.h"

#include "core/profiler.h"

ANK_GLOBAL_OBJECT(g_scenario, __scenario,
    start_year,
    climate,
    image_id,
    kingdom_supplies_grain,
    campaign_scenario_id,
    is_open_play,
    subtitle,
    scmode,
    player_rank
    );

ANK_GLOBAL_OBJECT(g_scenario.settings, __scenario_settings,
    campaign_mission_rank,
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

ANK_GLOBAL_OBJECT(g_scenario.victory_state, __scenario_victory,
    state,
    force_win,
    force_lost
    );

void __scenario_victory_continue_governing(int months) {
    g_scenario.victory_state.continue_governing(months);
}
ANK_FUNCTION_1(__scenario_victory_continue_governing)

void __scenario_victory_reset() {
    g_scenario.victory_state.reset();
}
ANK_FUNCTION(__scenario_victory_reset)

xstring __scenario_event_msg_text(int title_id, int index) {
    return g_scenario.events.msg_text(title_id, index);
}
ANK_FUNCTION_2(__scenario_event_msg_text)

bool __scenario_building_allowed(int btype) {
    return scenario_building_allowed((e_building_type)btype);
}
ANK_FUNCTION_1(__scenario_building_allowed)

xstring __scenario_scenario_name() {
    pcstr n = (pcstr)g_scenario.scenario_name;
    return (n && n[0]) ? xstring(n) : xstring();
}
ANK_FUNCTION(__scenario_scenario_name)

