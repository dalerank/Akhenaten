#pragma once

#include "game/simulation_time.h"

struct simulation_t {
    simulation_time_t simtime;
    bool time_runs = false;
};

extern simulation_t g_simulation;
