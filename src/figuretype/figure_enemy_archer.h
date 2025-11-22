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
        e_figure_type missile_type = FIGURE_ARROW;
    };

    virtual const base_params_t &base_params() const = 0;

    virtual void on_create() override;
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;
    virtual bool is_archer() const override { return true; }

    virtual int8_t missile_attack_value() const { return base_params().missile_attack_value; }
    virtual int8_t missile_delay() const { return base_params().missile_delay;}
    virtual int8_t attack_distance() const { return base_params().attack_distance; }
    virtual e_figure_type missile_type() const override { return base_params().missile_type; }

    virtual bool is_attack() const override { return action_state() == ACTION_154_ENEMY_ARCHER_SHOOT_MISSILE; }

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

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_barbarian_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_assyrian_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_ASSYRIAN_ARCHER, figure_assyrian_archer)
    figure_assyrian_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_assyrian_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_canaanite_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_CANAANITE_ARCHER, figure_canaanite_archer)
    figure_canaanite_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_canaanite_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_egyptian_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_EGYPTIAN_ARCHER, figure_egyptian_archer)
    figure_egyptian_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_egyptian_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_hittite_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_HITTITE_ARCHER, figure_hittite_archer)
    figure_hittite_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_hittite_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_hyksos_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_HYKSOS_ARCHER, figure_hyksos_archer)
    figure_hyksos_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_hyksos_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_libian_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_LIBIAN_ARCHER, figure_libian_archer)
    figure_libian_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_libian_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_nubian_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_NUBIAN_ARCHER, figure_nubian_archer)
    figure_nubian_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_nubian_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_persian_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_PERSIAN_ARCHER, figure_persian_archer)
    figure_persian_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_persian_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_roman_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_ROMAN_ARCHER, figure_roman_archer)
    figure_roman_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_roman_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)

class figure_seapeople_archer : public figure_enemy_archer {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_SEAPEOPLE_ARCHER, figure_seapeople_archer)
    figure_seapeople_archer(figure *f) : figure_enemy_archer(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    const base_params_t &base_params() const { return static_cast<const base_params_t &>(current_params()); }
};
ANK_CONFIG_STRUCT(figure_seapeople_archer::static_params,
    missile_attack_value, missile_delay, attack_distance, missile_type)