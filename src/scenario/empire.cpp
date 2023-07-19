#include "empire.h"

#include "city/message.h"
#include "empire/city.h"
#include "game/time.h"
#include "scenario/scenario_data.h"

int scenario_empire_id(void) {
    return g_scenario_data.empire.id;
}

int scenario_empire_is_expanded(void) {
    return g_scenario_data.empire.is_expanded;
}

void scenario_empire_process_expansion(void) {
    if (g_scenario_data.empire.is_expanded || g_scenario_data.empire.expansion_year <= 0)
        return;
    if (game_time_year() < g_scenario_data.empire.expansion_year + g_scenario_data.start_year)
        return;

    empire_city_expand_empire();

    g_scenario_data.empire.is_expanded = 1;
    city_message_post(true, MESSAGE_EMPIRE_HAS_EXPANDED, 0, 0);
}
