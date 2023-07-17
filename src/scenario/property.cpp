#include "property.h"

#include "core/string.h"
#include "scenario/data.h"
#include "game/mission.h"

int scenario_is_custom(void) {
    return g_scenario_data.settings.is_custom;
}
void scenario_set_custom(int custom) {
    g_scenario_data.settings.is_custom = custom;
}
int scenario_campaign_rank(void) {
    return g_scenario_data.settings.campaign_mission_rank;
}
void scenario_set_campaign_rank(int rank) {
    g_scenario_data.settings.campaign_mission_rank = rank;
}
int scenario_campaign_scenario_id(void) {
    return g_scenario_data.settings.campaign_scenario_id;
}
void scenario_set_campaign_scenario(int scenario_id) {
    g_scenario_data.settings.campaign_scenario_id = scenario_id;
}

bool scenario_is_mission_rank(int rank) {
//    if (GAME_ENV == ENGINE_ENV_C3)
//        return !g_scenario_data.settings.is_custom && g_scenario_data.settings.campaign_mission_rank == rank - 1;
//    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
    return !g_scenario_data.settings.is_custom && g_scenario_data.settings.campaign_mission_rank == rank - 1;
}
int scenario_is_tutorial_before_mission_5(void) {
    return !g_scenario_data.settings.is_custom && g_scenario_data.settings.campaign_mission_rank < 5;
}

int scenario_starting_kingdom(void) {
    return g_scenario_data.settings.starting_kingdom;
}
int scenario_starting_personal_savings(void) {
    return g_scenario_data.settings.starting_personal_savings;
}

const uint8_t *scenario_name(void) {
    return g_scenario_data.scenario_name;
}
void scenario_set_name(const uint8_t *name) {
    string_copy(name, g_scenario_data.scenario_name, MAX_SCENARIO_NAME);
}

int scenario_is_open_play(void) {
    return g_scenario_data.is_open_play;
}
int scenario_open_play_id(void) {
    return g_scenario_data.open_play_scenario_id;
}

int scenario_property_climate(void) {
    return g_scenario_data.climate;
}

int scenario_property_start_year(void) {
    return g_scenario_data.start_year;
}
int scenario_property_rome_supplies_wheat(void) {
    return g_scenario_data.rome_supplies_wheat;
}
int scenario_property_enemy(void) {
    return g_scenario_data.enemy_id;
}
int scenario_property_player_rank(void) {
    return g_scenario_data.player_rank;
}
int scenario_image_id(void) {
    return g_scenario_data.image_id;
}

const uint8_t *scenario_subtitle(void) {
    return g_scenario_data.subtitle;
}

int scenario_initial_funds(void) {
    return g_scenario_data.initial_funds;
}
int scenario_rescue_loan(void) {
    return g_scenario_data.rescue_loan;
}

int scenario_property_monuments_is_enabled(void) {
    return (g_scenario_data.monuments.first > 0 ||
        g_scenario_data.monuments.second > 0 ||
        g_scenario_data.monuments.third > 0);
}
int scenario_property_monument(int field) {
    switch (field) {
        case 0:
            return g_scenario_data.monuments.first;
        case 1:
            return g_scenario_data.monuments.second;
        case 2:
            return g_scenario_data.monuments.third;
    }
    return -1;
}
void scenario_set_monument(int field, int m) {
    switch (field) {
        case 0:
            g_scenario_data.monuments.first = m;
            break;
        case 1:
            g_scenario_data.monuments.second = m;
            break;
        case 2:
            g_scenario_data.monuments.third = m;
            break;
    }
}