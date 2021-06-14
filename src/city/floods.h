#ifndef OZYMANDIAS_FLOODS_H
#define OZYMANDIAS_FLOODS_H

#include "core/buffer.h"

typedef struct floods_data {
    int season_impose;
    int duration_impose;
    int quality_impose;
    int season;
    int duration;
    int quality;
    int unk00;
    int quality_next;
    int quality_prev;
    struct {
        int int01;      // todo:  XX 00 00 00 ??
        int int02;      //        00 00 00 00
        int id;         //        1X 00 00 00 struct index
        int int04;      //        10 47 D0 00 address
        int int05;      //        XX XX D0 01
        int int06;      //        XX XX D0 01
        int int07;      //        00 00 00 00
    } floodplains_inundation_cache[30];
    int unk_status_30; // 1E -> 13
    int unk01;         // 05
    int floodplains_state; // 06 -> 03
    int unk_status_10; // 0A
    int unk02;         // 01
} floods_data;

floods_data* give_me_da_floods_data();

int floodplains_current_cycle_tick();
int floodplains_current_cycle();
int floodplains_flooding_start_cycle();
int floodplains_flooding_end_cycle();
int floodplains_flooding_rest_period_cycle();

bool floodplains_is_coming();
bool floodplains_is_flooding();
int floodplains_expected_quality();
int floodplains_expected_month();

void floodplains_tick_update();

void floodplains_save_state(buffer *floodplain_data);
void floodplains_load_state(buffer *floodplain_data);

#endif //OZYMANDIAS_FLOODS_H
