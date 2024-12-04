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
#include "dev/debug.h"

#include <cmath>

floods_t g_floods;

declare_console_command_p(startflood, game_cheat_start_flood)
void game_cheat_start_flood(std::istream &is, std::ostream &os) {
    std::string args; is >> args;

    if (args == "+") {
        g_floods.force_inundation++;
    } else if (args == "-") {
        g_floods.force_inundation--;
    } else {
        g_floods.force_inundation = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    }
}

void floods_t::init() {
    flood_progress = 0;
    unk01 = 0;
    state = FLOOD_STATE_FARMABLE;
    floodplain_width = 0;
    has_floodplains = false;

    floodplain_width = map_floodplain_rebuild_rows();
    map_floodplain_rebuild_shores();
    if (floodplain_width > 0) {
        has_floodplains = true;
    }

    tick_update(true);
}

int floods_t::debug_period() {
    return debug_year_period;
}

float floods_t::current_cycle() {
    return (gametime().absolute_tick(true) + 1) / 25.0f;
}

int floods_t::current_subcycle() {
    return (gametime().absolute_tick(true) + 1) % 25;
}

bool floods_t::is_start_cycle() {
    return current_subcycle() == 0;
}

int floods_t::start_cycle() {
    float cycles_so_far = CYCLES_IN_A_YEAR * gametime().years_since_start();
    float cycle_start = ((float)season * 105.0f) / 100.0f + 15.0f + cycles_so_far - 0.5f;
    return (int)cycle_start;
}

int floods_t::end_cycle() {
    return start_cycle() + duration + floodplain_width * 2;
}

float floods_t::period_length(bool upcoming) {
    if (upcoming) {
        return (float)quality_next * (float)floodplain_width * 0.01f;
    }

    return (float)quality_last * (float)floodplain_width * 0.01f;
}

int floods_t::cycle_compare(int c2, bool relative) {
    float diff = c2 - current_cycle();
    if (relative) {
        diff = fmod(diff, CYCLES_IN_A_YEAR);
        if (diff > 0.5 * CYCLES_IN_A_YEAR) {
            diff -= CYCLES_IN_A_YEAR;
        }
    }
    return diff;
}

bool floods_t::cycle_is(int c2, bool relative) {
    return cycle_compare(c2, relative) == 0;
}

bool floods_t::state_is(int state) {
    return state == state;
}

void floods_t::adjust_next_quality(int quality) {
    quality_next = calc_bound(quality_next + quality, 0, 100);
}

int floods_t::expected_quality() {
    return quality_next;
}

int floods_t::expected_month() {
    auto& data = g_floods;
    return (data.season_initial / 15) - 10;
}

void floods_t::reset_farms() {
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

void floods_t::cycle_states_recalc() {
    // if no floodplains present, return
    if (!has_floodplains) {
        state = FLOOD_STATE_FARMABLE;
        quality = 0;
        return;
    }

    int cycle = current_cycle();
    int cycle_frame = current_subcycle();

    // clamp and update flood quality
    if (gametime().tick == 1 && state != FLOOD_STATE_FLOODING) {
        if (quality > quality_next) {
            quality -= 5;
            if (quality < quality_next) // clamp if over-shooting
                quality = quality_next;
        }

        if (quality < quality_next) {
            quality += 5;
            if (quality > quality_next) // clamp if over-shooting
                quality = quality_next;
        }
    }

    // fetch cycle & time variables
    int cycle_start = start_cycle();
    int cycle_end = end_cycle();
    int cycle_end_LAST_YEAR = cycle_end - CYCLES_IN_A_YEAR;
    int flooding_period = period_length();

    // ???
    unk01 = season / 30;
    if (force_inundation != 0) {
       
        if (force_inundation < flood_progress) {
            state = FLOOD_STATE_INUNDATED;
            force_inundation_tick++;
            if (force_inundation_tick > 120) {
                force_inundation_tick = 0;
                flood_progress--;
            }
        } else if (force_inundation > flood_progress) {
            state = FLOOD_STATE_CONTRACTING;
            force_inundation_tick++;
            if (force_inundation_tick > 120) {
                force_inundation_tick = 0;
                flood_progress++;
            }
        }
    } else if (cycle < cycle_end_LAST_YEAR + 28) {
        // resting period from last year
        state = FLOOD_STATE_RESTING;
        flood_progress = 30;
    } else if (cycle < cycle_start - 28) {
        // normal farming period
        state = FLOOD_STATE_FARMABLE;
        flood_progress = 30;
    } else if (cycle < cycle_start) {
        // flooding imminent!
        // tell all farms to DROP EVERYTHING and deliver food
        state = FLOOD_STATE_IMMINENT;
        flood_progress = 30;
    } else if (cycle < cycle_start + flooding_period) {
        // flooding in progress
        state = FLOOD_STATE_FLOODING;
        flood_progress = 29 - (cycle - cycle_start);
    } else if (cycle < cycle_end - flooding_period) {
        // fully flooded
        state = FLOOD_STATE_INUNDATED;
        flood_progress = 29 - flooding_period;
    } else if (cycle < cycle_end) {
        // contracting
        state = FLOOD_STATE_CONTRACTING;
        flood_progress = 30 - (cycle_end - cycle);
    } else if (cycle < cycle_end + 28) {
        // contracting done, resting
        state = FLOOD_STATE_RESTING;
        flood_progress = 30;
    } else if (state != FLOOD_STATE_FARMABLE) {
        // flooding over, farmlands available again
        reset_farms();
        state = FLOOD_STATE_FARMABLE;
    }

    // clamp flood progress
    flood_progress = std::clamp(flood_progress, 0, 30);
}

void floods_t::update_next_flood_params() {
    // update values
    season = season_initial;     // reset to initial
    duration = duration_initial; // reset to initial

    quality_last = std::min(quality, 100);

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
    quality_next += quality_randm;
    quality_next = std::min(quality_next, 100);
    quality_next = quality_next & (quality_next < 1) - 1;
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

void floods_t::tick_update(bool calc_only) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Floodplains Update");
    cycle_states_recalc();

    int cycle = current_cycle();
    int subcycle = current_subcycle();
    int cycle_start = start_cycle();
    int cycle_end = end_cycle();
    int flooding_period = period_length();

    // update internal tick variables
    debug_year_period = ((cycle_start - 1) * 25) - (cycle * 25 + subcycle);
    if (force_inundation != 0) {
        fticks = flood_progress * 25;
    } else if (cycle < cycle_start) {
        fticks = 0;
    } else if (cycle >= cycle_start && cycle < cycle_start + flooding_period) {
        fticks = (cycle - cycle_start) * 25 + subcycle + 1;
    } else if (cycle >= cycle_end - flooding_period && cycle <= cycle_end) {
        fticks = (cycle_end - cycle) * 25 - subcycle - 1;
    } else {
        fticks = (flooding_period) * 25;
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
        } else if (cycle == cycle_start + floodplain_width) {
            // This is where the fertility gets restored in the OG game.
            // It has been re-implemented differently inside the tile flooding/update procedure.
        } else if (cycle == cycle_end + 1) {
            // todo: FUN_004be2b0(city_data_ptr)
            // Something to do with figures/boats?
        }
    }

    // update at the end of each day
    if (gametime().tick == 50) {
        if (state_is(FLOOD_STATE_INUNDATED)) {
            g_city.religion.osiris_flood_will_destroy_active = 0;
        }
        // send nilometer message!
        if (cycle_is(end_cycle() + 23)) {
            post_flood_prediction_message();
        }
    }

    // update tiles!!
    if ((force_inundation != 0 && force_inundation < flood_progress) || (cycle >= cycle_start && cycle <= cycle_start + flooding_period)) {
        map_floodplain_update_inundation(flood_progress, 1, fticks);
    } else if ((force_inundation != 0 && force_inundation > flood_progress) || cycle >= cycle_end - flooding_period && cycle <= cycle_end) {
        map_floodplain_update_inundation(flood_progress, -1, fticks);
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