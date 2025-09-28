#pragma once

#include "figuretype/figure_enemy.h"

enum e_action_enemy_archer {
    ACTION_151_ENEMY_ARCHER_INITIAL = 151,
    ACTION_152_ENEMY_ARCHER_WAITING = 152,
    ACTION_153_ENEMY_ARCHER_MARCHING = 153,
    ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE = 154,
    ACTION_155_ENEMY_ARCHER_RELOAD = 155,
};

class figure_enemy_archer : public figure_enemy {
public:
    figure_enemy_archer(figure *f) : figure_enemy(f) {}
    virtual figure_enemy_archer *dcast_enemy_archer() override { return this; }

    struct base_params_t {
        int8_t missile_attack_value;
        int8_t missile_delay;
        int8_t attack_distance;
    };

    template<typename T>
    struct static_params_t : public base_params_t, public figures::model_t<T> {
        virtual void archive_load(archive arch) override;
    };

    virtual void on_create() override;
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual bool is_archer() const override { return true; }

    virtual int8_t missile_attack_value() const { return 0; }
    virtual int8_t missile_delay() const { return 0; }
    virtual int8_t attack_distance() const { return -1; }

    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENEMIES; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    //bool fight_enemy(int category, int max_distance);
    virtual void enemy_initial(formation *m) override;
    virtual void enemy_marching(formation *m) override;
    virtual void enemy_fighting(formation *m)override;
};

class figure_barbarian_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_BARBARIAN_ARCHER, figure_barbarian_archer)
    figure_barbarian_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public static_params_t<figure_barbarian_archer> {
        e_figure_type misslie_type = FIGURE_ARROW;
    } FIGURE_STATIC_DATA_T;

    virtual e_figure_type missile_type() const override { return current_params().misslie_type; }

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_BARBARIAN_ARCHER, "barb_arch" }; }
    virtual int8_t missile_attack_value() const override { return current_params().missile_attack_value; }
    virtual int8_t missile_delay() const override { return current_params().missile_delay; }
    virtual int8_t attack_distance() const override { return current_params().attack_distance; }
};