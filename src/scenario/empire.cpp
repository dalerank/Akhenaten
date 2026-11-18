#include "empire.h"

#include "city/city_message.h"
#include "empire/empire.h"
#include "game/simulation.h"
#include "scenario/scenario.h"

int scenario_empire_id() {
    return g_scenario.empire.id;
}

int scenario_empire_is_expanded() {
    return g_scenario.empire.is_expanded;
}

void scenario_empire_process_expansion() {
    if (g_scenario.empire.is_expanded || g_scenario.empire.expansion_year <= 0) {
        return;
    }

    if (g_simulation.simtime.year < g_scenario.empire.expansion_year + g_scenario.start_year) {
        return;
    }

    g_empire.expand();

    g_scenario.empire.is_expanded = 1;
    messages::popup("message_empire_has_expanded", 0, 0);
}
