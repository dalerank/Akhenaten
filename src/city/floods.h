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
    int unk01;              // 05
    int state;              // 1 - 6
    int floodplain_width;   // 0 - 30
    int unk02;              // 01
} floods_data;

floods_data* give_me_da_floods_data();

void floodplains_init();

int floodplains_current_cycle_tick();
int floodplains_current_cycle();
int floodplains_flooding_start_cycle();
int floodplains_flooding_end_cycle();
int floodplains_flooding_rest_period_cycle();

bool floodplains_is(int state);
int floodplains_expected_quality();
int floodplains_expected_month();

int floodplains_time_to_deliver();

void floodplains_tick_update();

void floodplains_save_state(buffer *floodplain_data);
void floodplains_load_state(buffer *floodplain_data);

#endif //OZYMANDIAS_FLOODS_H
