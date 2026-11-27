#pragma once

#include "building/building.h"
#include "building/monuments.h"
#include "game/game_system.h"
#include "game/gods.h"

struct construction_blessing_t : public game_system {
    ANK_ESID(construction_blessing)

    enum {
        FIRST_MASONRY_PHASE = 2,
        BUDGET_MAJOR = 2,
        BUDGET_MINOR = 1,
    };

    static int cap_phase(const building_monument& monument);

    bool try_bless(e_god god, bool major, bool force_construction);

private:
    static bool is_small_mastaba_family(e_building_type type);
    static void set_phase_all_parts(building_monument& main, int phase);
    static void zero_footprint_progress(building_monument& main);
    static void sync_parts_to_main_phase(building_monument& main);

    bool is_target(building& b) const;
    building_monument* find_target() const;
    bool apply(building_monument& main, int budget);
};

construction_blessing_t& construction_blessing();
