#pragma once

#include "figuretype/figure_enemy.h"

enum e_action_enemy_fast_sword {
    ACTION_151_ENEMY_FAST_SWORD_INITIAL = 151,
    ACTION_152_ENEMY_FAST_SWORD_WAITING = 152,
    ACTION_153_ENEMY_FAST_SWORD_MARCHING = 153,
    ACTION_154_ENEMY_FAST_SWORD_ATTACK = 154,
};

class figure_enemy_fast_sword : public figure_enemy {
public:
    figure_enemy_fast_sword(figure *f) : figure_enemy(f) {}

    struct base_params_t {
        uint16_t interval_attack_delay;
    };

    template<typename T>
    struct static_params_t : public base_params_t, public figures::model_t<T> {
        virtual void archive_load(archive arch) override {
            arch.r<base_params_t>(*this);
        }
    };

    struct runtime_data_t {
        uint8_t damage_action = 0;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual void update_animation() override;

    //virtual sound_key phrase_key() const override;
    virtual e_overlay get_overlay() const override { return OVERLAY_ENEMIES; }
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    virtual void enemy_initial(formation *m) override;
    virtual void enemy_marching(formation *m) override;
    virtual void enemy_fighting(formation *m) override;
    virtual bool is_attack() const override { return action_state() == ACTION_154_ENEMY_FAST_SWORD_ATTACK; }

    virtual int8_t interval_attack_delay() const { return 100; }
};
ANK_CONFIG_STRUCT(figure_enemy_fast_sword::base_params_t, interval_attack_delay)

class figure_barbarian_sword : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_BARBARIAN_SWORD, figure_barbarian_sword)
    figure_barbarian_sword(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_barbarian_sword> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_BARBARIAN_SWORD, "barb_swd" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};

class figure_assyrian_sword : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_ASSYRIAN_SWORD, figure_assyrian_sword)
    figure_assyrian_sword(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_assyrian_sword> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_ASSYRIAN_SWORD, "assr_swd" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};

class figure_canaanite_sword : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_CANAANITE_SWORD, figure_canaanite_sword)
    figure_canaanite_sword(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_canaanite_sword> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_CANAANITE_SWORD, "cana_swd" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};

class figure_hyksos_sword : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_HYKSOS_SWORDMAN, figure_hyksos_sword)
    figure_hyksos_sword(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_hyksos_sword> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_HYKSOS_SWORDMAN, "hyks_swd" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};

class figure_kushite_axeman : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_KUSHITE_AXEMAN, figure_kushite_axeman)
    figure_kushite_axeman(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_kushite_axeman> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_KUSHITE_AXEMAN, "kush_axe" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};

class figure_libian_sword : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_LIBIAN_SWORDMAN, figure_libian_sword)
    figure_libian_sword(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_libian_sword> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_HYKSOS_SWORDMAN, "libn_swd" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};

class figure_nubian_axeman : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_NUBIAN_AXEMAN, figure_nubian_axeman)
     figure_nubian_axeman(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_nubian_axeman> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_NUBIAN_AXEMAN, "nubn_axe" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};

class figure_phoenician_swordman : public figure_enemy_fast_sword {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_PHOENICIAN_SWORDMAN, figure_phoenician_swordman)    
    figure_phoenician_swordman(figure *f) : figure_enemy_fast_sword(f) {}

    struct static_params : public static_params_t<figure_phoenician_swordman> {
    } FIGURE_STATIC_DATA_T;

    virtual figure_phrase_t phrase() const override { return { FIGURE_ENEMY_PHOENICIAN_SWORDMAN, "nubn_axe" }; }
    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};