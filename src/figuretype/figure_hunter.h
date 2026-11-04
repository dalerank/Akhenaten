#pragma once

#include "figure/figure.h"

/**
 * Shared hunting-lodge hunter FSM (chase / hunt / pickup / pack / unload).
 * Action token names stay ACTION_*_OSTRICH_HUNTER_* for test/token stability.
 * Shoot/hit timings follow OG figure_hunter_action / figure_hunter_spear_action;
 * climate-split hunters, herd scare, and stuck-pack recovery stay remake.
 */
enum e_ostrich_hunter_action : uint16_t {
    ACTION_0_OSTRICH_HUNTER_NONE = 0,
    ACTION_8_OSTRICH_HUNTER_RECALCULATE = 8,
    ACTION_9_OSTRICH_HUNTER_CHASE_PREY = 9,
    ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL = 10,
    ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT = 11,
    ACTION_12_OSTRICH_HUNTER_MOVE_PACKED = 12,
    ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION = 13,
    ACTION_14_OSTRICH_HUNTER_UNLOADING = 14,
    ACTION_15_OSTRICH_HUNTER_HUNT = 15,
    ACTION_16_OSTRICH_HUNTER_INVESTIGATE = 16,
    ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED = 17,
    ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED = 18,

    ACTION_19_OSTRICH_HUNTER_MAX
};
using e_ostrich_hunter_action_tokens_t = token_holder<e_ostrich_hunter_action, ACTION_0_OSTRICH_HUNTER_NONE, ACTION_19_OSTRICH_HUNTER_MAX>;
extern const e_ostrich_hunter_action_tokens_t e_ostrich_hunter_action_tokens;

class figure_hunter : public figure_impl {
public:
    figure_hunter(figure *f) : figure_impl(f) {}

    struct static_params : public figure_static_params {
        uint8_t max_hunting_distance = 0;
        uint8_t attack_distance = 3;
        uint8_t animal_attack_value = 0;
        int16_t shoot_tick = 9;
        int16_t shoot_timeout = 300;
        e_figure_type prey_type = FIGURE_NONE;
        e_figure_type missile_type = FIGURE_HUNTER_SPEAR;

        void archive_init();
    };

    virtual figure_hunter *dcast_hunter() override { return this; }

    virtual e_figure_type prey_type() const { return hunter_params().prey_type; }
    virtual e_figure_type missile_type() const { return hunter_params().missile_type; }

    const static_params &hunter_params() const {
        return static_cast<const static_params &>(figure_static_params::get(base.type));
    }

    void on_spear_hit_prey(figure *prey);
    void on_spear_miss();

    static bool prey_is_downed(const figure *prey);

    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};
