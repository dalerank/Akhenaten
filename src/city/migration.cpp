#include "migration.h"

#include "city/city.h"
#include "city/message.h"
#include "core/calc.h"
#include "game/tutorial.h"

void city_t::migration_nobles_leave_city(int num_people) {
    migration.nobles_leave_city_this_year += num_people;
}

void city_t::migration_update_status() {
    int percentage_by_sentiment = 0;
    if (sentiment.value > 70) {
        percentage_by_sentiment = 100;
    } else if (sentiment.value > 60) {
        percentage_by_sentiment = 75;
    } else if (sentiment.value >= 50) {
        percentage_by_sentiment = 50;
    } else if (sentiment.value > 40) {
        percentage_by_sentiment = 0;
    } else if (sentiment.value > 30) {
        percentage_by_sentiment = -10;
    } else if (sentiment.value > 20) {
        percentage_by_sentiment = -25;
    } else {
        percentage_by_sentiment = -50;
    }

    migration.percentage_by_sentiment = percentage_by_sentiment;
    migration.percentage = migration.percentage_by_sentiment;

    migration.immigration_amount_per_batch = 0;
    migration.emigration_amount_per_batch = 0;

    int population_cap = tutorial_get_population_cap(200000);
    if (population.current >= population_cap) {
        migration.percentage = 0;
        migration.migration_cap = true;
        return;
    }
    // war scares immigrants away
    if (g_city.figures_total_invading_enemies() > 3 && migration.percentage > 0) {
        migration.percentage = 0;
        migration.invading_cap = true;
        return;
    }

    if (migration.percentage > 0) {
        // immigration
        if (migration.emigration_duration) {
            migration.emigration_duration--;
        } else {
            migration.immigration_amount_per_batch = calc_adjust_with_percentage(12, migration.percentage);
            migration.immigration_duration = 2;
        }
    } else if (migration.percentage < 0) {
        // emigration
        if (migration.immigration_duration) {
            migration.immigration_duration--;
        } else if (population.current > 100) {
            migration.emigration_amount_per_batch = calc_adjust_with_percentage(12, -migration.percentage);
            migration.emigration_duration = 2;
        }
    }
}

void city_t::create_immigrants(int num_people) {
    int immigrated = g_city.population.create_immigrants(num_people);
    migration.immigrated_today += immigrated;
    migration.newcomers += migration.immigrated_today;
    if (immigrated == 0) {
        migration.refused_immigrants_today += num_people;
    }
}

void city_t::create_emigrants(int num_people) {
    migration.emigrated_today += g_city.population.create_emigrants(num_people);
}

void city_t::create_migrants() {
    migration.immigrated_today = 0;
    migration.emigrated_today = 0;
    migration.refused_immigrants_today = 0;

    if (migration.immigration_amount_per_batch > 0) {
        if (migration.immigration_amount_per_batch >= 4) {
            create_immigrants(migration.immigration_amount_per_batch);

        } else if (migration.immigration_amount_per_batch + migration.immigration_queue_size >= 4) {
            create_immigrants(migration.immigration_amount_per_batch + migration.immigration_queue_size);
            migration.immigration_queue_size = 0;

        } else { // queue them for next round
            migration.immigration_queue_size += migration.immigration_amount_per_batch;
        }
    }
    
    if (migration.emigration_amount_per_batch > 0) {
        if (migration.emigration_amount_per_batch >= 4) {
            create_emigrants(migration.emigration_amount_per_batch);
        } else if (migration.emigration_amount_per_batch + migration.emigration_queue_size >= 4) {
            create_emigrants(migration.emigration_amount_per_batch + migration.emigration_queue_size);
            migration.emigration_queue_size = 0;
            if (!migration.emigration_message_shown) {
                migration.emigration_message_shown = 1;
                //                city_message_post(true, MESSAGE_EMIGRATION, 0, 0);
            }
        } else { // queue them for next round
            migration.emigration_queue_size += migration.emigration_amount_per_batch;
        }
    }

    migration.immigration_amount_per_batch = 0;
    migration.emigration_amount_per_batch = 0;
}

void city_t::migration_update() {
    migration_update_status();
    create_migrants();
}

void city_t::migration_determine_reason() {
    switch (sentiment.low_mood_cause) {
    case LOW_MOOD_NO_FOOD:
        migration.no_immigration_cause = 2;
        break;
    case LOW_MOOD_NO_JOBS:
        migration.no_immigration_cause = 1;
        break;
    case LOW_MOOD_HIGH_TAXES:
        migration.no_immigration_cause = 3;
        break;
    case LOW_MOOD_LOW_WAGES:
        migration.no_immigration_cause = 0;
        break;
    case LOW_MOOD_MANY_TENTS:
        migration.no_immigration_cause = 4;
        break;
    default:
        migration.no_immigration_cause = 5;
        break;
    }
}

int city_t::migration_no_room_for_immigrants() {
    return migration.refused_immigrants_today || population.room_in_houses <= 0;
}
