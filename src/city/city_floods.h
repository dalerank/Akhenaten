#pragma once

#include "core/buffer.h"

enum e_flood_state {
    FLOOD_STATE_IMMINENT = 1,
    FLOOD_STATE_FLOODING = 2,
    FLOOD_STATE_INUNDATED = 3,
    FLOOD_STATE_CONTRACTING = 4,
    FLOOD_STATE_RESTING = 5,
    FLOOD_STATE_FARMABLE = 6,
};

struct floods_t {
    int season_initial;
    int duration_initial;
    int quality_initial;
    int season;
    int duration;
    int unk00; // 00
    int quality_next = 100;
    int quality_current = 100;
    int quality_last = 100;
    //
    // Pharaoh had a struct containing tile data for the updates.
    // I reimplemented it via other means.
    //
    int flood_progress = 30;   // 0 - 30
    int flood_progress_target; // 0 - 30
    int unk01;            // season/floodplain_width -- probably a leftover from a previous flood system
    e_flood_state state;
    int floodplain_width; // 0 - 30
    bool has_floodplains; // 0 - 1
    int flood_progress_tick = 0;

    int fticks;
    int debug_year_period = 99;
    int flood_multiplier_grow = 20;
    int randomizing_int_1 = 0;
    int randomizing_int_2 = 0;
    int force_inundation = 0;
    int force_inundation_tick = 0;

    int current_subcycle();
    bool is_start_cycle();
    void init();
    int debug_period();
    int current_cycle();
    int start_cycle();
    int end_cycle();
    float period_length(bool upcoming = false);
    bool state_is(int state);
    void adjust_next_quality(int quality);
    int expected_quality();
    int expected_month();

    void reset_farms();
    void cycle_states_recalc();
    void update_next_flood_params();
    void tick_update(bool calc_only);
    void post_flood_prediction_message();
};

extern floods_t g_floods;

constexpr int CYCLES_IN_A_YEAR = 392;



