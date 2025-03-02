#include "city_house_population.h"

#include "building/building.h"
#include "building/building_house.h"
#include "building/list.h"
#include "building/model.h"
#include "config/config.h"
#include "city/labor.h"
#include "city/message.h"
#include "city/city.h"
#include "city/population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/game_environment.h"
#include "figuretype/figure_emigrant.h"
#include "figuretype/figure_immigrant.h"
#include "figuretype/figure_homeless.h"
#include "figure/figure.h"

int house_population_add_to_city(int num_people) {
    int added = 0;
    int building_id = city_population_last_used_house_add();
    for (int i = 1; i < MAX_BUILDINGS && added < num_people; i++) {
        if (++building_id >= MAX_BUILDINGS)
            building_id = 1;

        auto house = building_get(building_id)->dcast_house();
        if (house->state() == BUILDING_STATE_VALID && house->base.house_size && house->distance_from_entry() > 0 && house->house_population() > 0) {
            city_population_set_last_used_house_add(building_id);
            int max_people = model_get_house(house->house_level())->max_people;
            if (house->is_merged()) {
                max_people *= 4;
            }

            if (house->house_population() < max_people) {
                ++added;
                ++house->base.house_population;
            }
        }
    }
    return added;
}

int house_population_remove_from_city(int num_people) {
    int removed = 0;
    int building_id = city_population_last_used_house_remove();
    for (int i = 1; i < 4 * MAX_BUILDINGS && removed < num_people; i++) {
        if (++building_id >= MAX_BUILDINGS)
            building_id = 1;

        building* b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && b->house_size) {
            city_population_set_last_used_house_remove(building_id);
            if (b->house_population > 0) {
                ++removed;
                --b->house_population;
            }
        }
    }
    return removed;
}

static void fill_building_list_with_houses(void) {
    building_list_large_clear(0);
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size)
            building_list_large_add(i);
    }
}

void city_t::house_population_update_room() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Population Update");
    city_population_clear_capacity();

    fill_building_list_with_houses();
    int total_houses = building_list_large_size();
    const int* houses = building_list_large_items();
    for (int i = 0; i < total_houses; i++) {
        auto house = building_get(houses[i])->dcast_house();

        if (house->distance_from_entry() > 0) {
            int max_pop = model_get_house(house->house_level())->max_people;
            if (house->is_merged()) {
                max_pop *= 4;
            }

            city_population_add_capacity(house->house_population(), max_pop);
            auto &housed = house->runtime_data();
            housed.highest_population = std::max<short>(housed.highest_population, house->house_population());
        }
    }
}

int house_population_create_immigrants(int num_people) {
    int total_houses = building_list_large_size();
    const int* houses = building_list_large_items();
    int to_immigrate = num_people;
    // clean up any dead immigrants
    for (int i = 0; i < total_houses; i++) {
        building* b = building_get(houses[i]);
        if (b->has_figure(2) && b->get_figure(2)->state != FIGURE_STATE_ALIVE)
            b->remove_figure(2);
    }
    // houses with plenty of room
    for (int i = 0; i < total_houses && to_immigrate > 0; i++) {
        auto house = building_get(houses[i])->dcast_house();
        if (house && house->distance_from_entry() > 0 && house->population_room() >= 8 && !house->base.has_figure(2, -1)) {
            if (to_immigrate <= 4) {
                figure_immigrant::create(&house->base, to_immigrate);
                to_immigrate = 0;
            } else {
                figure_immigrant::create(&house->base, 4);
                to_immigrate -= 4;
            }
        }
    }
    // houses with less room
    for (int i = 0; i < total_houses && to_immigrate > 0; i++) {
        auto house = building_get(houses[i])->dcast_house();
        if (house->distance_from_entry() > 0 && house->population_room() > 0 && !house->base.has_figure(2, -1)) {
            int16_t population_room = house->population_room();
            if (to_immigrate <= population_room) {
                figure_immigrant::create(&house->base, to_immigrate);
                to_immigrate = 0;
            } else {
                figure_immigrant::create(&house->base, population_room);
                to_immigrate -= population_room;
            }
        }
    }
    return num_people - to_immigrate;
}

int house_population_create_emigrants(int num_people) {
    int total_houses = building_list_large_size();
    const int* ids = building_list_large_items();

    int to_emigrate = num_people;
    for (int level = HOUSE_CRUDE_HUT; level < HOUSE_COMMON_RESIDENCE && to_emigrate > 0; level++) {
        for (int i = 0; i < total_houses && to_emigrate > 0; i++) {
            auto house = building_get(ids[i])->dcast_house();

            if (house->house_population() <= 0 || house->house_level() != level) {
                continue;
            }

            if (config_get(CONFIG_GP_CH_SMALL_HUT_NIT_CREATE_EMIGRANT) && (level <= HOUSE_STURDY_HUT || (level < HOUSE_ORDINARY_COTTAGE && house->house_population() < 10))) {
                continue;
            }

            int current_people;
            if (house->house_population() >= 4) {
                current_people = 4;
            } else {
                current_people = house->house_population();
            }

            if (to_emigrate <= current_people) {
                figure_emigrant::create(&house->base, to_emigrate);
                to_emigrate = 0;
            } else {
                figure_emigrant::create(&house->base, current_people);
                to_emigrate -= current_people;
            }
        }
    }

    return num_people - to_emigrate;
}

static void calculate_working_population(void) {
    int num_peasants = 0;
    int num_nobles = 0;
    int total_houses = building_list_large_size();
    const int* houses = building_list_large_items();
    for (int i = 0; i < total_houses; i++) {
        auto house = building_get(houses[i])->dcast_house();
        if (house->house_population() > 0) {
            if (house->house_level() >= HOUSE_COMMON_MANOR)
                num_nobles += house->house_population();
            else {
                num_peasants += house->house_population();
            }
        }
    }
    g_city.labor.calculate_workers(num_peasants, num_nobles);
}

void city_population_reached_milestone(bool force) {
    int population = city_population();
    if (population >= 500 && (!city_message_mark_population_shown(500) || force))
        city_message_population_post(true, MESSAGE_POPULATION_500, 0, 0);

    if (population >= 1000 && (!city_message_mark_population_shown(1000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_1000, 0, 0);

    if (population >= 2000 && (!city_message_mark_population_shown(2000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_2000, 0, 0);

    if (population >= 3000 && (!city_message_mark_population_shown(3000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_3000, 0, 0);

    if (population >= 5000 && (!city_message_mark_population_shown(5000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_5000, 0, 0);

    if (population >= 10000 && (!city_message_mark_population_shown(10000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_10000, 0, 0);

    if (population >= 15000 && (!city_message_mark_population_shown(15000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_15000, 0, 0);

    if (population >= 20000 && (!city_message_mark_population_shown(20000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_20000, 0, 0);

    if (population >= 25000 && (!city_message_mark_population_shown(25000) || force))
        city_message_population_post(true, MESSAGE_POPULATION_25000, 0, 0);
}

void city_t::house_population_update_migration() {
    OZZY_PROFILER_SECTION("Game/Update/House Migration Update");

    city_population_yearly_update();
    calculate_working_population();
    
    city_population_reached_milestone(false);
}

void city_t::house_population_evict_overcrowded() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Overcrown Update");
    int size = building_list_large_size();
    const int* items = building_list_large_items();
    for (int i = 0; i < size; i++) {
        auto house = building_get(items[i])->dcast_house();
        if (!house) {
            continue;
        }

        int16_t population_room = house->population_room();
        if (population_room < 0) {
            int num_people_to_evict = -population_room;
            figure_create_homeless(house->tile(), num_people_to_evict);
            if (num_people_to_evict < house->house_population()) {
                house->base.house_population -= num_people_to_evict;
            } else {
                // house has been removed
                house->base.state = BUILDING_STATE_UNDO;
            }
        }
    }
}
