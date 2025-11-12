#pragma once

#include "figure/figure.h"

enum e_flotsam_action {
    ACTION_128_FLOTSAM_CREATED = 128,
    ACTION_129_FLOTSAM_FLOATING = 129,
    ACTION_130_FLOTSAM_OFF_MAP = 130,
};

class figure_flotsam : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_FLOTSAM, figure_flotsam)
    figure_flotsam(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        short frame;
        bool flotsam_visible;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
};