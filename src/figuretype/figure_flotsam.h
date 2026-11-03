#pragma once

#include "figure/figure.h"

enum e_flotsam_action {
    ACTION_8_FLOTSAM_CREATED = 8,
    ACTION_9_FLOTSAM_FLOATING = 9,
    ACTION_10_FLOTSAM_OFF_MAP = 10,
};

enum e_flotsam_kind {
    FLOTSAM_KIND_BOBBING = 0,
    FLOTSAM_KIND_DEBRIS_A = 1,
    FLOTSAM_KIND_DEBRIS_B = 2,
    FLOTSAM_KIND_SINKING = 3,
};

class figure_flotsam : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FLOTSAM, figure_flotsam)
    figure_flotsam(figure* f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t max_alive;
        uint8_t spawn_chance_pct;
    } FIGURE_STATIC_DATA_T;

    struct runtime_data_t {
        short frame;
        bool skip_tick;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void main_image_update() override;

    static int spawn(int kind);
    static void spawn_update_day();
};
ANK_CONFIG_STRUCT(figure_flotsam::static_params, max_alive, spawn_chance_pct)
