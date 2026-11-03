#pragma once

#include "figuretype/figure_enemy_fast_sword.h"

// Egyptian war elephant. Reuses fast-sword formation/melee AI; dedicated type
// so HP/speed/AoE can diverge. March SFX skipped in figure_enemy_fast_sword
// (camel/elephant filter). Splash trampling hits adjacent soldiers (Chebyshev 1).
class figure_enemy_elephant : public figure_enemy_fast_sword {
public:
    figure_enemy_elephant(figure *f) : figure_enemy_fast_sword(f) {}

    // damage_action @0 must match parent building-smash layout.
    struct runtime_data_t {
        uint8_t damage_action = 0;
        uint8_t trample_cooldown = 0;
    } FIGURE_RUNTIME_DATA_T;

    virtual void figure_action() override;
    // OG enemy_begin(0, 1) / silent march for 0x2F.
    virtual bool drowns_on_floodplain() const override { return false; }
    virtual bool silent_on_march() const override { return true; }

    // Splash damage to adjacent player soldiers. force=true bypasses cooldown (tests).
    void trample_adjacent(bool force = false);
};

class figure_egyptian_elephant : public figure_enemy_elephant {
public:
    FIGURE_METAINFO(FIGURE_ENEMY_EGYPTIAN_ELEPHANT, figure_egyptian_elephant)
    figure_egyptian_elephant(figure *f) : figure_enemy_elephant(f) {}

    struct static_params : public base_params_t, public figure_static_params {
    } FIGURE_STATIC_DATA_T;

    virtual int8_t interval_attack_delay() const override { return current_params().interval_attack_delay; }
};
ANK_CONFIG_STRUCT(figure_egyptian_elephant::static_params, interval_attack_delay)
