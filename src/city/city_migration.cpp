#include "city_migration.h"

#include "city/city.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "js/js_game.h"

svector<city_migration_t::condition, 16> g_migration_conditions;
city_migration_defaults_t ANK_VARIABLE(migration_defaults);
svector<sentiment_step_t, 16> g_migration_sentiment_influence;

void ANK_REGISTER_CONFIG_ITERATOR(config_load_migration_influence) {
    g_migration_sentiment_influence.clear();
    g_config_arch.r("migration_sentiment_influence", g_migration_sentiment_influence);
    assert(!g_migration_sentiment_influence.empty());
}

void city_migration_t::nobles_leave_city(int num_people) {
    nobles_leave_city_this_year += num_people;
}

void city_migration_t::update_status() {
    auto& params = migration_defaults;

    const auto &sentiment = g_city.sentiment;
    auto it = std::find_if(g_migration_sentiment_influence.begin(), g_migration_sentiment_influence.end(), [&] (const auto& t) {
        return sentiment.value > t.s; 
    });

    percentage_by_sentiment = (it != g_migration_sentiment_influence.end()) ? it->i : 0;
    percentage = percentage_by_sentiment;

    immigration_amount_per_batch = 0;
    emigration_amount_per_batch = 0;

    if (population_cap > 0 && g_city.population.current >= population_cap) {
        percentage = 0;
        migration_cap = true;
        return;
    }

    // war scares immigrants away
    if (g_city.figures_total_invading_enemies() > 3 && percentage > 0) {
        percentage = 0;
        invading_cap = true;
        return;
    }

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
}

void city_migration_t::update_conditions() {
    for (const auto &condition : g_migration_conditions) {
        condition(*this);
    }
}

void city_migration_t::update() {
    update_conditions();
    update_status();
    create_migrants();
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
