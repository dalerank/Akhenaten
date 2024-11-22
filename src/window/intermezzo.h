#pragma once

#include <functional>

typedef enum {
    INTERMEZZO_MISSION_BRIEFING = 0,
    INTERMEZZO_FIRED = 1,
    INTERMEZZO_WON = 2,
} intermezzo_type;

void window_intermezzo_show(intermezzo_type type, std::function<void()> f);
