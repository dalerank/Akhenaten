#include "distant_battle.h"

#include "city/buildings.h"
#include "city/map.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/military.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "empire/type.h"
#include "figure/formation_batalion.h"
#include "game/game.h"
#include "scenario/scenario.h"

int scenario_distant_battle_kingdome_travel_months(void) {
    return g_scenario.empire.distant_battle_kingdome_travel_months;
}

int scenario_distant_battle_enemy_travel_months(void) {
    return g_scenario.empire.distant_battle_enemy_travel_months;
}

void scenario_distant_battle_set_kingdome_travel_months(void) {
    g_scenario.empire.distant_battle_kingdome_travel_months = empire_object_init_distant_battle_travel_months(EMPIRE_OBJECT_KINGDOME_ARMY);
}

void scenario_distant_battle_set_enemy_travel_months(void) {
    g_scenario.empire.distant_battle_enemy_travel_months = empire_object_init_distant_battle_travel_months(EMPIRE_OBJECT_ENEMY_ARMY);
}

void scenario_distant_battle_process(void) {
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario.invasions[i].type == INVASION_TYPE_DISTANT_BATTLE
            && game.simtime.year == g_scenario.invasions[i].year + g_scenario.start_year
            && game.simtime.month == g_scenario.invasions[i].month
            && g_scenario.empire.distant_battle_enemy_travel_months > 4
            && g_scenario.empire.distant_battle_kingdome_travel_months > 4 && !city_military_has_distant_battle()) {
            events::emit(event_message{ true, "message_kingdome_requests_army", 0, 0 });
            city_military_init_distant_battle(g_scenario.invasions[i].amount);
            return;
        }
    }

    city_military_process_distant_battle();
}
