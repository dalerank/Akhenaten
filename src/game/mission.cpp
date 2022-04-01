#include "mission.h"

#include "scenario/property.h"
#include "core/game_environment.h"
#include "player_data.h"

int get_mission_campaign_id(int scenario_id) {
    if (scenario_id < SCENARIO_NULL || scenario_id >= SCENARIO_MAX)
        return CAMPAIGN_NULL;
    for (int i = 0; i < 9; ++i) {
        int last_in_campaign = get_last_mission_in_campaign(i);
        if (scenario_id <= last_in_campaign)
            return i;
    }
}
int get_first_mission_in_campaign(int campaign_id) {
    if (campaign_id < CAMPAIGN_PHARAOH_PREDYNASTIC || campaign_id >= CAMPAIGN_MAX)
        return SCENARIO_NULL;
    if (campaign_id == CAMPAIGN_PHARAOH_PREDYNASTIC)
        return SCENARIO_NUBT;
    else
        return 1 + SCENARIO_LAST_IN_CAMPAIGN[campaign_id - 1];
}
int get_last_mission_in_campaign(int campaign_id) {
    if (campaign_id < CAMPAIGN_PHARAOH_PREDYNASTIC || campaign_id >= CAMPAIGN_MAX)
        return SCENARIO_NULL;

   return SCENARIO_LAST_IN_CAMPAIGN[campaign_id];
}

int game_mission_choose(int rank, int index) {
    if (index < 0 || index > 2)
        index = 0;
    const int *scenarios = MISSION_RANK_TO_SCENARIO[rank].scenario;
    if (scenarios[index] == SCENARIO_NULL)
        return scenarios[0];
    return scenarios[index];
}
bool game_mission_has_choice(void) {
    return false; // TODO
//    if (GAME_ENV == ENGINE_ENV_C3)
//        return RANK_CHOICE_C3[scenario_campaign_rank()];
//    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
//        int selector = scenario_ph_mission_selector();
//        return CAN_CHOOSE_NEXT_SCENARIO_PH[selector];
//    }
}

bool game_campaign_unlocked(int campaign_id) {
    switch (campaign_id) {
        // pharaoh
        case CAMPAIGN_PHARAOH_ARCHAIC:
            return game_scenario_unlocked(SCENARIO_NUBT);
        case CAMPAIGN_PHARAOH_PREDYNASTIC:
            return game_scenario_unlocked(SCENARIO_NEKHEN);
        case CAMPAIGN_PHARAOH_OLD_KINGDOM:
            return game_scenario_unlocked(SCENARIO_SELIMA_OASIS);
        case CAMPAIGN_PHARAOH_MIDDLE_KINGDOM:
            return game_scenario_unlocked(SCENARIO_THINIS_2);
        case CAMPAIGN_PHARAOH_NEW_KINGDOM:
            return game_scenario_unlocked(SCENARIO_KHMUN);
        // cleopatra
        case CAMPAIGN_CLEOPATRA_VALLEY_OF_THE_KINGS:
            return game_scenario_unlocked(SCENARIO_VALLEY_THUTMOSE);
        case CAMPAIGN_CLEOPATRA_RAMSES_II:
            return game_scenario_unlocked(SCENARIO_SUMUR);
        case CAMPAIGN_CLEOPATRA_ANCIENT_CONQUERORS:
            return game_scenario_unlocked(SCENARIO_PI_YER);
        case CAMPAIGN_CLEOPATRA_CLEOPATRAS_CAPITAL:
            return game_scenario_unlocked(SCENARIO_ALEXANDRIA_1);
    }
}
bool game_scenario_unlocked(int scenario_id) {
    if (scenario_id < 0 || scenario_id >= SCENARIO_MAX) // invalid mission index
        return false;
    switch (scenario_id) {
        case SCENARIO_NUBT:
        case SCENARIO_VALLEY_THUTMOSE:
            return true; // first mission is always unlocked
    }
    const int *requirements = SCENARIO_REQUIREMENTS_PH[scenario_id].req_beaten;
    // by default, beating the previous scenario will unlock the scenario.
    if (requirements[0] == SCENARIO_NULL)
        return game_scenario_beaten(scenario_id - 1);
    // if otherwise specified, this scenario requires specific ones to unlock;
    // any one of them in the req. group will suffice to unlock the scenario.
    for (int i = 0; i < 3; ++i) {
        if (requirements[i] != SCENARIO_NULL)
            if (game_scenario_beaten(requirements[i]))
                return true;
    }
}
bool game_scenario_beaten(int scenario_id) {
    if (scenario_id < 0 || scenario_id >= SCENARIO_MAX) // invalid mission index
        return false;
    auto record = player_get_scenario_record(scenario_id);
    return record->nonempty;
}