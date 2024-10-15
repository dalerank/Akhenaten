#include "empire.h"

#include "city/message.h"
#include "empire/empire.h"
#include "game/time.h"
#include "scenario/scenario.h"

int scenario_empire_id() {
    return g_scenario_data.empire.id;
}

int scenario_empire_is_expanded() {
    return g_scenario_data.empire.is_expanded;
}

void scenario_empire_process_expansion() {
    if (g_scenario_data.empire.is_expanded || g_scenario_data.empire.expansion_year <= 0) {
        return;
    }

    if (gametime().year < g_scenario_data.empire.expansion_year + g_scenario_data.start_year) {
        return;
    }

    g_empire.expand();

    g_scenario_data.empire.is_expanded = 1;
    city_message_post(true, MESSAGE_EMPIRE_HAS_EXPANDED, 0, 0);
}
