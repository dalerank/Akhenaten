#pragma once

#include "city/city_religion.h"
#include "core/archive.h"
#include "game/game_system.h"

enum e_festival_type : uint8_t {
    FESTIVAL_NONE = 0,
    FESTIVAL_SMALL = 1,
    FESTIVAL_LARGE = 2,
    FESTIVAL_GRAND = 3,
    FESTIVAL_BAST_SPECIAL = 4,

    FESTIVAL_MAX,
};

struct event_festival_hold { e_god god; e_festival_type type; };

struct city_festival_t : public game_system {
    ANK_ESID(city_festival)

    int8_t months_till_next;
    e_god planned_god;
    e_festival_type planned_size;

    int8_t months_since_festival;
    int8_t first_festival_effect_months;
    int8_t second_festival_effect_months;

    bool entertainment_is_low() const { return months_since_festival > 6; }
    bool was_recent() const { return months_since_festival < 6; }

    void execute_festival();
    void advance_month();
};
