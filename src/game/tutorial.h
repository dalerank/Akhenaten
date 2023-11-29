#pragma once 

#include "core/buffer.h"
#include "city/constants.h"
#include "building/building_type.h"

struct tutorial_flags_t {
    struct {
        bool fire;
        bool population_150_reached;
        bool gamemeat_400_stored;
        bool collapse;
    } tutorial_1;

    struct {
        bool population_250_reached;
        bool population_450_reached;
        bool granary_built;
        bool gold_mined_500;
        bool temples_built;
        bool crime;
    } tutorial_2;

    struct {
        bool figs_800_stored;
        bool pottery_made;
        bool disease;
        int pottery_made_year;
    } tutorial_3;

    struct {
        bool beer_made;
    } tutorial_4;

    struct {
        bool spacious_apartment;
        bool papyrus_made;
    } tutorial_5;

    struct {
        bool flags[41];
        //
        bool crime;

        bool bricks_bought;

        bool tut5_can_trade_finally;

        //
        bool tut1_start;
        bool tut2_start;
        bool tut3_start;
        bool tut4_start;
        bool tut5_start;
        bool tut6_start;
        bool tut7_start;
        bool tut8_start;

    } pharaoh;
};

const tutorial_flags_t* tutorial_flags_struct();

void tutorial_init();

e_availability mission_advisor_availability(e_advisor advisor, int mission);
e_availability mission_empire_availability(int mission);

void tutorial_map_update(int tut);
void tutorial_menu_update(int tut);

int tutorial_get_population_cap(int current_cap);
int tutorial_get_immediate_goal_text();

int tutorial_adjust_request_year(int* year);

int tutorial_extra_fire_risk();
int tutorial_extra_damage_risk();

int tutorial_handle_fire();
int tutorial_handle_collapse();

void tutorial_on_crime();
void tutorial_on_disease();
void tutorial_on_filled_granary(int quantity);
void tutorial_on_add_to_storageyard();
void tutorial_on_gold_extracted();
void tutorial_on_religion();
void tutorial_on_house_evolve(e_house_level level);

void tutorial_starting_message();

void tutorial_on_day_tick();
void tutorial_on_month_tick();

void tutorial_update_step(int step);