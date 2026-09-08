#pragma once

#include "figure/figure.h"

enum e_frog_action {
    ACTION_120_FROG_CREATED = 120,
    ACTION_121_FROG_ROAMING = 121,
};

class figure_frog : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FROG, figure_frog)
    figure_frog(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t default_swarm = 10;
        uint8_t max_amount = 24;
        uint16_t plague_days = 80;
        uint8_t house_infest_days = 80;
        int8_t happiness_hit = -10;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint16_t days_left = 0;
        // uint16 fits 228² grid; 0xFFFF = never visited (int16 truncated high offsets).
        uint16_t last_infest_offset = 0xFFFF;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override {}
    virtual void update_animation() override;
    virtual void update_day() override;
    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }

    static int spawn_swarm(int count = 0);
    static void apply_plague(int swarm_count = 0);
    static void infest_house(building &b);
};
ANK_CONFIG_STRUCT(figure_frog::static_params,
    default_swarm, max_amount, plague_days, house_infest_days, happiness_hit)
