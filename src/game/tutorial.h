#ifndef GAME_TUTORIAL_H
#define GAME_TUTORIAL_H

#include "core/buffer.h"

typedef enum {
    AVAILABLE,
    NOT_AVAILABLE,
    NOT_AVAILABLE_YET,
} tutorial_availability;

typedef struct tutorial_flags {
    struct {
        int fire;
        int crime;
        int collapse;
        int senate_built;
    } tutorial1;
    struct {
        int granary_built;
        int population_250_reached;
        int population_450_reached;
        int pottery_made;
        int pottery_made_year;
    } tutorial2;
    struct {
        int disease;
    } tutorial3;
    struct {
        bool flags[41];
        //
        bool fire;
        bool population_150_reached;
        bool gamemeat_400_stored;
        bool collapse;
        bool gold_mined_enough;
        bool entertainment_msg;
        //
        bool housing_and_roads_msg;
        bool crime_and_gold_msg;




    } pharaoh;
} tutorial_flags;

tutorial_flags *give_me_da_tut_flags();

void tutorial_init(void);

tutorial_availability tutorial_advisor_empire_availability(void);

void tutorial_menu_update(int tut);

int tutorial_get_population_cap(int current_cap);

int tutorial_get_immediate_goal_text(void);

int tutorial_adjust_request_year(int *year);

int tutorial_extra_fire_risk(void);

int tutorial_extra_damage_risk(void);

int tutorial_handle_fire(void);

int tutorial_handle_collapse(void);

void tutorial_on_crime(void);

void tutorial_on_disease(void);

void tutorial_on_filled_granary(void);

void tutorial_on_add_to_warehouse(void);

void tutorial_starting_message();

void tutorial_on_day_tick(void);

void tutorial_on_month_tick(void);

void tutorial_save_state(buffer *buf1, buffer *buf2, buffer *buf3);

void tutorial_load_state(buffer *buf1, buffer *buf2, buffer *buf3);

#endif // GAME_TUTORIAL_H
