#pragma once

#include "figure/figure.h"

enum e_festival_priest_action {
    ACTION_8_FESTIVAL_PRIEST_CREATED = 8,
    ACTION_9_FESTIVAL_PRIEST_PICK_SPOT = 9,
    ACTION_10_FESTIVAL_PRIEST_WALKING = 10,
    ACTION_11_FESTIVAL_PRIEST_ARRIVED = 11,
};

enum {
    FESTIVAL_PRIEST_SQUARE_SIZE = 5,
    FESTIVAL_PRIEST_SQUARE_CENTER = 2,
};

// OG walkers.c figure_festival_priest_action + building_figure_helpers.c building_festival_spawn_celebrants.
class figure_festival_priest : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FESTIVAL_PRIEST, figure_festival_priest)
    figure_festival_priest(figure* f) : figure_impl(f) {}

    struct look_t {
        svector<e_building_type, 4> buildings;
        e_figure_type figure;
        xstring anim;
    };

    struct celebrant_group_t {
        uint8_t rate;
        svector<e_building_type, 12> buildings;
    };

    struct counts_as_t {
        e_building_type building;
        svector<e_building_type, 4> counts;
    };

    struct static_params : public figure_static_params {
        int8_t trips;
        uint8_t celebrants_per_size;
        svector<celebrant_group_t, 4> celebrant_groups;
        svector<counts_as_t, 4> active_counts_as;
        svector<look_t, 16> looks;
        look_t default_look;

        const look_t& look_of(e_building_type type) const;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        int8_t trips;
        e_figure_type look;
    } FIGURE_RUNTIME_DATA_T;

    virtual figure_festival_priest* dcast_festival_priest() override { return this; }
    virtual void figure_before_action() override {}
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void on_post_load() override;

    e_figure_type look() const { return runtime_data().look; }

    static void spawn_celebrants(int size);
    static figure* spawn_celebrant(building& b);
};
ANK_CONFIG_STRUCT(figure_festival_priest::look_t, buildings, figure, anim)
ANK_CONFIG_STRUCT(figure_festival_priest::celebrant_group_t, rate, buildings)
ANK_CONFIG_STRUCT(figure_festival_priest::counts_as_t, building, counts)
ANK_CONFIG_STRUCT(figure_festival_priest::static_params, trips, celebrants_per_size, celebrant_groups, active_counts_as,
  looks, default_look)
