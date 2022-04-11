#include "property.h"

#include "core/string.h"
#include "scenario/data.h"

int scenario_is_custom(void) {
    return scenario_data.settings.is_custom;
}
void scenario_set_custom(int custom) {
    scenario_data.settings.is_custom = custom;
}
int scenario_campaign_rank(void) {
    return scenario_data.settings.campaign_mission_rank;
}
void scenario_set_campaign_rank(int rank) {
    scenario_data.settings.campaign_mission_rank = rank;
}
int scenario_campaign_scenario_id(void) {
    return scenario_data.settings.campaign_scenario_id;
}
void scenario_set_campaign_scenario(int scenario_id) {
    scenario_data.settings.campaign_scenario_id = scenario_id;
}

#include "game/mission.h"

bool scenario_is_mission_rank(int rank) {
//    if (GAME_ENV == ENGINE_ENV_C3)
//        return !scenario_data.settings.is_custom && scenario_data.settings.campaign_mission_rank == rank - 1;
//    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
    return !scenario_data.settings.is_custom && scenario_data.settings.campaign_mission_rank == rank - 1;
}
int scenario_is_tutorial_before_mission_5(void) {
    return !scenario_data.settings.is_custom && scenario_data.settings.campaign_mission_rank < 5;
}

int scenario_starting_favor(void) {
    return scenario_data.settings.starting_kingdom;
}
int scenario_starting_personal_savings(void) {
    return scenario_data.settings.starting_personal_savings;
}

const uint8_t *scenario_name(void) {
    return scenario_data.scenario_name;
}
void scenario_set_name(const uint8_t *name) {
    string_copy(name, scenario_data.scenario_name, MAX_SCENARIO_NAME);
}

int scenario_is_open_play(void) {
    return scenario_data.is_open_play;
}
int scenario_open_play_id(void) {
    return scenario_data.open_play_scenario_id;
}

int scenario_property_climate(void) {
    return scenario_data.climate;
}

int scenario_property_start_year(void) {
    return scenario_data.start_year;
}
int scenario_property_rome_supplies_wheat(void) {
    return scenario_data.rome_supplies_wheat;
}
int scenario_property_enemy(void) {
    return scenario_data.enemy_id;
}
int scenario_property_player_rank(void) {
    return scenario_data.player_rank;
}
int scenario_image_id(void) {
    return scenario_data.image_id;
}

const uint8_t *scenario_subtitle(void) {
    return scenario_data.subtitle;
}

int scenario_initial_funds(void) {
    return scenario_data.initial_funds;
}
int scenario_rescue_loan(void) {
    return scenario_data.rescue_loan;
}

int scenario_property_monuments_is_enabled(void) {
    return (scenario_data.monuments.first > 0 ||
        scenario_data.monuments.second > 0 ||
        scenario_data.monuments.third > 0);
}
int scenario_property_monument(int field) {
    switch (field) {
        case 0:
            return scenario_data.monuments.first;
        case 1:
            return scenario_data.monuments.second;
        case 2:
            return scenario_data.monuments.third;
    }
    return -1;
}
void scenario_set_monument(int field, int m) {
    switch (field) {
        case 0:
            scenario_data.monuments.first = m;
            break;
        case 1:
            scenario_data.monuments.second = m;
            break;
        case 2:
            scenario_data.monuments.third = m;
            break;
    }
}