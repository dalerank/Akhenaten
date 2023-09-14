#include "health.h"

#include "building/building.h"
#include "building/house.h"
#include "building/destruction.h"
#include "city/data_private.h"
#include "city/message.h"
#include "core/calc.h"
#include "core/random.h"
#include "game/tutorial.h"
#include "scenario/property.h"

int city_health(void) {
    return city_data.health.value;
}

void city_health_change(int amount) {
    city_data.health.value = calc_bound(city_data.health.value + amount, 0, 100);
}

static void cause_disease(int total_people) {
    return; // todo: temp
    if (city_data.health.value >= 40) {
        return;
    }

    int chance_value = random_byte() & 0x3f;
    if (city_data.religion.bast_curse_active) {
        // force plague
        chance_value = 0;
        city_data.religion.bast_curse_active = false;
    }

    if (chance_value > 40 - city_data.health.value) {
        return;
    }

    int sick_people = calc_adjust_with_percentage(total_people, 7 + (random_byte() & 3));
    if (sick_people <= 0) {
        return;
    }

    city_health_change(10);
    int people_to_kill = sick_people - city_data.health.num_hospital_workers;
    if (people_to_kill <= 0) {
        city_message_post(true, MESSAGE_HEALTH_ILLNESS, 0, 0);
        return;
    }

    if (city_data.health.num_hospital_workers > 0) {
        city_message_post(true, MESSAGE_HEALTH_DISEASE, 0, 0);
    } else {
        city_message_post(true, MESSAGE_HEALTH_PESTILENCE, 0, 0);
    }

    tutorial_on_disease();

    // kill people who don't have access to a doctor
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size && b->house_population) {
            if (!(b->data.house.apothecary || b->data.house.physician)) {
                people_to_kill -= b->house_population;
                building_destroy_by_plague(b);
                if (people_to_kill <= 0) {
                    return;
                }
            }
        }
    }

    // kill people in tents
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size && b->house_population) {
            if (b->subtype.house_level <= HOUSE_LARGE_HUT) {
                people_to_kill -= b->house_population;
                building_destroy_by_plague(b);
                if (people_to_kill <= 0) {
                    return;
                }
            }
        }
    }

    // kill anyone
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size && b->house_population) {
            people_to_kill -= b->house_population;
            building_destroy_by_plague(b);
            if (people_to_kill <= 0) {
                return;
            }
        }
    }
}

void city_health_update(void) {
    if (city_data.population.population < 200 || scenario_is_mission_rank(1) || scenario_is_mission_rank(2)) {
        city_data.health.value = 50;
        city_data.health.target_value = 50;
        return;
    }

    int total_population = 0;
    int healthy_population = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !b->house_size || !b->house_population) {
            continue;
        }

        total_population += b->house_population;
        if (b->subtype.house_level <= HOUSE_LARGE_HUT) {
            if (b->data.house.apothecary) {
                healthy_population += b->house_population;
            } else {
                healthy_population += b->house_population / 4;
            }
        } else if (b->data.house.physician) {
            if (b->house_days_without_food == 0) {
                healthy_population += b->house_population;
            } else {
                healthy_population += b->house_population / 4;
            }
        } else if (b->house_days_without_food == 0) {
            healthy_population += b->house_population / 4;
        }
    }

    city_data.health.target_value = calc_percentage(healthy_population, total_population);
    if (city_data.health.value < city_data.health.target_value) {
        city_data.health.value += 2;
        if (city_data.health.value > city_data.health.target_value) {
            city_data.health.value = city_data.health.target_value;
        }

    } else if (city_data.health.value > city_data.health.target_value) {
        city_data.health.value -= 2;
        if (city_data.health.value < city_data.health.target_value) {
            city_data.health.value = city_data.health.target_value;
        }
    }
    city_data.health.value = calc_bound(city_data.health.value, 0, 100);

    cause_disease(total_population);
}

void city_health_reset_hospital_workers(void) {
    city_data.health.num_hospital_workers = 0;
}

void city_health_add_hospital_workers(int amount) {
    city_data.health.num_hospital_workers += amount;
}
