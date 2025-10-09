#pragma once

#include "figuretype/figure_enemy.h"

enum e_action_enemy_archer {
    ACTION_151_ENEMY_SPEARMAN_INITIAL = 151,
    ACTION_152_ENEMY_SPEARMAN_WAITING = 152,
    ACTION_153_ENEMY_SPEARMAN_MARCHING = 153,
    ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE = 154,
    ACTION_155_ENEMY_SPEARMAN_RELOAD = 155,
};

class figure_enemy_spearman : public figure_enemy {
public:
    figure_enemy_spearman(figure *f) : figure_enemy(f) {}
    virtual figure_enemy_spearman *dcast_enemy_spearman() override { return this; }

    struct base_params_t {
        int8_t missile_attack_value;
        int8_t missile_delay;
        int8_t attack_distance;
        e_figure_type missile_type = FIGURE_ARROW;
    };

    template<typename T>
    struct static_params_t : public base_params_t, public figures::model_t<T> {
        virtual void archive_load(archive arch) override {
            arch.r<base_params_t>(*this);
        }
    };

    virtual const base_params_t &base_params() const = 0;

    virtual void on_create() override;
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual bool is_archer() const override { return true; }

    virtual int8_t missile_attack_value() const { return base_params().missile_attack_value; }
    virtual int8_t missile_delay() const { return base_params().missile_delay; }
    virtual int8_t attack_distance() const { return base_params().attack_distance; }
    virtual e_figure_type missile_type() const override { return base_params().missile_type; }

    virtual bool is_attack() const override { return action_state() == ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE; }

    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENEMIES; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    //bool fight_enemy(int category, int max_distance);
    virtual void enemy_initial(formation *m) override;
    virtual void enemy_marching(formation *m) override;
    virtual void enemy_fighting(formation *m)override;
};
ANK_CONFIG_STRUCT(figure_enemy_spearman::base_params_t,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_egyptian_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_EGYPTIAN_SPEAR, figure_egyptian_spearman)
    figure_egyptian_spearman(figure *f) : figure_enemy_spearman(f) {}

    struct static_params : public static_params_t<figure_egyptian_spearman> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_EGYPTIAN_SPEAR, "egpt_spr" }; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};

class figure_hittite_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_HITTITE_SPEARMAN, figure_hittite_spearman)
    figure_hittite_spearman(figure *f) : figure_enemy_spearman(f) {}

    struct static_params : public static_params_t<figure_hittite_spearman> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_HITTITE_SPEARMAN, "hitt_spr" }; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};

class figure_kushite_spearman : public figure_enemy_spearman {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_KUSHITE_SPEARMAN, figure_kushite_spearman)
    figure_kushite_spearman(figure *f) : figure_enemy_spearman(f) {}

    struct static_params : public static_params_t<figure_kushite_spearman> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_KUSHITE_SPEARMAN, "kush_spr" }; }
    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};