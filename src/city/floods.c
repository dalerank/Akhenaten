#include <game/time.h>
#include <map/tiles.h>
#include "floods.h"

#include "city/constants.h"
#include "city/data_private.h"
#include "scenario/data.h"

static floods_data data;

floods_data* give_me_da_floods_data() {
    return &data;
}

static int cycle = 0;
static int cycle_tick = 0;

const double randomizing_double = 391.68; //0x40787ae147ae147b; // hardcoded
static int randomizing_int_1 = 0;
static int randomizing_int_2 = 0;

int floodplains_current_cycle_tick() {
    return cycle_tick;
}
int floodplains_current_cycle() {
    return cycle;
}
int floodplains_flooding_start_cycle() {
    int h = (int)(long long)((float)give_me_da_time()->year - (short)scenario.start_year) * (float)randomizing_double;
    return data.season * 1.05 + 15 + h;
}
int floodplains_flooding_end_cycle() {
    return floodplains_flooding_start_cycle() + data.duration + data.unk_status_10 * 2;
}
int floodplains_flooding_rest_period_cycle() {
    return (float)data.quality_prev * (float)data.unk_status_10 * 0.01;
}

bool floodplains_is_coming() {
    if (cycle == floodplains_flooding_start_cycle() - 1)
        return true;
    return false;
}
bool floodplains_is_flooding() {
    int flooding_cycle = floodplains_flooding_start_cycle();
    if (cycle >= flooding_cycle && cycle <= flooding_cycle + data.duration_impose)
        return true;
    return false;
}
int floodplains_expected_quality() {
    return data.quality_next;
}
int floodplains_expected_month() {
    return data.season_impose;
}

void FUN_004bd580(int* address, char param_1, unsigned int param_2, char param_3);

static void do_the_flooding(int state) {
    // todo
}
void floodplains_tick_update() {

//    int status_data_10 = data.unk_status_10; // todo ????
//    int status_data_30 = data.unk_status_30;
//    int* status_plains = &data_extra.floodplains_state;

    int total_ticks = game_time_absolute_tick();
    cycle = total_ticks / 25;
    cycle_tick = total_ticks % 25;

    // ???
    if (data.unk_status_30 == 0) {
        data.floodplains_state = 6;
        data.quality = 0;
        return;
    }

    // clamp and update flood quality
    if (game_time_tick() == 1 && data.floodplains_state != 2) {

        if (data.quality_next < data.quality) {
            if (data.quality_next < data.quality - 5)
                data.quality -= 5;
        } else if (data.quality_next > data.quality && data.quality_next < data.quality + 5)
            data.quality += 5;
    }

    // fetch cycle & time variables
    int cycle_flooding_start = floodplains_flooding_start_cycle();
    int cycle_flooding_end = floodplains_flooding_end_cycle();
    int rest_period = floodplains_flooding_rest_period_cycle();
    // ????
    if ((double)(cycle_flooding_start - cycle) > randomizing_double * 0.5) {
        cycle_flooding_start -= (int)randomizing_double;
        cycle_flooding_end -= - (int)randomizing_double;
    }

    // update at every tick
    data.unk01 = data.season / 30;

    if (cycle < cycle_flooding_start - 28) {
        // normal farming period
        data.floodplains_state = 6;
    } else if (cycle < cycle_flooding_start) {
        // flooding imminent!
        // tell all farms to DROP EVERYTHING and deliver food
        data.floodplains_state = 1;
    } else if (cycle < cycle_flooding_start + rest_period) {
        // flooding in progress
        data.floodplains_state = 2;
        data.unk_status_30 = 29 - (cycle - cycle_flooding_start);
    } else if (cycle < cycle_flooding_end - rest_period) {
        // fully flooded
        data.floodplains_state = 3;
        data.unk_status_30 = 29 - rest_period;
    } else if (cycle < cycle_flooding_end) {
        // contracting
        data.floodplains_state = 4;
        data.unk_status_30 = 30 - (cycle_flooding_end - cycle);
    } else if (cycle < cycle_flooding_end + 28) {
        // contracting done, resting
        data.floodplains_state = 5;
        data.unk_status_30 = 30;
    } else {
        // flooding over, farmlands available again
        data.floodplains_state = 6;
    }

    // clamp update status_30 ...
    if (data.unk_status_30 < 0)
        data.unk_status_30 = 0;
    else if (data.unk_status_30 > 30)
        data.unk_status_30 = 30;

    // update at every full cycle
    if (cycle_tick == 0) {
        if (cycle == cycle_flooding_start - 49) {
            // todo: FUN_00489310();
        }
        else if (cycle == cycle_flooding_start - 1) {
            // update values over to next flood
            data.season = data.season_impose;
            data.duration = data.duration_impose;
            data.quality = data.quality_next;

            // TEMP!!!!!
            data.quality_prev = 100;

            //////////////////////////////////////////////////////////////////

            // todo: quality?
//            if ((&DAT_00ea4cd8)[DAT_00ea9c18 * 0x24ec] != 0) {
//                if (!FUN_004c4e50((&DAT_00ea4f8c)[DAT_00ea9c18 * 0x1276]))
//                    data.quality_prev += + 10;
//            }
            if (data.quality_prev > 100)
                data.quality_prev = 100;

            //////////////////////////////////////////////////////////////////

            // todo: season?
//            FUN_004bd0b0(data.season_impose);
        }
        else if (cycle == cycle_flooding_end + 1) {
            // calculate next flood quality
            // post message
            // todo: FUN_004be2b0(city_data_ptr)
        }
        else if (cycle < cycle_flooding_start + rest_period) {
            // todo: unk_flag_00ea9c1c = 1
        }
        else if (cycle < cycle_flooding_end - rest_period) {
            if (cycle == cycle_flooding_start + data.unk_status_10) {
                // todo ?????
//                int* address = &data.quality_impose;
//                for (int i = 0; i < 30; i++) {
//                    *address = 0;
//                    address += 7;
//                }
            }
        }
        else  {
            // todo: unk_flag_00ea9c1c = 1
        }

    }

    // update tiles!!!!!!!!!!!!!! ACTUAL!!!!!!!! PROPER!!!!!!!!!!!!
    if (cycle >= cycle_flooding_start && cycle <= cycle_flooding_start + rest_period)
        map_update_floodplain_inundation(1, (29 - data.unk_status_30) * 25 + cycle_tick);
    else if (cycle >= cycle_flooding_end - rest_period && cycle <= cycle_flooding_end)
        map_update_floodplain_inundation(-1, (30 - data.unk_status_30) * 25 - cycle_tick);

    // update floodplain tiles!!!!!!
    int SHIFT_1 = randomizing_int_1; // 005de75c
    data.unk_status_30 = data.unk_status_30;
    if (cycle >= cycle_flooding_end - data.unk_status_10) {
        int temp_past_end = cycle - cycle_flooding_end + data.unk_status_10;
        if (temp_past_end < 0)
            temp_past_end += randomizing_double;

        long long weird_tick_count = ((float)total_ticks / 4.166666);
        SHIFT_1 = (int)
                ((long long)((unsigned long long)(unsigned int)((int)weird_tick_count >> 0x1f) << 0x20 | weird_tick_count & 0xffffffff) % 6) +
                temp_past_end * 6;

        int SHIFT_2 = data.unk_status_10 * 60;
        int SHIFT_4 = SHIFT_2;
        if (SHIFT_1 <= SHIFT_2)
            SHIFT_4 = SHIFT_1;
        if ((SHIFT_1 < SHIFT_2) && (SHIFT_4 != randomizing_int_2)) {
            SHIFT_2 = SHIFT_4 % data.unk_status_10;
            if (data.unk_status_10 - 1 <= SHIFT_4 % data.unk_status_10)
                SHIFT_2 = data.unk_status_10 - 1;
            SHIFT_2 = data.unk_status_30 - SHIFT_2;
            randomizing_int_2 = SHIFT_4;
            if ((SHIFT_2 > -1) && (SHIFT_2 < data.unk_status_30)) {


//                todo: FUN_004bde00((void *)(city_data_ptr + 0x32c64 + cycle_half_way_done * 0x1c));
//                void __fastcall FUN_004bde00(void *param_1)
//                {
//                    if (*(int *)((int)param_1 + 4) < 5) {
//                        *(int *)((int)param_1 + 4) = *(int *)((int)param_1 + 4) + 1;
//                        FUN_004bd580(param_1,'\0',1,'\x01');
//                    }
//                    return;
//                }


                // param_1 = (void *)(city_data_ptr + 0x32c64 + SHIFT_2 * 0x1c)                 ...
                // param_1 = (void *)(&data.duration_impose + SHIFT_2 * 28)         ...


                // take void pointer, convert pointer to int (raw 4-byte address num)
                // if (*(int *)((int)param_1 + 4) < 5)                                          ...
                // if (*(&data.duration_impose + SHIFT_2 * 28 + 4) < 5)             ...


                int* p = &data.duration_impose + SHIFT_2 * 28;
                int* a = p + 4;
                if (*a < 5) {
                    *a++;
                    FUN_004bd580(p,'\0',1,'\x01');
                }
//                if (*(int *)((int)param_1 + 4) < 5) {
//                    *(int *)((int)param_1 + 4) = *(int *)((int)param_1 + 4) + 1;
//                    FUN_004bd580(param_1,'\0',1,'\x01');
//                }
            }
        }
    }
    randomizing_int_1 = SHIFT_1; // 005de75c

    int flag = ((total_ticks % 25) * 100) / 25;
    int* address = &data.quality_prev + 1;
    if (data.floodplains_state != 2) {
        if (data.floodplains_state != 4)
            return;

        FUN_004bd580((address + data.unk_status_30 * 28), '\0', flag, '\0');
        // todo: unk_flag2_00bc8684 = 0;
        return;
    }
    FUN_004bd580((address + data.unk_status_30 * 28), '\x01', flag, '\0');
    // todo: unk_flag2_00bc8684 = 0;
}

void FUN_004bd580(int* address, char param_1, unsigned int param_2, char param_3) {
    int32_t iVar1;
    int32_t iVar2;
    int32_t* this_00;
    long long lVar4;

/* WARNING: Load size is inaccurate */
    int32_t value = *address;
    int32_t* address_shift_3byte = address + 24;
    int32_t* address_shift_2byte = address + 16;
    if (value != 0) {
        if (*address_shift_3byte == 0) {
            if (*address_shift_2byte == 0)
                iVar2 = 0;
            else
                iVar2 = *reinterpret_cast<int32_t*>(*address_shift_2byte + 0xc);

            *address_shift_3byte = iVar2;

            if ((iVar2 != 0) && (param_2 != 0)) {
                iVar2 = (((param_2 < 0) - 1 & param_2) * value) / 100;
                do {
                    if (iVar2 == 0) break;
                    iVar1 = **reinterpret_cast<int32_t**>(*address_shift_3byte + 4);
                    if (iVar1 == 0)
                        *address_shift_3byte = 0;
                    else
                        *address_shift_3byte = *(reinterpret_cast<int32_t*>(iVar1) + 0xc);

                    iVar2 = iVar2 + -1;
                } while (*address_shift_3byte != 0);
            }
        }
        this_00 = *(int32_t **) address_shift_3byte;
        if (this_00 != (int32_t *) 0x0) {
            if (param_3 == '\0') {
                lVar4 = (long long)(((float) value * 100.0) / 2500.0);
                iVar2 = (int32_t)lVar4 + 1;
                value = 1;
                if (0 < iVar2)
                    value = iVar2;

            }
            do {
                if (value == 0)
                    return;

                if (*reinterpret_cast<char*>(*(this_00) + 0x18) != '\0') {
                    int a = 0;
//                    FUN_004bd680(this_00, param_1); // actually update tiles
                }
                iVar2 = **(int **) (*reinterpret_cast<int32_t*>(address_shift_3byte) + 4);
                if (iVar2 == 0)
                    *address_shift_3byte = 0;
                else
                    *address_shift_3byte = *(reinterpret_cast<int32_t*>(iVar2) + 0xc);

                this_00 = *(int32_t**)address_shift_3byte;
                value = value + -1;
            } while (this_00 != (int32_t*)0x0);
        }
    }
    return;
}


void floodplains_save_state(buffer *floodplain_data) {
    // todo
}
void floodplains_load_state(buffer *floodplain_data) {
    data.season_impose = floodplain_data->read_i32();
    data.duration_impose = floodplain_data->read_i32();
    data.quality_impose = floodplain_data->read_i32();
    data.season = floodplain_data->read_i32();
    data.duration = floodplain_data->read_i32();
    data.quality = floodplain_data->read_i32();
    data.unk00 = floodplain_data->read_i32();
    data.quality_next = floodplain_data->read_i32();
    data.quality_prev = floodplain_data->read_i32();

    data.unk_status_30 = 30;
    data.unk00 = 0;
    data.floodplains_state = 6;
    data.unk_status_10 = 10;
}