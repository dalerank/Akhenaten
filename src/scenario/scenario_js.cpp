#include "scenario/scenario.h"

#include "js/js_game.h"
#include "core/profiler.h"

void __scenario_set_goal_tooltip(xstring text) {
    g_scenario.goal_tooltip = text;
}
ANK_FUNCTION_1(__scenario_set_goal_tooltip)

xstring __scenario_event_msg_text(int title_id, int index) {
    return g_scenario.events.msg_text(title_id, index);
}
ANK_FUNCTION_2(__scenario_event_msg_text)