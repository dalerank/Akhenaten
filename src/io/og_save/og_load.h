#pragma once

#include "io/og_save/og_save.h"

// Stage 2 of the original-save converter: OG records (og::savegame) written straight into the runtime objects.
// This path is separate from the .svx binds on purpose, so the bind layout can change without touching it.
// The scenario (rules, events, empire layout) comes from our mission script; only city state is taken from the
// save. OG data without a home in our model is logged as "[og-save] unmapped ..." and left out.
namespace og {

    struct load_report {
        int buildings = 0;
        int buildings_dropped = 0;
        int buildings_runtime_unmapped = 0;
        int figures_dropped = 0;
        int legions = 0;
        int formations_dropped = 0;
        int events_synced = 0;
        int events_unmatched = 0;
    };

    // The campaign mission the save was played in, -1 for a custom scenario.
    int mission_id(const savegame& s);

    void load_grids(const savegame& s);
    void load_world(const savegame& s);
    void load_city_state(const savegame& s);
    void load_buildings(const savegame& s, load_report& report);
    void load_formations(const savegame& s, load_report& report);
    void load_events(const savegame& s, load_report& report);

    // State that depends on what post_load rebuilt (food slots follow the city's allowed foods).
    void load_after_post_load(const savegame& s);

} // namespace og
