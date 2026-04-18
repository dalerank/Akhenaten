#pragma once

#include <cstdint>
#include "city/city_religion.h"
#include "core/archive.h"

enum e_festival_type : uint8_t {
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

    e_god selected_god;
    e_festival_type selected_size;

    int8_t months_since_festival;
    int8_t first_festival_effect_months;
    int8_t second_festival_effect_months;

    bool is_planned();
    int months_till_next();
    xstring selected_god_name();
    void select_god(e_god god_id);
    void select_size(e_festival_type size);
    void schedule(e_god god, e_festival_type festival_size, int months_until_festival, int festival_cost, int beer_to_remove);
    void execute_festival();
    void update();
};
ANK_CONFIG_PROPERTY(city_festival_t,
    selected_god,
    selected_size,
    months_since_festival)

