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
    int quality;
    int unk00; // 00
    int quality_next;
    int quality_last;
    //
    // Pharaoh had a struct containing tile data for the updates.
    // I reimplemented it via other means.
    //
    int flood_progress;   // 0 - 30
    int unk01;            // season/floodplain_width -- probably a leftover from a previous flood system
    e_flood_state state;
    int floodplain_width; // 0 - 30
    bool has_floodplains; // 0 - 1

    int fticks;
};

extern floods_t g_floods;

void floodplains_init();

int floods_debug_period();

constexpr float CYCLES_IN_A_YEAR = 9792.0f / 25.0f; // 391.68
float floods_current_cycle();
int floods_current_subcycle();
bool tick_is_flood_cycle();
int floods_start_cycle();
int floods_end_cycle();
float floods_period_length(bool upcoming = false);

bool floodplains_is(int state);

void floodplains_adjust_next_quality(int quality);
int floodplains_expected_quality();
int floodplains_expected_month();

void floodplains_tick_update(bool calc_only);
