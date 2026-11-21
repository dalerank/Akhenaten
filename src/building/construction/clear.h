#pragma once

#include "grid/point.h"

#include <functional>

struct event_clear_land_confirm {
    const char* loc_id;
    std::function<void()> on_yes;
};

int building_construction_clear_land(bool measure_only, tile2i start, tile2i end);
