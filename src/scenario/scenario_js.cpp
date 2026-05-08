#include "scenario/scenario.h"

#include "building/building_type.h"
#include "js/js_game.h"
#include "core/profiler.h"

ANK_GLOBAL_OBJECT(g_scenario, __scenario,
    start_year,
    kingdom_supplies_grain,
    campaign_scenario_id,
    is_open_play
    );


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