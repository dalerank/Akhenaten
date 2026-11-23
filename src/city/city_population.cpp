#include "city_population.h"

#include "building/building_house.h"
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
#include "js/js_register.h"

#include <cstring>
#include <numeric>
#include <algorithm>
#include <array>

city_population_rules_t ANK_VARIABLE(city_population_rules);

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

int population_system::add_to_houses(int num_people) {
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

int population_system::remove_from_houses(int num_people) {
    int removed = 0;
    int building_id = _state.last_used_house_remove;
    for (int i = 1; i < 4 * MAX_BUILDINGS && removed < num_people; i++) {
        if (++building_id >= MAX_BUILDINGS)
            building_id = 1;

        auto house = building_get(building_id)->dcast_house();
        if (house && house->state() == BUILDING_STATE_VALID && house->hsize()) {
            _state.last_used_house_remove = building_id;
            if (house->house_population() > 0) {
                ++removed;
                --house->runtime_data().population;
            }
        }
    }
    return removed;
}

void population_system::update_room() {
    OZZY_PROFILER_FUNCTION();
    city_population_clear_capacity();

    buildings_house_do([&] (building_house *house) {
        if (house->distance_from_entry() <= 0) {
            return;
        }

        const int people = house->house_population();
        const int mul = house->is_merged() ? 4 : 1;
        int max_pop = house->model().max_people * mul;

        if (house->runtime_data().frog_infest_days > 0 || house->base.has_plague) {
            max_pop = people;
        }

        city_population_add_capacity(people, max_pop);
        auto &housed = house->runtime_data();
        housed.highest_population = std::max<short>(housed.highest_population, people);
    });
}

int population_system::create_emigrants(int num_people) {
    // OG 0x00458B60: house levels 0..9 only (crude hut … spacious apartment), lowest first, groups ≤ 4
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
        if (level > HOUSE_SPACIOUS_APARTMENT) {
            continue;
        }

        // Enhanced: optionally skip small huts (OFF by default = OG, huts do emigrate)
        if (!!game_features::gameplay_change_small_hut_not_create_emigrant
            && (level <= HOUSE_STURDY_HUT || (level < HOUSE_ORDINARY_COTTAGE && house->house_population() < 10))) {
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

int population_system::create_immigrants(int num_people) {
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

        events::emit(event_create_immigrant{ house->id(), to_immigrate, SOURCE_LOCATION });
        to_immigrate -= std::min(to_immigrate, 4);
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
        events::emit(event_create_immigrant{ house->id(), to_immigrate, SOURCE_LOCATION });
        to_immigrate -= std::min(to_immigrate, population_room);
    }

    return num_people - to_immigrate;
}

void population_system::reached_milestone(bool force) {
    xstring message;

    for (const auto& ms: city_population_rules.milestones) {
        if (_state.current >= ms.pop && (!city_message_mark_population_shown(ms.pop) || force)) {
            message = ms.message;
        }
    }

    if (!message.empty()) {
        events::emit(event_message_population{ true, message });
    }
}

void population_system::evict_overcrowded() {
    OZZY_PROFILER_FUNCTION();

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

void population_system::update_migration() {
    OZZY_PROFILER_FUNCTION();

    yearly_update();
    calculate_working_people();

    reached_milestone(false);
}

void population_system::calculate_working_people() {
    int num_peasants = 0;
    int num_nobles = 0;

    buildings_house_do([&] (building_house *house) {
        if (house->house_population() <= 0) {
            return;
        }
            
        int &counter = house->house_level() >= HOUSE_COMMON_MANOR ? num_nobles : num_peasants;
        counter += house->house_population();
    });

    labor_system(_ctx.labor, {_state, _ctx.resource}).calculate_workers(num_peasants, num_nobles);
}

void population_system::recalculate() {
    int save_value = _state.current;
    _state.current = std::accumulate(std::begin(_state.at_age), std::end(_state.at_age), 0);
    _state.highest_ever = std::max(_state.current, _state.highest_ever);
}

void city_population_clear_capacity(void) {
    city_data.population.total_capacity = 0;
    city_data.population.room_in_houses = 0;
}

void city_population_add_capacity(int people_in_house, int max_people) {
    city_data.population.total_capacity += max_people;
    city_data.population.room_in_houses += max_people - people_in_house;
}

static void add_to_census(population_state& population, int num_people) {
    int odd = 0;
    int index = 0;
    for (int i = 0; i < num_people; i++, odd = 1 - odd) {
        int age = random_from_pool(index++) & 0x3f; // 63
        if (age > 50)
            age -= 30;
        else if (age < 10 && odd)
            age += 20;

        population.at_age[age]++;
    }
}

static void remove_from_census(population_state& population, int num_people) {
    int index = 0;
    int empty_buckets = 0;
    // remove people randomly up to age 63
    while (num_people > 0 && empty_buckets < 100) {
        int age = random_from_pool(index++) & 0x3f;
        if (population.at_age[age] <= 0)
            empty_buckets++;
        else {
            population.at_age[age]--;
            num_people--;
            empty_buckets = 0;
        }
    }
    // if random didn't work: remove from age 10 and up
    empty_buckets = 0;
    int age = 10;
    while (num_people > 0 && empty_buckets < 100) {
        if (population.at_age[age] <= 0)
            empty_buckets++;
        else {
            population.at_age[age]--;
            num_people--;
            empty_buckets = 0;
        }
        age++;
        if (age >= 100)
            age = 0;
    }
}

static void remove_from_census_in_age_decennium(population_state& population, int decennium, int num_people) {
    int empty_buckets = 0;
    int age = 0;
    while (num_people > 0 && empty_buckets < 10) {
        if (population.at_age[10 * decennium + age] <= 0)
            empty_buckets++;
        else {
            population.at_age[10 * decennium + age]--;
            num_people--;
            empty_buckets = 0;
        }
        age++;
        if (age >= 10)
            age = 0;
    }
}

int population_state::get_people_in_age_decennium(int decennium) const {
    const int start = 10 * decennium;
    const int end = start + 10;
    return std::accumulate(at_age.begin() + start, at_age.begin() + end, 0);
}

int population_system::average_age() {
    recalculate();
    if (!_state.current) {
        return 0;
    }

    int age_sum = 0;
    for (int i = 0; i < 100; i++) {
        age_sum += (_state.at_age[i] * i);
    }
    return age_sum / _state.current;
}

void population_system::add(int num_people) {
    _state.last_change = num_people;
    add_to_census(_state, num_people);
    recalculate();
}

void population_system::remove(int num_people) {
    _state.last_change = -num_people;
    remove_from_census(_state, num_people);
    recalculate();
}

void population_system::add_homeless(int num_people) {
    _state.lost_homeless -= num_people;
    add_to_census(_state, num_people);
    recalculate();
}

void population_system::remove_homeless(int num_people) {
    _state.lost_homeless += num_people;
    remove_from_census(_state, num_people);
    recalculate();
}

void population_system::remove_home_removed(int num_people) {
    _state.lost_removal += num_people;
    remove_from_census(_state, num_people);
    recalculate();
}

void population_system::remove_for_troop_request(int num_people) {
    int removed = remove_from_houses(num_people);
    remove_from_census(_state, removed);
    _state.lost_troop_request += num_people;
    recalculate();
}

int population_state::get_people_of_working_age() const {
    const int start_age = 20;  // decennium 2
    const int end_age = !!game_features::gameplay_change_retire_at_60 ? 60 : 50;  // decennium 5 or 4
    return std::accumulate(at_age.begin() + start_age, at_age.begin() + end_age, 0);
}

int population_state::get_people_aged_between(int min, int max) const {
    return std::accumulate(at_age.begin() + min, at_age.begin() + max, 0);
}

void population_system::calculate_educational_age() {
    _state.school_age = _state.get_people_aged_between(0, 14);
    _state.academy_age = _state.get_people_aged_between(14, 21);
}

void population_system::record_monthly() {
    _state.monthly.values[_state.monthly.next_index++] = _state.current;
    if (_state.monthly.next_index >= 2400)
        _state.monthly.next_index = 0;

    ++_state.monthly.count;
}

void population_system::update_day() {
    if (_state.last_day_current != _state.current) {
        events::emit(event_population_changed{_state.current});
    }
    _state.last_day_current = _state.current;
}

int population_state::at_month(int max_months, int month) const {
    int start_offset = 0;
    if (monthly.count > max_months) {
        start_offset = monthly.count + 2400 - max_months;
    }

    int index = (start_offset + month) % 2400;
    return monthly.values[index];
}

void population_system::yearly_advance_ages_and_calculate_deaths() {
    int aged100 = _state.at_age[99];
    for (int age = 99; age > 0; age--) {
        _state.at_age[age] = _state.at_age[age - 1];
    }

    _state.at_age[0] = 0;
    _state.yearly_deaths = 0;
    for (int decennium = 9; decennium >= 0; decennium--) {
        int people = _state.get_people_in_age_decennium(decennium);
        int death_percentage = DEATHS_PER_HEALTH_PER_AGE_DECENNIUM[_ctx.health.value / 10][decennium];
        int deaths = calc_adjust_with_percentage(people, death_percentage);
        int removed = remove_from_houses(deaths + aged100);

        if (!!game_features::gameplay_fix_100y_ghosts) {
            remove_from_census_in_age_decennium(_state, decennium, deaths);
        } else {
            // Original engine removes both deaths and aged100, which creates "ghosts".
            // It should be deaths only; now aged100 are removed from census while
            // they weren't *in* the census anymore
            remove_from_census_in_age_decennium(_state, decennium, removed);
        }

        _state.yearly_deaths += removed;
        aged100 = 0;
    }
}

void population_system::yearly_calculate_births() {
    _state.yearly_births = 0;
    for (int decennium = 9; decennium >= 0; decennium--) {
        int people = _state.get_people_in_age_decennium(decennium);
        int births = calc_adjust_with_percentage<int>(people, city_population_rules.births_per_age_decennium[decennium]);
        int added = add_to_houses(births);
        _state.at_age[0] += added;
        _state.yearly_births += added;
    }
}

void population_system::yearly_recalculate() {
    _state.yearly_update_requested = 0;
    _state.last_year = _state.current;
    recalculate();

    _state.lost_removal = 0;
    _state.total_all_years += _state.current;
    _state.total_years++;
    _state.average_per_year = _state.total_all_years / _state.total_years;
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

void population_system::houses_demanding_goods_fill_from() {
    for (int i = 0; i <= 3; i++) {
        _state.houses_demanding_goods[i] = 0;
    }

    for (int i = 0; i <= 19; i++) {
        const auto &model = building_house::get_model(i);
        if (model.pottery) {
            _state.houses_demanding_goods[0] += _state.housing_type_counts[i];
        }

        if (model.jewelry) {
            _state.houses_demanding_goods[1] += _state.housing_type_counts[i];
        }

        if (model.linen) {
            _state.houses_demanding_goods[2] += _state.housing_type_counts[i];
        }

        if (model.beer) {
            _state.houses_demanding_goods[3] += _state.housing_type_counts[i];
        }
    }
}

void population_system::housing_type_counts_update() {
    _state.housing_type_counts.fill(0);

    buildings_house_do([this](building_house* house) {
        if (house->state() == BUILDING_STATE_UNUSED || house->state() == BUILDING_STATE_UNDO
            || house->state() == BUILDING_STATE_DELETED_BY_GAME || house->state() == BUILDING_STATE_DELETED_BY_PLAYER) {
            return;
        }
        if (house->house_population() > 0) {
            _state.housing_type_counts[house->house_level()] += 1;
        }
    });

    houses_demanding_goods_fill_from();
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

void population_system::yearly_update() {
    if (_state.yearly_update_requested) {
        yearly_advance_ages_and_calculate_deaths();
        yearly_calculate_births();
        yearly_recalculate();
    }
}

void city_population_check_consistency(void) {
    int people_in_houses = calculate_people_per_house_type();
    if (people_in_houses < city_data.population.current)
        remove_from_census(city_data.population, city_data.population.current - people_in_houses);
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

