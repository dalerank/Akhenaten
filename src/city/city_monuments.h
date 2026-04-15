#pragma once

#include "game/game_system.h"

struct city_monuments_t : public game_system {
    ANK_ESID(city_monuments)

    void update_month();
    void advance_year();
};
