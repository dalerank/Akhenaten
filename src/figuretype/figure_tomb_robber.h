#pragma once

#include "figure/figure.h"

enum e_tomb_robber_action {
    // OG figure_tomb_robber_action (military.c): wait → walk 2× → rob → die.
    ACTION_8_TOMB_ROBBER_WAITING = 8,
    ACTION_9_TOMB_ROBBER_GOING_TO_TOMB = 9,
    // Remake (Enhanced: gameplay_change_tomb_robber_remake).
    ACTION_120_TOMB_ROBBER_CREATED = 120,
    ACTION_121_TOMB_ROBBER_GOING_TO_TOMB = 121,
    ACTION_122_TOMB_ROBBER_STEALING = 122,
    ACTION_123_TOMB_ROBBER_FLEEING = 123,
    ACTION_124_TOMB_ROBBER_CAUGHT = 124,
};

class figure_tomb_robber : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_TOMB_ROBER, figure_tomb_robber)
    figure_tomb_robber(figure *f) : figure_impl(f) {}
    virtual figure_tomb_robber *dcast_tomb_robber() override { return this; }

    struct runtime_data_t {
        building_id target_tomb_id = 0;
        uint8_t threat_only = 0; // remake preexisting sealed tomb — kingdom hit, no steal
        uint8_t stole = 0;
        uint8_t kill_bonus_done = 0; // OG: +1 kingdom when killed in a fight
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void on_post_load() override;
    virtual void figure_action() override;
    virtual void update_animation() override;

    // Apply steal / unfinished threat at tomb. Returns true if kingdom/provisions changed.
    bool commit_plunder();

    // Remake only: detain this robber (constable arrest). force: skip 75% roll.
    bool arrest(bool force = false);

    // Spawn helper (tests / remake monthly / crime-wave). force_gates: skip sentiment/random.
    static int try_spawn(bool force_gates = false);

    // Spawn up to `count` robbers (cap concurrent) + one crime-wave popup.
    static int spawn_wave(int count);

    // Remake monthly professional wave (dispatched ≥20, 1/24 → 2 robbers).
    static int try_professional_wave();

    // OG: burial provisions present, or unfinished mastaba/mausoleum/royal tomb.
    static bool og_possible();

    static bool city_has_stealable_provisions();
    static int city_dispatched_loads_total();
    static building *find_target_tomb(bool *out_threat_only = nullptr, tile2i origin = tile2i::invalid);
};
