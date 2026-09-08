#pragma once

#include "figuretype/figure_enemy.h"

enum e_action_enemy_spearman : uint16_t {
    ACTION_0_ENEMY_SPEARMAN_NONE = 0,
    ACTION_151_ENEMY_SPEARMAN_INITIAL = 151,
    ACTION_152_ENEMY_SPEARMAN_WAITING = 152,
    ACTION_153_ENEMY_SPEARMAN_MARCHING = 153,
    ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE = 154,
    ACTION_155_ENEMY_SPEARMAN_RELOAD = 155,
    ACTION_156_ENEMY_SPEARMAN_LEAVING = 156,

    ACTION_157_ENEMY_SPEARMAN_MAX
};
using e_action_enemy_spearman_tokens_t = token_holder<e_action_enemy_spearman, ACTION_0_ENEMY_SPEARMAN_NONE, ACTION_157_ENEMY_SPEARMAN_MAX>;
extern const e_action_enemy_spearman_tokens_t e_action_enemy_spearman_tokens;

class figure_enemy_spearman : public figure_enemy {
public:
    figure_enemy_spearman(figure *f) : figure_enemy(f) {}
    virtual figure_enemy_spearman *dcast_enemy_spearman() override { return this; }

    struct static_params : public figure_static_params {
        int8_t missile_attack_value;
        int8_t missile_delay;
        int8_t attack_distance;
        e_figure_type missile_type = FIGURE_ARROW;
    };

    const static_params &current_params() const { return (const static_params &)figure_enemy::current_params(); };

    virtual void on_create() override;
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual bool is_archer() const override { return true; }
    virtual bool is_attack() const override { return base.in_attack(); }

    virtual int8_t missile_attack_value() const { return current_params().missile_attack_value; }
    virtual int8_t missile_delay() const { return current_params().missile_delay; }
    virtual int8_t attack_distance() const { return current_params().attack_distance; }
    virtual e_figure_type missile_type() const override { return current_params().missile_type; }

    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    //bool fight_enemy(int category, int max_distance);
    virtual void enemy_initial(formation *m) override;
    virtual void enemy_marching(formation *m) override;
    virtual void enemy_fighting(formation *m) override;
    virtual void leave_city() override;
};
ANK_CONFIG_STRUCT(figure_enemy_spearman::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_egyptian_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_EGYPTIAN_SPEAR, figure_egyptian_spearman)
    figure_egyptian_spearman(figure *f) : figure_enemy_spearman(f) {}
};

// Kingdom javelin (55). Favour-army remap of egyptian type1 slot.
class figure_kingdome_javelin : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_KINGDOME_JAVELIN, figure_kingdome_javelin)
    figure_kingdome_javelin(figure *f) : figure_enemy_spearman(f) {}
};


class figure_hittite_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_HITTITE_SPEARMAN, figure_hittite_spearman)
    figure_hittite_spearman(figure *f) : figure_enemy_spearman(f) {}
};

class figure_kushite_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_KUSHITE_SPEARMAN, figure_kushite_spearman)
    figure_kushite_spearman(figure *f) : figure_enemy_spearman(f) {}
};

class figure_persian_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_PERSIAN_SPEARMAN, figure_persian_spearman)
    figure_persian_spearman(figure *f) : figure_enemy_spearman(f) {}
};

class figure_phoenician_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_PHOENICIAN_SPEARMAN, figure_phoenician_spearman)
    figure_phoenician_spearman(figure *f) : figure_enemy_spearman(f) {}
};
