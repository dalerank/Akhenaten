#pragma once

#include "figure/figure.h"

class figure_enemy : public figure_impl {
public:
    figure_enemy(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;

    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENEMIES; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    virtual void enemy_initial(formation *m);
    virtual void enemy_marching(formation *m);
    virtual void enemy_fighting(formation *m);
};
