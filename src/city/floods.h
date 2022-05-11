#ifndef OZYMANDIAS_FLOODS_H
#define OZYMANDIAS_FLOODS_H

#include "core/buffer.h"

enum {
    FLOOD_STATE_IMMINENT = 1,
    FLOOD_STATE_FLOODING = 2,
    FLOOD_STATE_INUNDATED = 3,
    FLOOD_STATE_CONTRACTING = 4,
    FLOOD_STATE_RESTING = 5,
    FLOOD_STATE_FARMABLE = 6,
};


typedef struct floods_data {
    int season_initial;
    int duration_initial;
    int quality_initial;
    int season;
    int duration;
    int quality;
    int unk00;              // 00
    int quality_next;
    int quality_last;
    //
    // Pharaoh had a struct containing tile data for the updates.
    // I reimplemented it via other means.
    //
    int flood_progress;     // 0 - 30
    int unk01;              // season/floodplain_width -- probably a leftover from a previous flood system
    int state;              // 1 - 6
    int floodplain_width;   // 0 - 30
    bool has_floodplains;   // 0 - 1
} floods_data_t;

const floods_data_t * floodplain_data();

void floodplains_init();

extern const double cycles_in_a_year;
double floodplains_current_cycle();
int floodplains_current_cycle_tick();
bool is_flood_cycle_tick();
double floodplains_flooding_start_cycle();
double floodplains_flooding_end_cycle();
double floodplains_flooding_cycles_length(bool upcoming = false);

bool floodplains_is(int state);
void floodplains_adjust_next_quality(int quality);
int floodplains_expected_quality();
int floodplains_expected_month();

void floodplains_tick_update(bool calc_only);
void floodplains_day_update();

#endif //OZYMANDIAS_FLOODS_H
