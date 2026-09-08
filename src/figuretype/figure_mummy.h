#pragma once

#include "figure/figure.h"

enum e_mummy_action : uint16_t {
    ACTION_0_MUMMY_CREATED = 0,
    ACTION_1_MUMMY_ROAMING = 1,

    ACTION_2_MUMMY_MAX
};
using e_mummy_action_tokens_t = token_holder<e_mummy_action, ACTION_0_MUMMY_CREATED, ACTION_2_MUMMY_MAX>;
extern const e_mummy_action_tokens_t e_mummy_action_tokens;

// Undead curse walker. Scenario EVENT_TYPE_MUMMY (29) / spawn_wave.
class figure_mummy : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_MUMMY, figure_mummy)
    figure_mummy(figure *f) : figure_impl(f) {}

    struct runtime_data_t {
        // Lifetime while roaming — must not share wait_ticks (stagger / corpse / combat).
        uint16_t roam_ticks = 0;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override { /* free roam; no home return */ }
    virtual void update_animation() override;
    virtual void acquire_attack() override;

    // Spawn N mummies + one message_mummy_attacks (496). Returns first figure id, or 0.
    // Caps by k_mummy_max_wave and live mummies already on the map.
    static int spawn_wave(int count = 1);
};
