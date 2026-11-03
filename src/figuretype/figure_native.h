#pragma once

#include "figure/figure.h"

// OG FIG_BARBARIAN / figure_indigenous_native_action action ids (Pharaoh 8..11).
enum e_native_action {
    ACTION_8_NATIVE_GOING_TO_MEETING = 8,
    ACTION_9_NATIVE_RETURNING = 9,
    ACTION_10_NATIVE_CREATED = 10,
    ACTION_11_NATIVE_ATTACKING = 11,

    ACTION_12_NATIVE_MAX
};

class figure_native : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_INDIGENOUS_NATIVE, figure_native)
    figure_native(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        int8_t applied_damage;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void before_poof() override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};
