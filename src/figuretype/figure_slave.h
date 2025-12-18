#pragma once 

#include "figure/figure.h"

enum e_slave_action {
    ACTION_150_SLAVE_ATTACK = 150,
    ACTION_156_SLAVE_GOING_TO_MEETING_CENTER = 156,
    ACTION_157_SLAVE_RETURNING_FROM_MEETING = 157,
    ACTION_158_SLAVE_CREATED = 158,
    ACTION_159_SLAVE_ATTACKING = 159,
};

class figure_slave : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_SLAVE, figure_slave)
    figure_slave(figure *f) : figure_impl(f) {}

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