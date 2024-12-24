#include "distant_battle.h"

#include "city/buildings.h"
#include "city/map.h"
#include "city/message.h"
#include "city/military.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "empire/type.h"
#include "figure/formation_legion.h"
#include "game/game.h"
#include "scenario/scenario.h"

int scenario_distant_battle_kingdome_travel_months(void) {
    return g_scenario_data.empire.distant_battle_kingdome_travel_months;
}

int scenario_distant_battle_enemy_travel_months(void) {
    return g_scenario_data.empire.distant_battle_enemy_travel_months;
}

void scenario_distant_battle_set_kingdome_travel_months(void) {
    g_scenario_data.empire.distant_battle_kingdome_travel_months = empire_object_init_distant_battle_travel_months(EMPIRE_OBJECT_KINGDOME_ARMY);
}

void scenario_distant_battle_set_enemy_travel_months(void) {
    g_scenario_data.empire.distant_battle_enemy_travel_months = empire_object_init_distant_battle_travel_months(EMPIRE_OBJECT_ENEMY_ARMY);
}

void scenario_distant_battle_process(void) {
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario_data.invasions[i].type == INVASION_TYPE_DISTANT_BATTLE
            && game.simtime.year == g_scenario_data.invasions[i].year + g_scenario_data.start_year
            && game.simtime.month == g_scenario_data.invasions[i].month
            && g_scenario_data.empire.distant_battle_enemy_travel_months > 4
            && g_scenario_data.empire.distant_battle_kingdome_travel_months > 4 && !city_military_has_distant_battle()) {
            city_message_post(true, MESSAGE_KINGDOME_REQUESTS_ARMY, 0, 0);
            city_military_init_distant_battle(g_scenario_data.invasions[i].amount);
            return;
        }
    }

    city_military_process_distant_battle();
}
