#include "city_population.h"

#include "building/building_house.h"
#include "building/model.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "game/game_config.h"
#include "figuretype/figure_emigrant.h"
#include "figuretype/figure_immigrant.h"
#include "figuretype/figure_homeless.h"
#include "core/profiler.h"

static const int BIRTHS_PER_AGE_DECENNIUM[10] = {0, 3, 16, 9, 2, 0, 0, 0, 0, 0};

static const int DEATHS_PER_HEALTH_PER_AGE_DECENNIUM[11][10] = {{20, 10, 5, 10, 20, 30, 50, 85, 100, 100},
                                                                {15, 8, 4, 8, 16, 25, 45, 70, 90, 100},
                                                                {10, 6, 2, 6, 12, 20, 30, 55, 80, 90},
                                                                {5, 4, 0, 4, 8, 15, 25, 40, 65, 80},
                                                                {3, 2, 0, 2, 6, 12, 20, 30, 50, 70},
                                                                {2, 0, 0, 0, 4, 8, 15, 25, 40, 60},
                                                                {1, 0, 0, 0, 2, 6, 12, 20, 30, 50},
                                                                {0, 0, 0, 0, 0, 4, 8, 15, 20, 40},
                                                                {0, 0, 0, 0, 0, 2, 6, 10, 15, 30},
                                                                {0, 0, 0, 0, 0, 0, 4, 5, 10, 20},
                                                                {0, 0, 0, 0, 0, 0, 0, 2, 5, 10}};

static auto &city_data = g_city;

int city_population_last_used_house_add(void) {
    return city_data.population.last_used_house_add;
}

void city_population_set_last_used_house_add(int building_id) {
    city_data.population.last_used_house_add = building_id;
}

int city_population_last_used_house_remove(void) {
    return city_data.population.last_used_house_remove;
}

void city_population_set_last_used_house_remove(int building_id) {
    city_data.population.last_used_house_remove = building_id;
}

int city_population_t::add_to_houses(int num_people) {
    int added = 0;
    buildings_house_do([&] (building_house *house) {
        if (house->state() == BUILDING_STATE_VALID && house->distance_from_entry() > 0 && house->house_population() > 0) {
            int max_people = house->model().max_people;
            if (house->is_merged()) {
                max_people *= 4;
            }

            if (house->house_population() < max_people) {
                ++added;
                ++house->runtime_data().population;
            }
        }
    });
    return added;
}


int city_population_t::remove_from_houses(int num_people) {
    int removed = 0;
    int building_id = city_population_last_used_house_remove();
    for (int i = 1; i < 4 * MAX_BUILDINGS && removed < num_people; i++) {
        if (++building_id >= MAX_BUILDINGS)
            building_id = 1;

        auto house = building_get(building_id)->dcast_house();
        if (house && house->state() == BUILDING_STATE_VALID && house->hsize()) {
            city_population_set_last_used_house_remove(building_id);
            if (house->house_population() > 0) {
                ++removed;
                --house->runtime_data().population;
            }
        }
    }
    return removed;
}

void city_population_t::update_room() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Population Update");
    city_population_clear_capacity();

    buildings_house_do([&] (building_house *house) {
        if (house->distance_from_entry() <= 0) {
            return;
        }

        const int mul = house->is_merged() ? 4 : 1;
        const int max_pop = house->model().max_people * mul;

        city_population_add_capacity(house->house_population(), max_pop);
        auto &housed = house->runtime_data();
        housed.highest_population = std::max<short>(housed.highest_population, house->house_population());
    });
}

int city_population_t::create_emigrants(int num_people) {
    svector<building_house *, 2000> houses;
    buildings_houses_get(houses);

    std::sort(houses.begin(), houses.end(), [] (auto &lhs, auto &rhs) { return lhs->house_level() < rhs->house_level(); });

    int to_emigrate = num_people;
    for (auto house: houses) {
        if (to_emigrate <= 0) {
            break;
        }

        if (house->house_population() <= 0) {
            continue;
        }

        const int level = house->house_level();
        if (!game_features::gameplay_change_small_hut_not_create_emigrant && (level <= HOUSE_STURDY_HUT || (level < HOUSE_ORDINARY_COTTAGE && house->house_population() < 10))) {
            continue;
        }

        int current_people;
        if (house->house_population() >= 4) {
            current_people = 4;
        } else {
            current_people = house->house_population();
        }

        if (to_emigrate <= current_people) {
            events::emit(event_create_emigrant{ house->id(), to_emigrate, SOURCE_LOCATION });
            to_emigrate = 0;
        } else {
            events::emit(event_create_emigrant{ house->id(), current_people, SOURCE_LOCATION });
            to_emigrate -= current_people;
        }
    }

    return num_people - to_emigrate;
}

int city_population_t::create_immigrants(int num_people) {

    svector<building_house *, 2000> houses;
    buildings_houses_get(houses);

    // clean up any dead immigrants
    for (auto house: houses) {
        if (house->base.has_figure(BUILDING_SLOT_IMMIGRANT) && house->get_figure(BUILDING_SLOT_IMMIGRANT)->state != FIGURE_STATE_ALIVE) {
            house->base.remove_figure(BUILDING_SLOT_IMMIGRANT);
        }
    };

    // houses with plenty of room
    int to_immigrate = num_people;
    for (auto &house: houses) {
        if (to_immigrate <= 0) {
            break;
        }

        if (house->distance_from_entry() <= 0 || house->population_room() <= 8 || house->base.has_figure(BUILDING_SLOT_IMMIGRANT, -1)) {
            continue; // house already has immigrant
        }

        to_immigrate -= std::min(to_immigrate, 4);
        events::emit(event_create_immigrant{ house->id(), to_immigrate, SOURCE_LOCATION });
    }

    // houses with less room
    for (auto &house : houses) {
        if (to_immigrate <= 0) {
            break;
        }

        if (house->distance_from_entry() <= 0 || house->population_room() <= 0 || house->base.has_figure(BUILDING_SLOT_IMMIGRANT, -1)) {
            continue; // immigrant algready going to this house
        }
        const int population_room = house->population_room();
        to_immigrate -= std::min(to_immigrate, population_room);
        events::emit(event_create_immigrant{ house->id(), to_immigrate, SOURCE_LOCATION });
    }

    return num_people - to_immigrate;
}

void city_population_t::reached_milestone(bool force) {
    int message = 0;

    struct popm {
        int pop;
        int message;
    };
    constexpr popm milestones[] = {
        {500, MESSAGE_POPULATION_500},
        {1000, MESSAGE_POPULATION_1000},
        {2000, MESSAGE_POPULATION_2000},
        {3000, MESSAGE_POPULATION_3000},
        {5000, MESSAGE_POPULATION_5000},
        {10000, MESSAGE_POPULATION_10000},
        {15000, MESSAGE_POPULATION_15000},
        {20000, MESSAGE_POPULATION_20000},
        {25000, MESSAGE_POPULATION_25000},
    };

    for (const auto& ms: milestones) {
        if (current >= ms.pop && (!city_message_mark_population_shown(ms.pop) || force)) {
            message = ms.message;
        }
    }

    if (message > 0) {
        events::emit(event_message_population{ true, message, 0, 0 });
    }
}

void city_population_t::evict_overcrowded() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/House Overcrown Update");

    buildings_house_do([] (building_house *house) {
        int16_t population_room = house->population_room();
        if (population_room >= 0) {
            return;
        }

        int num_people_to_evict = -population_room;
        events::emit(event_create_homeless{ house->tile(), num_people_to_evict, SOURCE_LOCATION });
        if (num_people_to_evict < house->house_population()) {
            house->runtime_data().population -= num_people_to_evict;
        } else {
            // house has been removed
            house->base.state = BUILDING_STATE_UNDO;
        }
    });
}

void city_population_t::update_migration() {
    OZZY_PROFILER_SECTION("Game/Update/House Migration Update");

    yearly_update();
    calculate_working_people();

    reached_milestone(false);
}

void city_population_t::calculate_working_people() {
    int num_peasants = 0;
    int num_nobles = 0;

    buildings_house_do([&] (building_house *house) {
        if (house->house_population() <= 0) {
            return;
        }
            
        int &counter = house->house_level() >= HOUSE_COMMON_MANOR ? num_nobles : num_peasants;
        counter += house->house_population();
    });

    g_city.labor.calculate_workers(num_peasants, num_nobles);
}

void city_population_t::recalculate() {
    int save_value = current;
    current = 0;
    for (int i = 0; i < 100; i++) {
        current += at_age[i];
    }

    highest_ever = std::max(current, highest_ever);
}

void city_population_clear_capacity(void) {
    city_data.population.total_capacity = 0;
    city_data.population.room_in_houses = 0;
}

void city_population_add_capacity(int people_in_house, int max_people) {
    city_data.population.total_capacity += max_people;
    city_data.population.room_in_houses += max_people - people_in_house;
}

static void add_to_census(int num_people) {
    int odd = 0;
    int index = 0;
    for (int i = 0; i < num_people; i++, odd = 1 - odd) {
        int age = random_from_pool(index++) & 0x3f; // 63
        if (age > 50)
            age -= 30;
        else if (age < 10 && odd)
            age += 20;

        city_data.population.at_age[age]++;
    }
}

static void remove_from_census(int num_people) {
    int index = 0;
    int empty_buckets = 0;
    // remove people randomly up to age 63
    while (num_people > 0 && empty_buckets < 100) {
        int age = random_from_pool(index++) & 0x3f;
        if (city_data.population.at_age[age] <= 0)
            empty_buckets++;
        else {
            city_data.population.at_age[age]--;
            num_people--;
            empty_buckets = 0;
        }
    }
    // if random didn't work: remove from age 10 and up
    empty_buckets = 0;
    int age = 10;
    while (num_people > 0 && empty_buckets < 100) {
        if (city_data.population.at_age[age] <= 0)
            empty_buckets++;
        else {
            city_data.population.at_age[age]--;
            num_people--;
            empty_buckets = 0;
        }
        age++;
        if (age >= 100)
            age = 0;
    }
}

static void remove_from_census_in_age_decennium(int decennium, int num_people) {
    int empty_buckets = 0;
    int age = 0;
    while (num_people > 0 && empty_buckets < 10) {
        if (city_data.population.at_age[10 * decennium + age] <= 0)
            empty_buckets++;
        else {
            city_data.population.at_age[10 * decennium + age]--;
            num_people--;
            empty_buckets = 0;
        }
        age++;
        if (age >= 10)
            age = 0;
    }
}

static int get_people_in_age_decennium(int decennium) {
    int pop = 0;
    for (int i = 0; i < 10; i++) {
        pop += city_data.population.at_age[10 * decennium + i];
    }
    return pop;
}

int city_population_t::average_age() {
    recalculate();
    if (!current) {
        return 0;
    }

    int age_sum = 0;
    for (int i = 0; i < 100; i++) {
        age_sum += (at_age[i] * i);
    }
    return age_sum / current;
}

void city_population_t::add(int num_people) {
    last_change = num_people;
    add_to_census(num_people);
    recalculate();
}

void city_population_t::remove(int num_people) {
    last_change = -num_people;
    remove_from_census(num_people);
    recalculate();
}

void city_population_t::add_homeless(int num_people) {
    lost_homeless -= num_people;
    add_to_census(num_people);
    recalculate();
}

void city_population_t::remove_homeless(int num_people) {
    lost_homeless += num_people;
    remove_from_census(num_people);
    recalculate();
}

void city_population_t::remove_home_removed(int num_people) {
    lost_removal += num_people;
    remove_from_census(num_people);
    recalculate();
}

void city_population_t::remove_for_troop_request(int num_people) {
    int removed = remove_from_houses(num_people);
    remove_from_census(removed);
    lost_troop_request += num_people;
    recalculate();
}

int city_population_people_of_working_age() {
    if (!!game_features::gameplay_change_retire_at_60) {
        return get_people_in_age_decennium(2) + get_people_in_age_decennium(3) + get_people_in_age_decennium(4) + get_people_in_age_decennium(5);
    } else {
        return get_people_in_age_decennium(2) + get_people_in_age_decennium(3) + get_people_in_age_decennium(4);
    }
}

int city_population_percent_in_workforce(void) {
    if (!city_data.population.current)
        return 0;

    if (!!game_features::gameplay_change_fixed_workers) {
        return 38;
    }

    return calc_percentage(city_data.labor.workers_available, city_data.population.current);
}

static int get_people_aged_between(int min, int max) {
    int pop = 0;
    for (int i = min; i < max; i++) {
        pop += city_data.population.at_age[i];
    }
    return pop;
}

void city_population_calculate_educational_age(void) {
    city_data.population.school_age = get_people_aged_between(0, 14);
    city_data.population.academy_age = get_people_aged_between(14, 21);
}

void city_population_t::record_monthly() {
    monthly.values[monthly.next_index++] = current;
    if (monthly.next_index >= 2400)
        monthly.next_index = 0;

    ++monthly.count;
}

void city_population_t::update_day() {
    if (last_day_current != current) {
        events::emit(event_population_changed{ current });
    }
    last_day_current = current;
}

int city_population_t::at_month(int max_months, int month) {
    int start_offset = 0;
    if (monthly.count > max_months) {
        start_offset = monthly.count + 2400 - max_months;
    }

    int index = (start_offset + month) % 2400;
    return monthly.values[index];
}

void city_population_t::yearly_advance_ages_and_calculate_deaths() {
    int aged100 = at_age[99];
    for (int age = 99; age > 0; age--) {
        at_age[age] = at_age[age - 1];
    }

    at_age[0] = 0;
    yearly_deaths = 0;
    for (int decennium = 9; decennium >= 0; decennium--) {
        int people = get_people_in_age_decennium(decennium);
        int death_percentage = DEATHS_PER_HEALTH_PER_AGE_DECENNIUM[city_data.health.value / 10][decennium];
        int deaths = calc_adjust_with_percentage(people, death_percentage);
        int removed = remove_from_houses(deaths + aged100);

        if (!!game_features::gameplay_fix_100y_ghosts) {
            remove_from_census_in_age_decennium(decennium, deaths);
        } else {
            // Original engine removes both deaths and aged100, which creates "ghosts".
            // It should be deaths only; now aged100 are removed from census while
            // they weren't *in* the census anymore
            remove_from_census_in_age_decennium(decennium, removed);
        }

        yearly_deaths += removed;
        aged100 = 0;
    }
}

static void yearly_calculate_births(void) {
    city_data.population.yearly_births = 0;
    for (int decennium = 9; decennium >= 0; decennium--) {
        int people = get_people_in_age_decennium(decennium);
        int births = calc_adjust_with_percentage(people, BIRTHS_PER_AGE_DECENNIUM[decennium]);
        int added = g_city.population.add_to_houses(births);
        city_data.population.at_age[0] += added;
        city_data.population.yearly_births += added;
    }
}

void city_population_t::yearly_recalculate() {
    yearly_update_requested = 0;
    last_year = current;
    recalculate();

    lost_removal = 0;
    total_all_years += current;
    total_years++;
    average_per_year = total_all_years / total_years;
}

int calculate_total_housing_buildings(void) {
    int total = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (!house) {
            continue;
        }

        const e_building_state state = house->state();
        if (state == BUILDING_STATE_UNUSED || state == BUILDING_STATE_UNDO
            || state == BUILDING_STATE_DELETED_BY_GAME || state == BUILDING_STATE_DELETED_BY_PLAYER) {
            continue;
        }

        total += (house->house_population() > 0) ? 1 : 0;
    }

    return total;
}

int* calculate_number_of_each_housing_type(void) {
    static int housing_type_counts[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i <= 19; i++) {
        housing_type_counts[i] = 0;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();

        if (!house) {
            continue;
        }

        if (house->state() == BUILDING_STATE_UNUSED || house->state() == BUILDING_STATE_UNDO
            || house->state() == BUILDING_STATE_DELETED_BY_GAME || house->state() == BUILDING_STATE_DELETED_BY_PLAYER) {
            continue;
        }

        if (house->house_population() > 0) {
            housing_type_counts[house->house_level()] += 1;
        }
    }

    return housing_type_counts;
}

int* calculate_houses_demanding_goods(int* housing_type_counts) {
    static int houses_demanding_goods[4] = {0, 0, 0, 0};

    for (int i = 0; i <= 3; i++) {
        houses_demanding_goods[i] = 0;
    }

    for (int i = 0; i <= 19; i++) {
        const auto &model = model_get_house(i);
        if (model.pottery)
            houses_demanding_goods[0] += housing_type_counts[i];

        if (model.jewelry)
            houses_demanding_goods[1] += housing_type_counts[i];

        if (model.linen)
            houses_demanding_goods[2] += housing_type_counts[i];

        if (model.beer)
            houses_demanding_goods[3] += housing_type_counts[i];
    }

    return houses_demanding_goods;
}

static int calculate_people_per_house_type(void) {
    city_data.population.people_in_shanties = 0;
    city_data.population.people_in_manors = 0;
    city_data.population.people_in_huts = 0;
    city_data.population.people_in_residences = 0;
    int total = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (!house) {
            continue;
        }

        if (house->state() == BUILDING_STATE_UNUSED || house->state() == BUILDING_STATE_UNDO
            || house->state() == BUILDING_STATE_DELETED_BY_GAME || house->state() == BUILDING_STATE_DELETED_BY_PLAYER) {
            continue;
        }

        if (house->house_population()) {
            auto &housed = house->runtime_data();
            int pop = housed.population;
            total += pop;

            e_house_level hlevel = house->house_level();
            if (hlevel <= HOUSE_STURDY_HUT) {
                city_data.population.people_in_huts += pop;
            }

            if (hlevel <= HOUSE_COMMON_SHANTY) {
                city_data.population.people_in_shanties += pop;
            }

            if (hlevel >= HOUSE_COMMON_RESIDENCE) {
                city_data.population.people_in_residences += pop;
            }

            if (hlevel >= HOUSE_COMMON_MANOR) {
                city_data.population.people_in_manors += pop;
            }
        }
    }
    return total;
}

void city_population_request_yearly_update(void) {
    city_data.population.yearly_update_requested = 1;
    calculate_people_per_house_type();
}

void city_population_t::yearly_update() {
    if (yearly_update_requested) {
        yearly_advance_ages_and_calculate_deaths();
        yearly_calculate_births();
        yearly_recalculate();
    }
}

void city_population_check_consistency(void) {
    int people_in_houses = calculate_people_per_house_type();
    if (people_in_houses < city_data.population.current)
        remove_from_census(city_data.population.current - people_in_houses);
}

int city_population_open_housing_capacity(void) {
    return city_data.population.room_in_houses;
}

int city_population_total_housing_capacity(void) {
    return city_data.population.total_capacity;
}

int city_population_yearly_deaths(void) {
    return city_data.population.yearly_deaths;
}

int city_population_yearly_births() {
    return city_data.population.yearly_births;
}

int city_population_t::percentage_in_shanties() {
    if (!current) {
        return 0;
    }

    return calc_percentage(people_in_shanties, city_data.population.current);
}

int city_population_t::percentage_in_manors() {
    if (!current) {
        return 0;
    }

    return calc_percentage(people_in_manors, current);
}
