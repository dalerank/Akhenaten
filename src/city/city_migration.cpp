#include "city_migration.h"

#include "building/building_house.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/log.h"
#include "game/game.h"
#include "game/game_events.h"
#include "js/js_game.h"

svector<city_migration_t::condition, 16> g_migration_conditions;
city_migration_defaults_t ANK_VARIABLE(migration_defaults);
svector<sentiment_step_t, 16> ANK_VARIABLE(migration_sentiment_influence);
svector<unemployment_step_t, 16> ANK_VARIABLE(migration_unemployment_percentage);
std::unordered_map<xstring, int> g_migration_cap_reasons;
std::unordered_map<xstring, std::pair<int, int>> g_migration_unemployment_cap_reasons;

e_no_immigration_reason_tokens_t ANK_CONFIG_ENUM(no_immigration_reason_tokens);

void city_migration_t::nobles_leave_city(int num_people) {
    nobles_leave_city_this_year += num_people;
}

void city_migration_t::update_status() {
    auto& params = migration_defaults;

    const auto &sentiment = g_city.sentiment;
    auto sent_it = std::find_if(migration_sentiment_influence.begin(), migration_sentiment_influence.end(), [sentiment = sentiment.value] (const auto& t) {
        return sentiment > t.s;
    });

    const int8_t unemployment_percentage = g_city.labor.unemployment_percentage;
    auto unemployment_it = std::find_if(migration_unemployment_percentage.begin(), migration_unemployment_percentage.end(), [unemployment_percentage] (const auto &t) {
        return unemployment_percentage > t.u;
    });

    int want_percentage_by_unemployments = (unemployment_it != migration_unemployment_percentage.end()) ? unemployment_it->p : 0;
    std::pair<int, int> range_percentage_by_unemployments{ -9999, 9999 };
    for (const auto &it : g_migration_unemployment_cap_reasons) {
        range_percentage_by_unemployments.first = std::max(range_percentage_by_unemployments.first, it.second.first);
        range_percentage_by_unemployments.second = std::min(range_percentage_by_unemployments.second, it.second.second);
    }
    percentage_by_unemployments = std::clamp(want_percentage_by_unemployments, range_percentage_by_unemployments.first, range_percentage_by_unemployments.second);

    percentage_by_sentiment = (sent_it != migration_sentiment_influence.end()) ? sent_it->i : 0;
    percentage = (percentage_by_sentiment + percentage_by_unemployments);

    immigration_amount_per_batch = 0;
    emigration_amount_per_batch = 0;

    int cur_population_cap = 999999;
    for (const auto &it: g_migration_cap_reasons) {
        if (it.second > 0) {
            cur_population_cap = std::min(cur_population_cap, it.second);
        }
    }

    if (population_cap > 0) {
        cur_population_cap = std::min(cur_population_cap, population_cap);
    }

    if (cur_population_cap > 0 && g_city.population.current >= cur_population_cap) {
        percentage = 0;
        if (!migration_cap && g_city.population.room_in_houses > 0) {
            events::emit(event_city_warning{ "#immigration_people_wont_come" });
        }
        migration_cap = true;
        return;
    }
    migration_cap = false;

    // war scares immigrants away
    if (g_city.figures.total_invading_enemies() > 3 && percentage > 0) {
        percentage = 0;
        invading_cap = true;
        return;
    }
    invading_cap = false;

    if (percentage > 0) {
        // immigration
        if (emigration_duration) {
            emigration_duration--;
        } else {
            immigration_amount_per_batch = calc_adjust_with_percentage<int>(params.max_newcomers_per_update, percentage);
            immigration_duration = 2;
        }
    } else if (percentage < 0) {
        // emigration
        if (immigration_duration) {
            immigration_duration--;
        } else if (g_city.population.current > 100) {
            emigration_amount_per_batch = calc_adjust_with_percentage<int>(params.max_leftovers_per_update, -percentage);
            emigration_duration = 2;
        }
    }
}

void city_migration_t::create_immigrants(int num_people) {
    int immigrated = g_city.population.create_immigrants(num_people);
    immigrated_today += immigrated;
    newcomers += immigrated_today;
    if (immigrated == 0) {
        refused_immigrants_today += num_people;
    }
}

void city_migration_t::set_unemployments_cap(xstring reason, int min, int max) {
    if (min == 0 && max == 0) {
        g_migration_unemployment_cap_reasons.erase(reason);
        return;
    }

    g_migration_unemployment_cap_reasons[reason] = { min, max };
}

void city_migration_t::set_migration_cap(xstring reason, int cap) {
    if (cap == 0) {
        g_migration_cap_reasons.erase(reason);
        return;
    }

    g_migration_cap_reasons[reason] = cap;
}

const std::unordered_map<xstring, int> &city_migration_t::get_migration_caps() {
    return g_migration_cap_reasons;
}

city_migration_defaults_t& city_migration_t::current_params() {
    return migration_defaults;
}

void city_migration_t::create_emigrants(int num_people) {
    emigrated_today += g_city.population.create_emigrants(num_people);
}

void city_migration_t::create_migrants() {
    immigrated_today = 0;
    emigrated_today = 0;
    refused_immigrants_today = 0;

    auto& params = migration_defaults;
    if (immigration_amount_per_batch > 0) {
        if (immigration_amount_per_batch >= params.max_immigration_amount_per_batch) {
            create_immigrants(immigration_amount_per_batch);

        } else if (immigration_amount_per_batch + immigration_queue_size >= params.max_immigration_amount_per_batch) {
            create_immigrants(immigration_amount_per_batch + immigration_queue_size);
            immigration_queue_size = 0;

        } else { // queue them for next round
            immigration_queue_size += immigration_amount_per_batch;
        }
    }

    if (emigration_amount_per_batch > 0) {
        if (emigration_amount_per_batch >= params.max_emigration_amount_per_batch) {
            create_emigrants(emigration_amount_per_batch);

        } else if (emigration_amount_per_batch + emigration_queue_size >= params.max_emigration_amount_per_batch) {
            create_emigrants(emigration_amount_per_batch + emigration_queue_size);
            emigration_queue_size = 0;
            if (!emigration_message_shown) {
                emigration_message_shown = 1;
                //                city_message_post(true, MESSAGE_EMIGRATION, 0, 0);
            }
        } else { // queue them for next round
            emigration_queue_size += emigration_amount_per_batch;
        }
    }

    immigration_amount_per_batch = 0;
    emigration_amount_per_batch = 0;
}

void city_migration_t::reset() {
    g_migration_conditions.clear();
    g_migration_cap_reasons.clear();
    g_migration_unemployment_cap_reasons.clear();
    migration_cap = false;
    invading_cap = false;
}

void city_migration_t::update_conditions() {
    for (const auto &condition : g_migration_conditions) {
        condition(*this);
    }
}

void city_migration_t::update_month() {
    int houses_total = 0;
    int houses_with_room = 0;
    int houses_no_entry = 0;
    int houses_immigrant_slot = 0;
    int houses_immigrant_slot_dead = 0;
    int vacant_lots = 0;
    int vacant_lots_with_room = 0;
    int room_reachable = 0;

    buildings_house_do([&](building_house *house) {
        if (house->state() != BUILDING_STATE_VALID) {
            return;
        }

        ++houses_total;
        const int room = house->population_room();
        const bool no_entry = house->distance_from_entry() <= 0;
        const bool vacant = house->is_vacant_lot();

        if (vacant) {
            ++vacant_lots;
            if (room > 0) {
                ++vacant_lots_with_room;
            }
        }

        if (no_entry) {
            ++houses_no_entry;
        } else if (room > 0) {
            ++houses_with_room;
            room_reachable += room;
        }

        if (house->base.has_figure(BUILDING_SLOT_IMMIGRANT, -1)) {
            ++houses_immigrant_slot;
            if (house->get_figure(BUILDING_SLOT_IMMIGRANT)->state != FIGURE_STATE_ALIVE) {
                ++houses_immigrant_slot_dead;
            }
        }
    });

    logs::info("[migration] %d.%02d pop=%d room=%d/%d reachable_room=%d sentiment=%d unemp=%d%%",
               game.simtime.year, game.simtime.month + 1,
               g_city.population.current, g_city.population.room_in_houses, g_city.population.total_capacity,
               room_reachable, g_city.sentiment.value, g_city.labor.unemployment_percentage);
    logs::info("[migration] pct=%d (sent=%d unemp=%d) queue=%d/%d batch=%d/%d duration=%d/%d",
               percentage, percentage_by_sentiment, percentage_by_unemployments,
               immigration_queue_size, emigration_queue_size,
               immigration_amount_per_batch, emigration_amount_per_batch,
               immigration_duration, emigration_duration);
    logs::info("[migration] newcomers=%d last_day immigrated=%d emigrated=%d refused=%d cause=%d cap=%d invading=%d pop_cap=%d",
               newcomers, immigrated_today, emigrated_today, refused_immigrants_today,
               no_immigration_cause, migration_cap ? 1 : 0, invading_cap ? 1 : 0, population_cap);
    logs::info("[migration] houses=%d with_room=%d no_entry=%d immigrant_slot=%d (dead=%d) vacant=%d/%d",
               houses_total, houses_with_room, houses_no_entry,
               houses_immigrant_slot, houses_immigrant_slot_dead,
               vacant_lots_with_room, vacant_lots);

    for (const auto &it : g_migration_cap_reasons) {
        logs::info("[migration] cap_reason '%s'=%d", it.first.c_str(), it.second);
    }
    for (const auto &it : g_migration_unemployment_cap_reasons) {
        logs::info("[migration] unemp_cap '%s'=[%d,%d]", it.first.c_str(), it.second.first, it.second.second);
    }

    reset_newcomers();
}

void city_migration_t::update() {
    update_conditions();
    update_status();
    create_migrants();

    events::emit(event_migration_update{ g_city.population.current });
}

void city_migration_t::determine_reason() {
    switch (g_city.sentiment.low_mood_cause) {
    case LOW_MOOD_NO_FOOD:
        no_immigration_cause = 2;
        break;
    case LOW_MOOD_NO_JOBS:
        no_immigration_cause = 1;
        break;
    case LOW_MOOD_HIGH_TAXES:
        no_immigration_cause = 3;
        break;
    case LOW_MOOD_LOW_WAGES:
        no_immigration_cause = 0;
        break;
    case LOW_MOOD_MANY_TENTS:
        no_immigration_cause = 4;
        break;
    default:
        no_immigration_cause = 5;
        break;
    }
}

int city_migration_t::no_room_for_immigrants() {
    return refused_immigrants_today || g_city.population.room_in_houses <= 0;
}

void city_migration_t::add_condition(condition cond) {
    g_migration_conditions.push_back(cond);
}
