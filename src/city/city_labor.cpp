#include "city_labor.h"

#include "building/building.h"
#include "building/building_farm.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "core/random.h"
#include "game/game_config.h"
#include "scenario/scenario.h"
#include "city/city_industry.h"
#include "grid/terrain.h"
#include "js/js_game.h"

#include <algorithm>

const token_holder<e_labor_category, LABOR_CATEGORY_NONE, LABOR_CATEGORY_SIZE> ANK_CONFIG_ENUM(e_labor_category_tokens);

static int category_for_int_arr[300] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 10
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 20
  6,  6,  6,  6,  6,  6,  6,  6,  -1, -1, // 30
  -1, -1, -1, -1, -1, -1, 7,  7,  7,  7,  // 40
  0,  7,  7,  7,  -1, 4,  -1, 5,  5,  5,  // 50
  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  // 60
  0,  1,  0,  -1, 1,  0,  1,  -1, -1, -1, // 70
  7,  2,  -1, -1, 8,  8,  8,  8,  -1, -1, // 80
  -1, 3,  -1, -1, 5,  5,  -1, -1, 8,  -1, // 90
  1,  1,  1,  0,  0,  1,  0,  0,  0,  0,  // 100
  0,  0,  0,  0,  0,  -1, -1, -1, -1, -1, // 110
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 120
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 130
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 140
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 150
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 160
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 170
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 180
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 190
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 200
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 210
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 220
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 230
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 240
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 250
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 260
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 270
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 280
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 290
};

static int category_for_int_arr_ph[303] = {
  // houses
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 10
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 20

  2, // bandstand
  2, // booth
  2, // senet house
  2, // pavillion
  2, // conservatory
  2, // dance school
  2, // juggler school

  -1, -1, -1,

  -1, // charioteers (fort)

  -1, -1, -1,

  -1, // archers (fort)
  -1, // infantry (fort)
  5,  // apothecary
  5,  // mortuary

  -1,

  5, // dentist

  -1,

  4, // school

  -1,

  4, // library

  -1,

  6, // police station

  -1, -1, -1, -1,

  3,  3,  3,  3,  3, // temples
  3,  3,  3,  3,  3, // temple complexes
  0,                 // market
  0,                 // granary
  1,                 // warehouse
  -1,                // warehouse space
  1,                 // shipyard
  1,                 // dock
  0,                 // fishing wharf
  -1, -1, -1,        // mansions

  -1,

  6,      // engineer
  -1, -1, // bridges

  -1, -1,

  7,  7, // tax collector

  -1, -1, // 80

  1, // water lift (2)

  -1,

  -1, // well

  -1,

  8, // military academy
  8, // recruiter

  -1, -1, -1, -1, // 90

  0,  0,  0,  0,  0,  0, // farms
  1,  1,                 // quarries
  1,                     // timber
  1,                     // clay pit
  1,                     // beer
  1,                     // linen
  1,                     // weapons
  1,                     // luxury goods
  1,                     //  potter
  0,                     // hunting's lodge

  -1, -1, -1, -1,                         // 110
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 120
  -1, -1, -1, -1, -1, -1,

  6, // ferry

  -1,

  -1, // roadblock

  -1, // 130

  3,  3,  3,  3,  3,                      // shrines
  -1, -1, -1, -1, -1,                     // 140
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 150
  -1,

  1, // gold mine
  1, // gems quarry

  -1, -1, -1, -1,

  6, // firehouse

  -1,

  -1, // wall

  -1,

  -1, // gatehouse

  -1,

  8, // tower

  -1, -1, -1,

  1,  1,  1, // guilds

  5,  // water supply
  8,  // transport wharf
  8,  // warship wharf
  -1, // pyramid
  7,  // courthouse

  -1, -1,

  7,  7,  7, // town palace

  -1, -1, -1, -1,

  0, // cattle ranch
  1, // reed gatherers
  0, // figs farm

  -1, -1,

  0, // workcamp

  -1, -1,

  -1, // gatehouse (2)

  1, // papyrus
  1, // bricks
  1, // chariots
  5, // physician

  -1, -1,

  -1, // festival square
  -1, // sphynx

  -1, -1, -1, -1, -1,

  1, // granite
  1, // copper

  -1, -1, // 210
  -1,

  1,  // sandstone
  -1, // mausoleum

  -1,

  1,  // henna farm
  -1, // alex. library
  2,  // zoo
  -1, // caesareum
  -1, // pharos lighth.
  -1, // small r. tomb
  -1, // abu simbel
  1,  // artisans guild
  0,  // lamps
  0,  // paint
  -1, // medium r. tomb
  -1, // large r. tomb
  -1, // grand r. tomb
};

const labor_category* city_labor_t::category(int category) {
    return &categories[category];
}

void city_labor_t::set_category(e_building_type type, int category) {
    category_for_int_arr_ph[type] = category;
}

struct building_type_category {
    e_building_type btype;
    e_labor_category category;
};

constexpr building_type_category category_alias_default[] = {
    {BUILDING_BARLEY_FARM, LABOR_CATEGORY_FOOD_PRODUCTION},
    {BUILDING_CHICKPEAS_FARM, LABOR_CATEGORY_FOOD_PRODUCTION},
    {BUILDING_FLAX_FARM, LABOR_CATEGORY_FOOD_PRODUCTION},
    {BUILDING_POTTERY_WORKSHOP, LABOR_CATEGORY_INDUSTRY_COMMERCE}
};

static bool category_alias_inited = false;
static e_labor_category category_alias[255];

e_labor_category category_for_building(building* b) {
    if (map_terrain_is(b->tile, TERRAIN_FLOODPLAIN) && b->is_farm()) {
        return LABOR_CATEGORY_NONE;
    }

    if (!category_alias_inited) {
        category_alias_inited = true;
        std::fill(std::begin(category_alias), std::end(category_alias), (e_labor_category)-2);
        for (const auto &cat : category_alias_default) {
            category_alias[cat.btype] = cat.category;
        }
    }

    e_labor_category cat = category_alias[b->type];
    return cat >= 0 ? cat : (e_labor_category)category_for_int_arr_ph[b->type];
}

struct labor_priority_t {
    e_labor_category category;
    int workers;
};

labor_priority_t DEFAULT_PRIORITY[] = {
  {LABOR_CATEGORY_INFRASTRUCTURE, 3},
  {LABOR_CATEGORY_WATER_HEALTH, 1},
  {LABOR_CATEGORY_GOVERNMENT, 3},
  {LABOR_CATEGORY_MILITARY, 2},
  {LABOR_CATEGORY_FOOD_PRODUCTION, 4},
  {LABOR_CATEGORY_INDUSTRY_COMMERCE, 2},
  {LABOR_CATEGORY_ENTERTAINMENT, 1},
  {LABOR_CATEGORY_EDUCATION, 1},
  {LABOR_CATEGORY_RELIGION, 1},
};

static bool is_industry_disabled(building* b) {
    int resource = b->output.resource;
    return g_city.resource.mothballed[resource];
}

int city_labor_t::workers_allocated(int category) const {
    return categories[category].workers_allocated;
}

void city_labor_t::calculate_workers(int num_plebs, int num_patricians) {
    auto &population = g_city.population;
    population.percentage_plebs = calc_percentage(num_plebs, num_plebs + num_patricians);

    if (!!game_features::gameplay_change_fixed_workers) {
        population.working_age = calc_adjust_with_percentage(num_plebs, 38);
        workers_available = population.working_age;
    } else {
        const int num_in_working_age = population.get_people_of_working_age();
        population.working_age = calc_adjust_with_percentage(num_in_working_age, 60);
        workers_available = calc_adjust_with_percentage(g_city.population.working_age, g_city.population.percentage_plebs);
    }
}

static bool should_have_workers(building* b, int category, int check_access) {
    if (category < 0)
        return false;

    if (category == LABOR_CATEGORY_ENTERTAINMENT) {
        if (b->type == BUILDING_SENET_HOUSE && b->prev_part_building_id)
            return false;
    } else if (category == LABOR_CATEGORY_FOOD_PRODUCTION || category == LABOR_CATEGORY_INDUSTRY_COMMERCE) {
        if (is_industry_disabled(b))
            return false;
    }

    if (check_access)
        return b->houses_covered > 0 ? 1 : 0;

    return true;
}

void city_labor_t::calculate_workers_needed_per_category() {
    for (int cat = 0; cat < LABOR_CATEGORY_SIZE; cat++) {
        categories[cat].buildings = 0;
        categories[cat].total_houses_covered = 0;
        categories[cat].workers_allocated = 0;
        categories[cat].workers_needed = 0;
    }

    buildings_valid_do([this] (building &b) {
        e_labor_category category = category_for_building(&b);
        b.labor_category = category;

        // exception for floodplain farms in Pharaoh
        // it cover by distance from work camp
        if (b.is_floodplain_farm()) {
            b.labor_category = LABOR_CATEGORY_NONE;
        }

        if (!should_have_workers(&b, category, 1)) {
            return;
        }

        categories[category].workers_needed += b.max_workers;
        categories[category].total_houses_covered += b.houses_covered;
        categories[category].buildings++;
    });
}

void city_labor_t::set_building_worker_weight() {
    int water_per_10k_per_building = calc_percentage(100, categories[LABOR_CATEGORY_WATER_HEALTH].buildings);
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        e_labor_category cat = category_for_building(b);
        if (cat == LABOR_CATEGORY_WATER_HEALTH) {
            b->percentage_houses_covered = water_per_10k_per_building;
        } else if (cat >= 0) {
            b->percentage_houses_covered = 0;
            if (b->houses_covered) {
                b->percentage_houses_covered = calc_percentage(100 * b->houses_covered, categories[cat].total_houses_covered);
            }
        }
    }
}

void city_labor_t::allocate_workers_to_categories() {
    int workers_needed_l = 0;
    for (int i = 0; i < LABOR_CATEGORY_SIZE; i++) {
        categories[i].workers_allocated = 0;
        workers_needed_l += categories[i].workers_needed;
    }
    workers_needed = 0;
    if (workers_needed_l <= workers_available) {
        for (int i = 0; i < LABOR_CATEGORY_SIZE; i++) {
            categories[i].workers_allocated = categories[i].workers_needed;
        }
        workers_employed = workers_needed_l;
    } else {
        // not enough workers
        int available = workers_available;
        // distribute by user-defined priority
        for (int p = 1; p <= 9 && available > 0; p++) {
            for (int c = 0; c < 9; c++) {
                if (p == categories[c].priority) {
                    int to_allocate = categories[c].workers_needed;
                    if (to_allocate > available)
                        to_allocate = available;

                    categories[c].workers_allocated = to_allocate;
                    available -= to_allocate;
                    break;
                }
            }
        }
        // (sort of) round-robin distribution over unprioritized categories:
        int guard = 0;
        do {
            guard++;
            if (guard >= workers_available) {
                break;
            }

            for (int p = 0; p < 9; p++) {
                int cat = DEFAULT_PRIORITY[p].category;
                if (!categories[cat].priority) {
                    int needed = categories[cat].workers_needed - categories[cat].workers_allocated;
                    if (needed > 0) {
                        int to_allocate = DEFAULT_PRIORITY[p].workers;
                        if (to_allocate > available)
                            to_allocate = available;

                        if (to_allocate > needed)
                            to_allocate = needed;

                        categories[cat].workers_allocated += to_allocate;
                        available -= to_allocate;
                        if (available <= 0)
                            break;
                    }
                }
            }
        } while (available > 0);

        workers_employed = workers_available;
        for (int i = 0; i < 9; i++) {
            workers_needed += categories[i].workers_needed - categories[i].workers_allocated;
        }
    }
    workers_unemployed = workers_available - workers_employed;
    unemployment_percentage = calc_percentage(workers_unemployed, workers_available);
}

void city_labor_t::allocate_workers_to_water() {
    //if (GAME_ENV == ENGINE_ENV_PHARAOH)
        return;

    static int start_building_id = 1;
    labor_category* water_cat = &categories[LABOR_CATEGORY_WATER_HEALTH];

    int percentage_not_filled = 100 - calc_percentage(water_cat->workers_allocated, water_cat->workers_needed);

    int buildings_to_skip = calc_adjust_with_percentage(water_cat->buildings, percentage_not_filled);

    int workers_per_building;
    if (buildings_to_skip == water_cat->buildings)
        workers_per_building = 1;
    else {
        workers_per_building = water_cat->workers_allocated / (water_cat->buildings - buildings_to_skip);
    }
    int building_id = start_building_id;
    start_building_id = 0;
    for (int guard = 1; guard < MAX_BUILDINGS; guard++, building_id++) {
        if (building_id >= MAX_BUILDINGS)
            building_id = 1;

        building* b = building_get(building_id);
        if (b->state != BUILDING_STATE_VALID || category_for_building(b) != LABOR_CATEGORY_WATER_HEALTH)
            continue;

        b->num_workers = 0;
        if (b->percentage_houses_covered > 0) {
            if (percentage_not_filled > 0) {
                if (buildings_to_skip) {
                    --buildings_to_skip;
                } else if (start_building_id) {
                    b->num_workers = workers_per_building;
                } else {
                    start_building_id = building_id;
                    b->num_workers = workers_per_building;
                }
            } else {
                b->num_workers = b->max_workers;
            }
        }
    }
    if (!start_building_id) {
        // no buildings assigned or full employment
        start_building_id = 1;
    }
}

void city_labor_t::allocate_workers_to_non_water_buildings() {
    int category_workers_needed[LABOR_CATEGORY_SIZE];
    int category_workers_allocated[LABOR_CATEGORY_SIZE];
    for (int i = 0; i < LABOR_CATEGORY_SIZE; i++) {
        category_workers_allocated[i] = 0;
        category_workers_needed[i] = categories[i].workers_allocated < categories[i].workers_needed ? 1 : 0;
    }

    buildings_valid_do([&] (building &b) {
        e_labor_category cat = category_for_building(&b);
        if (b.is_floodplain_farm()) {
            auto &d = b.dcast_farm()->runtime_data();
            if (d.labor_state <= 0) {
                b.num_workers = 0;
            }
            return; // water is handled by allocate_workers_to_water(void) in C3

        } else {
            if (b.houses_covered <= 0) {
                b.num_workers = 0;
            }
        }

        if (!should_have_workers(&b, cat, 0)) {
            return;
        }

        if (b.percentage_houses_covered > 0) {
            const int required_workers = b.max_workers;
            if (category_workers_needed[cat]) {
                short num_workers = calc_adjust_with_percentage<short>(categories[cat].workers_allocated, b.percentage_houses_covered) / 100;
                if (num_workers > required_workers) {
                    num_workers = required_workers;
                }

                b.num_workers = num_workers;
                category_workers_allocated[cat] += num_workers;
            } else {
                b.num_workers = required_workers;
            }
        }
    });

    for (int i = 0; i < LABOR_CATEGORY_SIZE; i++) {
        if (category_workers_needed[i]) {
            // watch out: category_workers_needed is now reset to 'unallocated workers available'
            if (category_workers_allocated[i] >= categories[i].workers_allocated) {
                category_workers_needed[i] = 0;
                category_workers_allocated[i] = 0;
            } else {
                category_workers_needed[i] = categories[i].workers_allocated - category_workers_allocated[i];
            }
        }
    }
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;
        e_labor_category cat = category_for_building(b);
        if (cat < 0)
            continue;

        if (!should_have_workers(b, cat, 0))
            continue;

        if (b->percentage_houses_covered > 0 && category_workers_needed[cat]) {
            int required_workers = b->max_workers;
            if (b->num_workers < required_workers) {
                int needed = required_workers - b->num_workers;
                if (needed > category_workers_needed[cat]) {
                    b->num_workers += category_workers_needed[cat];
                    category_workers_needed[cat] = 0;
                } else {
                    b->num_workers += needed;
                    category_workers_needed[cat] -= needed;
                }
            }
        }
    }
}

void city_labor_t::allocate_workers_to_buildings() {
    set_building_worker_weight();
    allocate_workers_to_water();
    allocate_workers_to_non_water_buildings();
}

void city_labor_t::check_employment() {
    int orig_needed = workers_needed;
    allocate_workers_to_categories();
    // senate unemployment display is delayed when unemployment is rising
    if (unemployment_percentage < unemployment_percentage_for_goverment) {
        unemployment_percentage_for_goverment = unemployment_percentage;
    } else if (unemployment_percentage < unemployment_percentage_for_goverment + 5) {
        unemployment_percentage_for_goverment = unemployment_percentage;
    } else {
        unemployment_percentage_for_goverment += 5;
    }

    unemployment_percentage_for_goverment = std::clamp<int>(unemployment_percentage_for_goverment, 0, 100);

    // workers needed message
    if (!orig_needed && workers_needed > 0) {
        city_message_post_with_message_delay(MESSAGE_CAT_WORKERS_NEEDED, 0, "message_workers_needed", 6);
    }
}
void city_labor_t::allocate_workers() {
    allocate_workers_to_categories();
    allocate_workers_to_buildings();
}

void city_labor_t::update() {
    OZZY_PROFILER_FUNCTION();
    calculate_workers_needed_per_category();
    check_employment();
    allocate_workers_to_buildings();
}

void city_labor_t::set_priority(int category, int new_priority) {
    int old_priority = categories[category].priority;
    if (old_priority == new_priority)
        return;
    int shift;
    int from_prio;
    int to_prio;
    if (!old_priority && new_priority) {
        // shift all bigger than 'new_priority' by one down (+1)
        shift = 1;
        from_prio = new_priority;
        to_prio = 9;
    } else if (old_priority && !new_priority) {
        // shift all bigger than 'old_priority' by one up (-1)
        shift = -1;
        from_prio = old_priority;
        to_prio = 9;
    } else if (new_priority < old_priority) {
        // shift all between new and old by one down (+1)
        shift = 1;
        from_prio = new_priority;
        to_prio = old_priority;
    } else {
        // shift all between old and new by one up (-1)
        shift = -1;
        from_prio = old_priority;
        to_prio = new_priority;
    }
    categories[category].priority = new_priority;
    for (int i = 0; i < 9; i++) {
        if (i == category)
            continue;

        int current_priority = categories[i].priority;
        if (from_prio <= current_priority && current_priority <= to_prio)
            categories[i].priority += shift;
    }
    g_city.labor.allocate_workers();
}

int city_labor_t::max_selectable_priority(int category) {
    int max = 0;
    for (int i = 0; i < 9; i++) {
        if (categories[i].priority > 0)
            ++max;
    }
    if (max < 9 && !categories[category].priority) {
        // allow space for new priority
        ++max;
    }
    return max;
}
