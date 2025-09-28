#pragma once

#include "figure/figure.h"

class figure_enemy : public figure_impl {
public:
    figure_enemy(figure *f) : figure_impl(f) {}
    virtual figure_enemy *dcast_enemy() override { return this; }

    virtual void on_create() override;
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual bool is_archer() const { return false; }
    virtual bool is_spearman() const { return false; }
    virtual bool is_mounted_archer() const { return false; }
    virtual e_figure_type missile_type() const { return FIGURE_NONE; }
    virtual bool ignore_pharaoh_soldiers() const { return false; }

    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENEMIES; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    virtual void enemy_initial(formation *m);
    virtual void enemy_marching(formation *m);
    virtual void enemy_fighting(formation *m);
};
