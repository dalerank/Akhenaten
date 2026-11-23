#include "city_floods.h"

#include "building/building.h"
#include "building/building_farm.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/random.h"
#include "core/svector.h"
#include "js/js_register.h"
#include "grid/basin.h"
#include "grid/floodplain.h"
#include "grid/tiles.h"
#include "io/chunk_serializer.h"
#include "city/city.h"
#include "city_message.h"
#include "game/game_config.h"
#include "core/log.h"
#include "game/simulation.h"

#include <cmath>
#include <cctype>
#include "scenario/scenario.h"

floods_t g_floods;

void floods_t::init() {
    season_default = season_initial;
    duration_default = duration_initial;
    season_month = 0;
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

int floods_t::current_cycle() {
    const int tick_since_year
      = g_simulation.simtime.absolute_tick(true) - g_simulation.simtime.absolute_tick_year_start() + 1;
    return (tick_since_year / 25) % CYCLES_IN_A_YEAR;
}

int floods_t::current_subcycle() {
    return (g_simulation.simtime.absolute_tick(true) + 1) % 25;
}

bool floods_t::is_start_cycle() {
    return current_subcycle() == 0;
}

int floods_t::start_cycle() {
    float cycle_start = ((float)season * 105.0f) / 100.0f + 15.0f - 0.5f;
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

bool floods_t::state_is(int state) {
    return this->state == state;
}

void floods_t::adjust_next_quality(int quality) {
    quality_next = calc_bound(quality_next + quality, 0, 100);
}

int floods_t::expected_quality() {
    return quality_next;
}

int floods_t::expected_month() {
    return (season_initial / 15) - 10;
}

void floods_t::reset_farms() {
    for (building *it = building_begin(), *end = building_end(); it != end; ++it) {
        if (it->state != BUILDING_STATE_VALID) {
            continue;
        }

        if (!it->is_floodplain_farm()) {
            continue;
        }

        auto *farm = it->dcast_farm();
        if (!farm) {
            continue;
        }

        auto &d = farm->runtime_data();
        it->progress = 0;
        d.ready_production = 0;
        d.worker_id = 0;
        d.work_camp_id = 0;
        d.labor_state = LABOR_STATE_NONE;
        d.labor_days_left = 0;
        it->num_workers = 0;
        farm->restore_tiles_if_emerged();
    }
}

void floods_t::cycle_states_recalc() {
    // if no floodplains present, return
    if (!has_floodplains) {
        state = FLOOD_STATE_FARMABLE;
        flood_progress_target = 0;
        return;
    }

    int cycle = current_cycle();
    int cycle_frame = current_subcycle();

    // fetch cycle & time variables
    int cycle_start = start_cycle();
    int cycle_end = end_cycle();
    int cycle_end_LAST_YEAR = cycle_end - 380;
    int flooding_period = period_length();

    auto inrease_progress_tick = [this] {
        if (++flood_progress_tick > 20) {
            flood_progress_tick = 0;
            return true;
        }
        return false;
    };

    season_month = season / 30;
    if (force_inundation != 0) {
        if (force_inundation < flood_progress) {
            state = FLOOD_STATE_INUNDATED;
            force_inundation_tick++;
            if (force_inundation_tick > 60) {
                force_inundation_tick = 0;
                flood_progress--;
            }
        } else if (force_inundation > flood_progress) {
            state = FLOOD_STATE_CONTRACTING;
            force_inundation_tick++;
            if (force_inundation_tick > 60) {
                force_inundation_tick = 0;
                flood_progress++;
            }
        }
    } else if (cycle < cycle_end_LAST_YEAR + 28) {
        // resting period from last year
        state = FLOOD_STATE_RESTING;
        flood_progress_target = 30;
    } else if (cycle < cycle_start - 28) {
        // normal farming period
        state = FLOOD_STATE_FARMABLE;
    } else if (cycle < cycle_start) {
        // flooding imminent!
        // tell all farms to DROP EVERYTHING and deliver food
        state = FLOOD_STATE_IMMINENT;
    } else if (cycle <= cycle_start + flooding_period) {
        // flooding in progress
        state = FLOOD_STATE_FLOODING;
    } else if (cycle <= cycle_end - flooding_period) {
        // fully flooded
        state = FLOOD_STATE_INUNDATED;
        flood_progress_target = 0;
    } else if (cycle <= cycle_end) {
        // contracting
        state = FLOOD_STATE_CONTRACTING;
        flood_progress_target = 30;
    } else if (cycle <= cycle_end + 28) {
        // contracting done, resting
        state = FLOOD_STATE_RESTING;
        flood_progress_target = 30;
    } else if (state != FLOOD_STATE_FARMABLE) {
        // flooding over, farmlands available again
        reset_farms();
        state = FLOOD_STATE_FARMABLE;
    }

    if (force_inundation == 0) {
        if (flood_progress != flood_progress_target && inrease_progress_tick()) {
            flood_progress += (flood_progress > flood_progress_target) ? -1 : +1;
        }
    }

    // clamp flood progress
    flood_progress = std::clamp(flood_progress, 0, 30);
    flood_progress_target = std::clamp(flood_progress_target, 0, 30);
}

struct flood_quality_step_t {
    int weight;
    int delta;
};
ANK_CONFIG_STRUCT(flood_quality_step_t, weight, delta)
svector<flood_quality_step_t, 16> ANK_VARIABLE(flood_quality_steps);

// OG floods.c floodplain_settings_randomize_next_quality; the steps table lives in city/floods.js.
static int flood_randomized_quality(int quality) {
    random_generate_next();
    const int roll = random_short() % 99 + 1;
    int sum = 0;
    for (const auto& step : flood_quality_steps) {
        sum += step.weight;
        if (roll < sum) {
            return calc_bound(quality + step.delta, 0, 100);
        }
    }
    return calc_bound(quality, 0, 100);
}

void floods_t::update_next_flood_params() {
    season = season_initial;     // reset to initial
    duration = duration_initial; // reset to initial

    quality_last = quality_current;

    quality_current = quality_next;
    quality_next = flood_randomized_quality(quality_initial);
}

void floods_t::post_flood_prediction_message() {
    if (g_scenario.env.hide_nilometer) {
        return;
    }

    // Enhanced mute: swallow modal flood prediction. If OG Flood bit is Banner,
    // still post so the player gets a non-modal banner (I2).
    if (game_features::gameui_disable_nilometer_popups.to_bool()
        && !popup_messages_want_banner(POPUP_MSG_FLOOD)) {
        return;
    }

    if (quality_next == 100) {
        messages::popup("message_perfect_inundation", 0, 0);
    } else if (quality_next >= 75) {
        messages::popup("message_excellent_inundation", 0, 0);
    } else if (quality_next >= 50) {
        messages::popup("message_good_inundation", 0, 0);
    } else if (quality_next >= 25) {
        messages::popup("message_mediocre_inundation", 0, 0);
    } else if (quality_next > 0) {
        messages::popup("message_poor_inundation", 0, 0);
    } else {
        messages::popup("message_no_inundation", 0, 0);
    }
}

void floods_t::tick_update(bool calc_only) {
    OZZY_PROFILER_FUNCTION();
    cycle_states_recalc();

    int cycle = current_cycle();
    int subcycle = current_subcycle();
    int cycle_start = start_cycle();
    int cycle_end = end_cycle();
    int flooding_period = period_length();

    // update internal tick variables
    debug_year_period = ((cycle_start - 1) * 25) - (cycle * 25 + subcycle);
    if (force_inundation != 0) {
        fticks = flood_progress * 25 - 1;
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
        if (!calc_only && cycle == cycle_start - 49) {
            building_farm::food_warning();
        }
        if (cycle == cycle_start - 1) {
            if (!calc_only) {
                update_next_flood_params();
                post_flood_prediction_message();
            }
        } else if (cycle == cycle_start) {
            // Osiris "next flood destroys farms" also overruns perimeter dikes once.
            // Perfect/Excellent quality alone does NOT breach — that is a gift, not a disaster.
            if (!calc_only
                && game_features::gameplay_enhanced_flood_basins.to_bool()
                && g_city.religion.osiris_flood_will_destroy_active > 0) {
                const int max_tiles = 1 + (anti_scum_random_15bit() % 3); // 1..3
                int first_offset = -1;
                const int removed = map_basin_breach_perimeter(max_tiles, &first_offset);
                if (removed > 0) {
                    messages::popup("message_dike_breach", 0, first_offset >= 0 ? first_offset : 0);
                }
            }
        } else if (cycle == cycle_start + floodplain_width) {
            // This is where the fertility gets restored in the OG game.
            // It has been re-implemented differently inside the tile flooding/update procedure.
        } else if (cycle == cycle_end + 1) {
            g_city.fishing_points.reset();
        }
    }

    // update at the end of each day
    if (g_simulation.simtime.tick == 50) {
        if (state_is(FLOOD_STATE_INUNDATED)) {
            g_city.religion.osiris_flood_will_destroy_active = 0;
        }
    }

    // update tiles!!
    if (force_inundation != 0) {
        if (flood_progress != force_inundation) {
            int delta = (flood_progress > force_inundation) ? 1 : -1;
            map_floodplain_update_inundation(flood_progress, delta, fticks);
        }
    } else {
        if (flood_progress != flood_progress_target) {
            int delta = (flood_progress > flood_progress_target) ? 1 : -1;
            map_floodplain_update_inundation(flood_progress, delta, fticks);
        }
    }

    // update grass growth
    if ((subcycle % flood_multiplier_grow == 0) && (cycle < cycle_start - 27 || cycle >= cycle_end - 24)) {
        map_floodplain_advance_growth();
    }

    map_floodplain_sub_growth();
}
