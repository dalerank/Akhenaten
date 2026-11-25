#pragma once

#include "game/game_system.h"

struct city_monuments_t : public game_system {
    ANK_ESID(city_monuments)

    void advance_year();
};

city_monuments_t& city_monuments();
