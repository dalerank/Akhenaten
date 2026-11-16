#pragma once

#include "building/building.h"
#include "building/monuments.h"
#include "game/gods.h"

enum {
    CONSTRUCTION_BLESSING_FIRST_MASONRY_PHASE = 2,
    CONSTRUCTION_BLESSING_BUDGET_MAJOR = 2,
    CONSTRUCTION_BLESSING_BUDGET_MINOR = 1,
};

int construction_blessing_cap_phase(const building_monument &monument);
bool is_construction_blessing_monument(building &b);
building_monument* find_construction_blessing_target();
bool apply_construction_blessing(building_monument &main, int budget);
bool maybe_construction_blessing(e_god god, bool major, bool force_construction);
