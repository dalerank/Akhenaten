#pragma once

#include "figure/figure.h"

enum e_native_action {
    ACTION_159_NATIVE_ATTACKING = 159,
    ACTION_160_NATIVE_GOING_TO_WAREHOUSE = 160,
    ACTION_161_NATIVE_RETURNING = 161,
    ACTION_162_NATIVE_CREATED = 162,
    ACTION_163_NATIVE_AT_WAREHOUSE = 163,
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
    //virtual bool play_die_sound() override;
    //virtual void apply_damage(int hit_dmg, figure_id attacker_id) override;

    virtual e_minimap_figure_color minimap_color() const override { return FIGURE_COLOR_ANIMAL; }
};