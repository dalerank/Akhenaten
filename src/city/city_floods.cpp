#include "city_floods.h"

#include "building/building.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/random.h"
#include "game/time.h"
#include "grid/floodplain.h"
#include "grid/tiles.h"
#include "io/manager.h"
#include "city/city.h"
#include "message.h"

#include <cmath>

floods_t g_floods;

static int flood_multiplier_grow = 20;
static int randomizing_int_1 = 0;
static int randomizing_int_2 = 0;

void floodplains_init() {
    auto& data = g_floods;
    data.flood_progress = 0;
    data.unk01 = 0;
    data.state = FLOOD_STATE_FARMABLE;
    data.floodplain_width = 0;
    data.has_floodplains = false;

    data.floodplain_width = map_floodplain_rebuild_rows();
    map_floodplain_rebuild_shores();
    if (data.floodplain_width > 0) {
        data.has_floodplains = true;
    }

    floodplains_tick_update(true);
}

static int debug_year_period = 99;

int floods_debug_period() {
    return debug_year_period;
}

float floods_current_cycle() {
    return (gametime().absolute_tick(true) + 1) / 25.0f;
}

int floods_current_subcycle() {
    return (gametime().absolute_tick(true) + 1) % 25;
}

bool tick_is_flood_cycle() {
    return floods_current_subcycle() == 0;
}
int floods_start_cycle() {
    auto& data = g_floods;
    float cycles_so_far = CYCLES_IN_A_YEAR * gametime().years_since_start();
    float cycle_start = ((float)data.season * 105.0f) / 100.0f + 15.0f + cycles_so_far - 0.5f;
    return (int)cycle_start;
}

int floods_end_cycle() {
    auto& data = g_floods;
    return floods_start_cycle() + data.duration + data.floodplain_width * 2;
}

float floods_period_length(bool upcoming) {
    auto& data = g_floods;
    if (upcoming)
        return (float)data.quality_next * (float)data.floodplain_width * 0.01f;
    return (float)data.quality_last * (float)data.floodplain_width * 0.01f;
}

int cycle_compare(int c2, bool relative = true) {
    double diff = c2 - floods_current_cycle();
    if (relative) {
        diff = fmod(diff, CYCLES_IN_A_YEAR);
        if (diff > 0.5 * CYCLES_IN_A_YEAR)
            diff -= CYCLES_IN_A_YEAR;
    }
    return diff;
}

bool cycle_is(int c2, bool relative = true) {
    return cycle_compare(c2, relative) == 0;
}

bool floodplains_is(int state) {
    auto& data = g_floods;
    return data.state == state;
}

void floodplains_adjust_next_quality(int quality) {
    auto& data = g_floods;
    data.quality_next = calc_bound(data.quality_next + quality, 0, 100);
}

int floodplains_expected_quality() {
    auto& data = g_floods;
    return data.quality_next;
}

int floodplains_expected_month() {
    auto& data = g_floods;
    return (data.season_initial / 15) - 10;
}

static void floodplains_reset_farms() {
    for (building *it = building_begin(), *end = building_end(); it != end; ++it) {
        if (it->state != BUILDING_STATE_VALID) {
            continue;
        }

        if (!building_is_floodplain_farm(*it)) {
            continue;
        }

        it->data.industry.progress = 0;
        it->data.industry.ready_production = 0;
        it->data.industry.worker_id = 0;
        it->data.industry.work_camp_id = 0;
        it->data.industry.labor_state = LABOR_STATE_NONE;
        it->data.industry.labor_days_left = 0;
        it->num_workers = 0;
    }
}

static void cycle_states_recalc() {
    auto &data = g_floods;
    // if no floodplains present, return
    if (!data.has_floodplains) {
        data.state = FLOOD_STATE_FARMABLE;
        data.quality = 0;
        return;
    }

    int cycle = floods_current_cycle();
    int cycle_frame = floods_current_subcycle();

    // clamp and update flood quality
    if (gametime().tick == 1 && data.state != FLOOD_STATE_FLOODING) {
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
    int cycle_start = floods_start_cycle();
    int cycle_end = floods_end_cycle();
    int cycle_end_LAST_YEAR = cycle_end - CYCLES_IN_A_YEAR;
    int flooding_period = floods_period_length();

    // ???
    data.unk01 = data.season / 30;
    if (cycle < cycle_end_LAST_YEAR + 28) {
        // resting period from last year
        data.state = FLOOD_STATE_RESTING;
        data.flood_progress = 30;
    } else if (cycle < cycle_start - 28) {
        // normal farming period
        data.state = FLOOD_STATE_FARMABLE;
        data.flood_progress = 30;
    } else if (cycle < cycle_start) {
        // flooding imminent!
        // tell all farms to DROP EVERYTHING and deliver food
        data.state = FLOOD_STATE_IMMINENT;
        data.flood_progress = 30;
    } else if (cycle < cycle_start + flooding_period) {
        // flooding in progress
        data.state = FLOOD_STATE_FLOODING;
        data.flood_progress = 29 - (cycle - cycle_start);
    } else if (cycle < cycle_end - flooding_period) {
        // fully flooded
        data.state = FLOOD_STATE_INUNDATED;
        data.flood_progress = 29 - flooding_period;
    } else if (cycle < cycle_end) {
        // contracting
        data.state = FLOOD_STATE_CONTRACTING;
        data.flood_progress = 30 - (cycle_end - cycle);
    } else if (cycle < cycle_end + 28) {
        // contracting done, resting
        data.state = FLOOD_STATE_RESTING;
        data.flood_progress = 30;
    } else if (data.state != FLOOD_STATE_FARMABLE) {
        // flooding over, farmlands available again
        floodplains_reset_farms();
        data.state = FLOOD_STATE_FARMABLE;
    }

    // clamp flood progress
    if (data.flood_progress < 0) {
        data.flood_progress = 0;
    } else if (data.flood_progress > 30) {
        data.flood_progress = 30;
    }
}
static void update_next_flood_params() {
    auto& data = g_floods;

    // update values
    data.season = data.season_initial;     // reset to initial
    data.duration = data.duration_initial; // reset to initial

    data.quality_last = data.quality;
    if (data.quality_last > 100) {
        data.quality_last = 100; // clamp!
    }

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
    if (data.quality_next > 99) {
        data.quality_next = 100;
    }
    data.quality_next = data.quality_next & (data.quality_next < 1) - 1;
}
static void post_flood_prediction_message() {
    auto& data = g_floods;

    if (data.quality_next == 100) {
        city_message_post(true, MESSAGE_FLOOD_PERFECT, 0, 0);
    } else if (data.quality_next >= 75) {
        city_message_post(true, MESSAGE_FLOOD_EXCELLENT, 0, 0);
    } else if (data.quality_next >= 50) {
        city_message_post(true, MESSAGE_FLOOD_GOOD, 0, 0);
    } else if (data.quality_next >= 25) {
        city_message_post(true, MESSAGE_FLOOD_MEDIOCRE, 0, 0);
    } else if (data.quality_next > 0) {
        city_message_post(true, MESSAGE_FLOOD_POOR, 0, 0);
    } else {
        city_message_post(true, MESSAGE_FLOOD_FAIL, 0, 0);
    }
}

void floodplains_tick_update(bool calc_only) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Floodplains Update");
    auto& data = g_floods;

    cycle_states_recalc();

    int cycle = floods_current_cycle();
    int subcycle = floods_current_subcycle();
    int cycle_start = floods_start_cycle();
    int cycle_end = floods_end_cycle();
    int flooding_period = floods_period_length();

    // update internal tick variables
    debug_year_period = ((cycle_start - 1) * 25) - (cycle * 25 + subcycle);
    if (cycle < cycle_start) {
        g_floods.fticks = 0;
    } else if (cycle >= cycle_start && cycle < cycle_start + flooding_period) {
        g_floods.fticks = (cycle - cycle_start) * 25 + subcycle + 1;
    } else if (cycle >= cycle_end - flooding_period && cycle <= cycle_end) {
        g_floods.fticks = (cycle_end - cycle) * 25 - subcycle - 1;
    } else {
        g_floods.fticks = (flooding_period) * 25;
    }

    if (calc_only) {
        return;
    }

    // update at every full cycle
    if (subcycle == 0) {
        if (cycle == cycle_start - 49) {
            // todo: FUN_00489310();
            // This is where the game sends off the order to farms to drop everything and harvest in the OG game.
            // It has been re-implemented indirectly inside the farms' figure spawn loop.
        } else if (cycle == cycle_start - 1) {
            if (!calc_only)
                update_next_flood_params();
        } else if (cycle == cycle_start + data.floodplain_width) {
            // This is where the fertility gets restored in the OG game.
            // It has been re-implemented differently inside the tile flooding/update procedure.
        } else if (cycle == cycle_end + 1) {
            // todo: FUN_004be2b0(city_data_ptr)
            // Something to do with figures/boats?
        }
    }

    // update at the end of each day
    if (gametime().tick == 50) {
        if (floodplains_is(FLOOD_STATE_INUNDATED)) {
            g_city.religion.osiris_flood_will_destroy_active = 0;
        }
        // send nilometer message!
        if (cycle_is(floods_end_cycle() + 23)) {
            post_flood_prediction_message();
        }
    }

    // update tiles!!
    if (cycle >= cycle_start && cycle <= cycle_start + flooding_period) {
        int fticks = (cycle - cycle_start) * 25 + subcycle + 1;
        map_floodplain_update_inundation(data.flood_progress, 1, fticks);

    } else if (cycle >= cycle_end - flooding_period && cycle <= cycle_end) {
        int fticks = (cycle_end - cycle) * 25 - subcycle + 25;
        map_floodplain_update_inundation(data.flood_progress, -1, fticks);
    }

    // update grass growth
    if (subcycle % flood_multiplier_grow == 0 && (cycle < cycle_start - 27 || cycle >= cycle_end - 24)) {
        map_floodplain_advance_growth();
    }

    map_floodplain_sub_growth();
}

io_buffer* iob_floodplain_settings = new io_buffer([](io_buffer* iob, size_t version) {
    auto& data = g_floods;

    iob->bind(BIND_SIGNATURE_INT32, &data.season_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.duration_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.season);
    iob->bind(BIND_SIGNATURE_INT32, &data.duration);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality);
    iob->bind(BIND_SIGNATURE_INT32, &data.unk00);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality_next);
    if (FILEIO.get_file_version() >= 149) {
        iob->bind(BIND_SIGNATURE_INT32, &data.quality_last);
    }

    data.flood_progress = 30;
    data.unk00 = 0;
    data.state = FLOOD_STATE_FARMABLE;
    data.floodplain_width = 10;
});