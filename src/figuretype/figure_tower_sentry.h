#pragma once

#include "figure/figure.h"

enum e_tower_sentry_action {
    ACTION_150_TOWER_SENTRY_ATTACK = 150,
    ACTION_170_TOWER_SENTRY_AT_REST = 170,
    ACTION_171_TOWER_SENTRY_PATROLLING = 171,
    ACTION_172_TOWER_SENTRY_FIRING = 172,
    ACTION_173_TOWER_SENTRY_RETURNING = 173,
    ACTION_174_TOWER_SENTRY_GOING_TO_TOWER = 174,
};

class figure_tower_sentry : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TOWER_SENTRY, figure_tower_sentry)
    figure_tower_sentry(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t missile_delay;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        uint8_t wait_ticks_next_target;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_CRIME; }
    virtual void update_animation() override;
    virtual void poof() override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    void tower_sentry_pick_target();
    int tower_sentry_init_patrol(building *b, int *x_tile, int *y_tile);
    void move_ticks_tower_sentry(int num_ticks);
};
ANK_CONFIG_STRUCT(figure_tower_sentry::static_params, missile_delay)