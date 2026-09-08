#pragma once

#include "figure/figure.h"

enum e_enemy_action {
    ACTION_151_ENEMY_INITIAL = 151,
    ACTION_152_ENEMY_WAITING = 152, // idle / embarked — no march or fire
    ACTION_153_ENEMY_MARCHING = 153,
    ACTION_154_ENEMY_FIGHTING = 154,
    ACTION_156_ENEMY_LEAVING = 156,
};

class figure_enemy : public figure_impl {
public:
    figure_enemy(figure *f) : figure_impl(f) {}
    virtual figure_enemy *dcast_enemy() override { return this; }

    struct runtime_data_t {
        tile2i last_target;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual bool is_archer() const { return false; }
    virtual bool is_spearman() const { return false; }
    virtual bool is_mounted_archer() const { return false; }
    // March/fight tick scale; mounts (camel, mounted archer) return >1.
    virtual int8_t enemy_speed_multiplier() const { return 1; }
    virtual e_figure_type missile_type() const { return FIGURE_NONE; }
    virtual bool ignore_pharaoh_soldiers() const { return false; }
    // Per-tick city tally: normal enemies → figures.enemies; kingdom army → kingdome_soldiers.
    virtual void count_as_city_invader();

    virtual bool is_attack() const { assert(false && "this function should be implemented"); return false; }
    virtual void formation_reset_to_initial(const formation *m) override;
    virtual e_figure_action enemy_initial_action() const { return (e_figure_action)ACTION_151_ENEMY_INITIAL; }

    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    virtual void enemy_initial(formation *m);
    virtual void enemy_marching(formation *m);
    virtual void enemy_fighting(formation *m);
    virtual void enemy_leaving();

    virtual void before_poof() override;

    virtual void leave_city();
};
