#include <game/time.h>
#include <map/tiles.h>
#include <map/building.h>
#include <map/terrain.h>
#include <game/io/manager.h>
#include <map/floodplain.h>
#include <core/calc.h>
#include <core/random.h>
#include "floods.h"

#include "city/constants.h"
#include "city/data_private.h"
#include "scenario/data.h"
#include "buildings.h"
#include "message.h"

static floods_data_t data;

const floods_data_t *floodplain_data() {
    return &data;
}

static int randomizing_int_1 = 0;
static int randomizing_int_2 = 0;

void floodplains_init() {
    data.flood_progress = 0;
    data.unk01 = 0;
    data.state = FLOOD_STATE_FARMABLE;
    data.floodplain_width = 0;
    data.has_floodplains = false;

    data.floodplain_width = map_floodplain_rebuild_shoreorder();
    if (data.floodplain_width > 0)
        data.has_floodplains = true;

    floodplains_tick_update(true);
}

const double cycles_in_a_year = 9792.0f / 25.0f; // 391.68
static int total_tick_count() {
    return game_time_absolute_tick(true);
}
double floodplains_current_cycle() {
    return (double)(total_tick_count() + 1) / 25.0f;
}
int floodplains_current_cycle_tick() {
    return (total_tick_count() + 1) % 25;
}
bool is_flood_cycle_tick() {
    return floodplains_current_cycle_tick() == 0;
}
double floodplains_flooding_start_cycle() {
    double cycles_so_far = cycles_in_a_year * (double)game_time_year_since_start();
    double cycle_flooding_start = ((double)data.season * 105.0f) / 100.0f + 15.0f + cycles_so_far;
//    if ((double)(cycle_flooding_start - floodplains_current_cycle()) > cycles_in_a_year * 0.5)
//        cycle_flooding_start -= (int)cycles_in_a_year;
    return cycle_flooding_start;
}
double floodplains_flooding_end_cycle() {
    return floodplains_flooding_start_cycle() + (double)data.duration + (double)data.floodplain_width * 2.0f;
}
double floodplains_flooding_cycles_length(bool upcoming) {
    if (upcoming)
        return (float)data.quality_next * (float)data.floodplain_width * 0.01;
    return (float)data.quality_last * (float)data.floodplain_width * 0.01;
}

bool floodplains_is(int state) {
    return data.state == state;
}

void floodplains_adjust_next_quality(int quality) {
    data.quality_next = calc_bound(data.quality_next + quality, 0, 100);
}

int floodplains_expected_quality() {
    return data.quality_next;
}
int floodplains_expected_month() {
    return (data.season_initial / 15) - 10;
}

static void cycle_dates_recalc() {
    // if no floodplains present, return
    if (!data.has_floodplains) {
        data.state = FLOOD_STATE_FARMABLE;
        data.quality = 0;
        return;
    }

    // TODO: the cycles don't match up PERFECTLY with the original game... but close enough?
    int cycle = floodplains_current_cycle();
    int cycle_frame = floodplains_current_cycle_tick();

    // clamp and update flood quality
    if (game_time_tick() == 1 && data.state != FLOOD_STATE_FLOODING) {
        if (data.quality > data.quality_next) {
            data.quality -= 5;
            if (data.quality < data.quality_next) // clamp if over-shooting
                data.quality = data.quality_next;
        }
        if (data.quality < data.quality_next) {
            data.quality += 5;
            if (data.quality > data.quality_next) // clamp if over-shooting
                data.quality = data.quality_next;
        }
    }

    // fetch cycle & time variables
    int cycle_flooding_start = floodplains_flooding_start_cycle();
    int cycle_flooding_end = floodplains_flooding_end_cycle();
    int half_period = floodplains_flooding_cycles_length();

    // ???
    data.unk01 = data.season / 30;

    if (cycle < cycle_flooding_start - 28) {
        // normal farming period
        data.state = FLOOD_STATE_FARMABLE;
    } else if (cycle < cycle_flooding_start) {
        // flooding imminent!
        // tell all farms to DROP EVERYTHING and deliver food
        data.state = FLOOD_STATE_IMMINENT;
    } else if (cycle < cycle_flooding_start + half_period) {
        // flooding in progress
        data.state = FLOOD_STATE_FLOODING;
        data.flood_progress = 29 - (cycle - cycle_flooding_start);
    } else if (cycle < cycle_flooding_end - half_period) {
        // fully flooded
        data.state = FLOOD_STATE_INUNDATED;
        data.flood_progress = 29 - half_period;
    } else if (cycle < cycle_flooding_end) {
        // contracting
        data.state = FLOOD_STATE_CONTRACTING;
        data.flood_progress = 30 - (cycle_flooding_end - cycle);
    } else if (cycle < cycle_flooding_end + 28) {
        // contracting done, resting
        data.state = FLOOD_STATE_RESTING;
        data.flood_progress = 30;
        if (cycle == cycle_flooding_end + 18 && game_time_tick() == 0) {
            // send nilometer message!
            if (data.quality_next == 100)
                city_message_post(true, MESSAGE_FLOOD_PERFECT, 0, 0);
            else if (data.quality_next >= 75)
                city_message_post(true, MESSAGE_FLOOD_EXCELLENT, 0, 0);
            else if (data.quality_next >= 50)
                city_message_post(true, MESSAGE_FLOOD_GOOD, 0, 0);
            else if (data.quality_next >= 25)
                city_message_post(true, MESSAGE_FLOOD_MEDIOCRE, 0, 0);
            else if (data.quality_next > 0)
                city_message_post(true, MESSAGE_FLOOD_POOR, 0, 0);
            else
                city_message_post(true, MESSAGE_FLOOD_FAIL, 0, 0);
        }
    } else {
        // flooding over, farmlands available again
        data.state = FLOOD_STATE_FARMABLE;
    }

    // clamp flood progress
    if (data.flood_progress < 0)
        data.flood_progress = 0;
    else if (data.flood_progress > 30)
        data.flood_progress = 30;
}
static void update_next_flood_params() {
    // update values
    data.season = data.season_initial;      // reset to initial
    data.duration = data.duration_initial;  // reset to initial

    data.quality_last = data.quality;
    if (data.quality_last > 100)
        data.quality_last = 100; // clamp!


    // calculate the next flood quality
    int bnd[11] = {2, 3, 5, 10, 15, 30, 15, 10, 5, 3, 2};
    int arr[11] = {100, 80, 60, 40, 20, 0, -20, -40, -60, -80, -100};
    int quality_randm = 0;
    int boundary = 0;
    random_generate_next();
    int randm = (random_short() % 99 + 1);
    for (int i = 0; i < 12; ++i) {
        boundary += bnd[i];
        if (randm < boundary) {
            quality_randm = arr[i];
            break;
        }
    }
    data.quality_next += quality_randm;
    if (data.quality_next > 99)
        data.quality_next = 100;
    data.quality_next = data.quality_next & (data.quality_next < 1) - 1;
}
void floodplains_tick_update(bool calc_only) {
    cycle_dates_recalc();
    if (calc_only)
        return;

    int cycle = floodplains_current_cycle();
    int cycle_frame = floodplains_current_cycle_tick();
    int cycle_flooding_start = floodplains_flooding_start_cycle();
    int cycle_flooding_end = floodplains_flooding_end_cycle();
    int half_period = floodplains_flooding_cycles_length();

    // update at every full cycle
    if (cycle_frame == 0) {
        if (cycle == cycle_flooding_start - 49) {
            // todo: FUN_00489310();
            // This is where the game sends off the order to farms to drop everything and harvest in the OG game.
            // It has been re-implemented indirectly inside the farms' figure spawn loop.
        }
        else if (cycle == cycle_flooding_start - 1) {
            update_next_flood_params();
        }
        else if (cycle == cycle_flooding_start + data.floodplain_width) {
            // This is where the fertility gets restored in the OG game.
            // It has been re-implemented differently inside the tile flooding/update procedure.
        }
        else if (cycle == cycle_flooding_end + 1) {
            // todo: FUN_004be2b0(city_data_ptr)
            // Something to do with figures/boats?
        }
    }

    // update tiles!!
    if (cycle >= cycle_flooding_start && cycle <= cycle_flooding_start + half_period)
        map_update_floodplain_inundation(1, (29 - data.flood_progress) * 25 + cycle_frame);
    else if (cycle >= cycle_flooding_end - half_period && cycle <= cycle_flooding_end)
        map_update_floodplain_inundation(-1, (30 - data.flood_progress) * 25 - cycle_frame);

    // update grass growth
    if (cycle_frame % 10 == 0 && (cycle < cycle_flooding_start - 27 || cycle >= cycle_flooding_end - half_period))
        map_advance_floodplain_growth();
}
void floodplains_day_update() {
    if (floodplains_is(FLOOD_STATE_INUNDATED)) {
        city_data.religion.osiris_flood_will_destroy_active = 0;
    }
}

io_buffer *iob_floodplain_settings = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_INT32, &data.season_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.duration_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.season);
    iob->bind(BIND_SIGNATURE_INT32, &data.duration);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality);
    iob->bind(BIND_SIGNATURE_INT32, &data.unk00);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality_next);
    if (GamestateIO::get_file_version() >= 149)
        iob->bind(BIND_SIGNATURE_INT32, &data.quality_last);

    data.flood_progress = 30;
    data.unk00 = 0;
    data.state = FLOOD_STATE_FARMABLE;
    data.floodplain_width = 10;
});