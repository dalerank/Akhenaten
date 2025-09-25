#pragma once

#include "figuretype/figure_enemy.h"

class figure_enemy_archer : public figure_enemy {
public:
    figure_enemy_archer(figure *f) : figure_enemy(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;

    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENEMIES; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    bool fight_enemy(int category, int max_distance);
};

class figure_barbarian_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_BARBARIAN_ARCHER, figure_barbarian_archer)
    figure_barbarian_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public figure_model {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_BARBARIAN_ARCHER, "barb_arch" }; }
};