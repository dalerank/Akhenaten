#pragma once

#include <stdint.h>

enum e_climate { 
    CLIMATE_CENTRAL = 0, 
    CLIMATE_NORTHERN = 1, 
    CLIMATE_DESERT = 2
};

int scenario_is_custom();

void scenario_set_custom(int custom);

int scenario_campaign_rank(void);

void scenario_set_campaign_rank(int rank);

int scenario_campaign_scenario_id(void);

void scenario_set_campaign_scenario(int scenario_id);

bool scenario_is_mission_rank(int rank);
int scenario_is_tutorial_before_mission_5(void);
int scenario_starting_kingdom(void);

int scenario_starting_personal_savings(void);

const uint8_t* scenario_name(void);

void scenario_set_name(const uint8_t* name);

int scenario_is_open_play(void);

int scenario_open_play_id(void);

int scenario_property_climate(void);

int scenario_property_start_year(void);

int scenario_property_kingdom_supplies_grain();

int scenario_property_enemy(void);

int scenario_property_player_rank(void);

int scenario_image_id(void);

const uint8_t* scenario_subtitle(void);

int scenario_initial_funds(void);

int scenario_rescue_loan(void);

int scenario_property_monuments_is_enabled(void);
int scenario_property_monument(int field);
void scenario_set_monument(int field, int m);

void scenario_load_meta_data(int scenario_id);
