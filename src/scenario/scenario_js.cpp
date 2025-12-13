#include "scenario/scenario.h"

#include "js/js_game.h"

void __scenario_set_goal_tooltip(xstring text) {
    g_scenario.goal_tooltip = text;
}
ANK_FUNCTION_1(__scenario_set_goal_tooltip)