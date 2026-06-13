#pragma once

#include "core/xstring.h"
#include "game/game_system.h"

struct event_update_victory_state { int population; };

enum e_victory_state {
    e_victory_state_lost = -1,
    e_victory_state_none = 0,
    e_victory_state_won = 1
};

struct city_victory_t : public game_system {
    ANK_ESID(city_victory)

    e_victory_state state;
    bool force_win;
    bool force_lost;

    void reset();
    void victory_check();
};
