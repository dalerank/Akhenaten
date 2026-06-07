#include "scenario/scenario.h"

#include "building/building_type.h"
#include "core/encoding.h"
#include "game/game_environment.h"
#include "scenario/criteria.h"

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

int __scenario_victory_houses_of_required_level() {
    return g_scenario.victory_state.houses_of_required_level();
}
ANK_FUNCTION(__scenario_victory_houses_of_required_level)

bool __scenario_victory_is_housing_condition_met() {
    return g_scenario.victory_state.is_housing_condition_met();
}
ANK_FUNCTION(__scenario_victory_is_housing_condition_met)

int __scenario_criteria_max_year() {
    return scenario_criteria_max_year();
}
ANK_FUNCTION(__scenario_criteria_max_year)

bvariant_map __scenario_victory_reasons() {
    bvariant_map result;
    for (const auto &[reason, met] : get_victory_reasons()) {
        result[reason] = bvariant(met);
    }
    return result;
}
ANK_FUNCTION(__scenario_victory_reasons)

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


