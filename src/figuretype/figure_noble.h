#pragma once 

#include "figure/figure.h"

class figure_noble : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_NOBLES, figure_noble)
    figure_noble(figure *f) : figure_impl(f) {}

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