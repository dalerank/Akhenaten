#pragma once

#include <cstdint>
#include "city/city_religion.h"

enum e_festival_type {
    FESTIVAL_NONE = 0,
    FESTIVAL_SMALL = 1,
    FESTIVAL_LARGE = 2,
    FESTIVAL_GRAND = 3,
    FESTIVAL_BAST_SPECIAL = 4,
};


struct event_festival_hold { e_god god; e_festival_type type; };

struct city_festival_t {
    struct {
        int8_t months_to_go;
        e_god god;
        e_festival_type size;
    } planned;

    enum {
        small_min_months = 1,
        middle_min_months = 2,
        grand_min_minths = 3,
    };

    struct {
        e_god god;
        e_festival_type size;
    } selected;
    
    uint16_t small_cost;
    uint16_t large_cost;
    uint16_t grand_cost;
    uint16_t grand_alcohol;
    bool not_enough_alcohol;

    int8_t months_since_festival;
    int8_t first_festival_effect_months;
    int8_t second_festival_effect_months;

    bool is_planned();
    int months_till_next();
    e_god selected_god();
    xstring selected_god_name();
    void select_god(e_god god_id);
    int selected_size();
    bool select_size(e_festival_type size);
    void schedule();
    void execute_festival();
    void update();
    void calculate_costs();
    int get_advice();
};

