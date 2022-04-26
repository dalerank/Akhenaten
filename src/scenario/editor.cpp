#include "editor.h"

#include "core/lang.h"
#include "core/string.h"
#include "map/grid.h"
#include "scenario/data.h"
#include "scenario/property.h"

#include <string.h>

static const struct {
    int width;
    int height;
} MAP_SIZES[] = {
        {40,  40},
        {60,  60},
        {80,  80},
        {100, 100},
        {120, 120},
        {160, 160}
};

static void init_point(map_point *point) {
    point->x = -1;
    point->y = -1;
}

void scenario_editor_create(int map_size) {
    memset(&scenario_data, 0, sizeof(scenario_data));

    scenario_data.map.width = MAP_SIZES[map_size].width;
    scenario_data.map.height = MAP_SIZES[map_size].height;
    scenario_data.map.grid_border_size = GRID_LENGTH - scenario_data.map.width;
    scenario_data.map.grid_start = (GRID_LENGTH - scenario_data.map.height) / 2 * GRID_LENGTH +
                                   (GRID_LENGTH - scenario_data.map.width) / 2;

    string_copy(lang_get_string(44, 37), scenario_data.subtitle, MAX_SUBTITLE);
    string_copy(lang_get_string(44, 38), scenario_data.brief_description, MAX_BRIEF_DESCRIPTION);

    scenario_data.initial_funds = 1000;
    scenario_data.rescue_loan = 500;
    scenario_data.start_year = -500;

    scenario_data.win_criteria.milestone25_year = 10;
    scenario_data.win_criteria.milestone50_year = 20;
    scenario_data.win_criteria.milestone75_year = 30;

    for (int i = 0; i < MAX_ALLOWED_BUILDINGS; i++) {
        scenario_data.allowed_buildings[i] = 1;
    }
    scenario_data.rome_supplies_wheat = 0;

    scenario_data.win_criteria.culture.goal = 10;
    scenario_data.win_criteria.culture.enabled = 1;
    scenario_data.win_criteria.prosperity.goal = 10;
    scenario_data.win_criteria.prosperity.enabled = 1;
    scenario_data.win_criteria.monuments.goal = 10;
    scenario_data.win_criteria.monuments.enabled = 1;
    scenario_data.win_criteria.kingdom.goal = 10;
    scenario_data.win_criteria.kingdom.enabled = 1;
    scenario_data.win_criteria.population.goal = 0;
    scenario_data.win_criteria.population.enabled = 0;

    scenario_data.win_criteria.time_limit.years = 0;
    scenario_data.win_criteria.time_limit.enabled = 0;
    scenario_data.win_criteria.survival_time.years = 0;
    scenario_data.win_criteria.survival_time.enabled = 0;

    scenario_data.earthquake.severity = 0;
    scenario_data.earthquake.year = 0;

    init_point(&scenario_data.earthquake_point);
    init_point(&scenario_data.entry_point);
    init_point(&scenario_data.exit_point);
    init_point(&scenario_data.river_entry_point);
    init_point(&scenario_data.river_exit_point);
    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++)
        init_point(&scenario_data.invasion_points_land[i]);
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++)
        init_point(&scenario_data.invasion_points_sea[i]);

    for (int i = 0; i < MAX_FISH_POINTS; i++)
        init_point(&scenario_data.fishing_points[i]);
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++)
        init_point(&scenario_data.herd_points_predator[i]);
    for (int i = 0; i < MAX_PREY_HERD_POINTS; i++)
        init_point(&scenario_data.herd_points_prey[i]);

    for (int i = 0; i < MAX_REQUESTS; i++) {
        scenario_data.requests[i].deadline_years = 5;
        scenario_data.requests[i].favor = 8;
    }
    for (int i = 0; i < MAX_INVASIONS; i++) {
        scenario_data.invasions[i].from = 8;
    }

    scenario_data.is_saved = 1;
}

void scenario_editor_set_native_images(int image_hut, int image_meeting, int image_crops) {
    scenario_data.native_images.hut = image_hut;
    scenario_data.native_images.meeting = image_meeting;
    scenario_data.native_images.crops = image_crops;
}

void scenario_editor_request_get(int index, editor_request *request) {
    request->year = scenario_data.requests[index].year;
    request->amount = scenario_data.requests[index].amount;
    request->resource = scenario_data.requests[index].resource;
    request->deadline_years = scenario_data.requests[index].deadline_years;
    request->favor = scenario_data.requests[index].favor;
}

static void sort_requests(void) {
    for (int i = 0; i < MAX_REQUESTS; i++) {
        for (int j = MAX_REQUESTS - 1; j > 0; j--) {
            request_t *current = &scenario_data.requests[j];
            request_t *prev = &scenario_data.requests[j - 1];
            if (current->resource && (!prev->resource || prev->year > current->year)) {
                request_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_request_delete(int index) {
    scenario_data.requests[index].year = 0;
    scenario_data.requests[index].amount = 0;
    scenario_data.requests[index].resource = 0;
    scenario_data.requests[index].deadline_years = 5;
    scenario_data.requests[index].favor = 8;
    sort_requests();
    scenario_data.is_saved = 0;
}

void scenario_editor_request_save(int index, editor_request *request) {
    scenario_data.requests[index].year = request->year;
    scenario_data.requests[index].amount = request->amount;
    scenario_data.requests[index].resource = request->resource;
    scenario_data.requests[index].deadline_years = request->deadline_years;
    scenario_data.requests[index].favor = request->favor;
    sort_requests();
    scenario_data.is_saved = 0;
}

void scenario_editor_invasion_get(int index, editor_invasion *invasion) {
    invasion->year = scenario_data.invasions[index].year;
    invasion->type = scenario_data.invasions[index].type;
    invasion->amount = scenario_data.invasions[index].amount;
    invasion->from = scenario_data.invasions[index].from;
    invasion->attack_type = scenario_data.invasions[index].attack_type;
}

static void sort_invasions(void) {
    for (int i = 0; i < MAX_INVASIONS; i++) {
        for (int j = MAX_INVASIONS - 1; j > 0; j--) {
            invasion_t *current = &scenario_data.invasions[j];
            invasion_t *prev = &scenario_data.invasions[j - 1];
            if (current->type && (!prev->type || prev->year > current->year)) {
                invasion_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_invasion_delete(int index) {
    scenario_data.invasions[index].year = 0;
    scenario_data.invasions[index].amount = 0;
    scenario_data.invasions[index].type = 0;
    scenario_data.invasions[index].from = 8;
    scenario_data.invasions[index].attack_type = 0;
    sort_invasions();
    scenario_data.is_saved = 0;
}

void scenario_editor_invasion_save(int index, editor_invasion *invasion) {
    scenario_data.invasions[index].year = invasion->type ? invasion->year : 0;
    scenario_data.invasions[index].amount = invasion->type ? invasion->amount : 0;
    scenario_data.invasions[index].type = invasion->type;
    scenario_data.invasions[index].from = invasion->from;
    scenario_data.invasions[index].attack_type = invasion->attack_type;
    sort_invasions();
    scenario_data.is_saved = 0;
}

void scenario_editor_price_change_get(int index, editor_price_change *price_change) {
    price_change->year = scenario_data.price_changes[index].year;
    price_change->resource = scenario_data.price_changes[index].resource;
    price_change->amount = scenario_data.price_changes[index].amount;
    price_change->is_rise = scenario_data.price_changes[index].is_rise;
}

static void sort_price_changes(void) {
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        if (!scenario_data.price_changes[i].resource)
            scenario_data.price_changes[i].year = 0;

    }
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        for (int j = MAX_PRICE_CHANGES - 1; j > 0; j--) {
            price_change_t *current = &scenario_data.price_changes[j];
            price_change_t *prev = &scenario_data.price_changes[j - 1];
            if (current->year && (!prev->year || prev->year > current->year)) {
                price_change_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_price_change_delete(int index) {
    scenario_data.price_changes[index].year = 0;
    scenario_data.price_changes[index].resource = 0;
    scenario_data.price_changes[index].amount = 0;
    scenario_data.price_changes[index].is_rise = 0;
    sort_price_changes();
    scenario_data.is_saved = 0;
}

void scenario_editor_price_change_save(int index, editor_price_change *price_change) {
    scenario_data.price_changes[index].year = price_change->year;
    scenario_data.price_changes[index].resource = price_change->resource;
    scenario_data.price_changes[index].amount = price_change->amount;
    scenario_data.price_changes[index].is_rise = price_change->is_rise;
    sort_price_changes();
    scenario_data.is_saved = 0;
}

void scenario_editor_demand_change_get(int index, editor_demand_change *demand_change) {
    demand_change->year = scenario_data.demand_changes[index].year;
    demand_change->resource = scenario_data.demand_changes[index].resource;
    demand_change->route_id = scenario_data.demand_changes[index].route_id;
    demand_change->is_rise = scenario_data.demand_changes[index].is_rise;
}

static void sort_demand_changes(void) {
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        if (!scenario_data.demand_changes[i].resource)
            scenario_data.demand_changes[i].year = 0;

    }
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        for (int j = MAX_DEMAND_CHANGES - 1; j > 0; j--) {
            demand_change_t *current = &scenario_data.demand_changes[j];
            demand_change_t *prev = &scenario_data.demand_changes[j - 1];
            if (current->year && (!prev->year || prev->year > current->year)) {
                demand_change_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_demand_change_delete(int index) {
    scenario_data.demand_changes[index].year = 0;
    scenario_data.demand_changes[index].resource = 0;
    scenario_data.demand_changes[index].route_id = 0;
    scenario_data.demand_changes[index].is_rise = 0;
    sort_demand_changes();
    scenario_data.is_saved = 0;
}

void scenario_editor_demand_change_save(int index, editor_demand_change *demand_change) {
    scenario_data.demand_changes[index].year = demand_change->year;
    scenario_data.demand_changes[index].resource = demand_change->resource;
    scenario_data.demand_changes[index].route_id = demand_change->route_id;
    scenario_data.demand_changes[index].is_rise = demand_change->is_rise;
    sort_demand_changes();
    scenario_data.is_saved = 0;
}

void scenario_editor_cycle_image(int forward) {
    if (forward)
        scenario_data.image_id++;
    else {
        scenario_data.image_id--;
    }
    if (scenario_data.image_id < 0)
        scenario_data.image_id = 15;

    if (scenario_data.image_id > 15)
        scenario_data.image_id = 0;

    scenario_data.is_saved = 0;
}

void scenario_editor_cycle_climate(void) {
    switch (scenario_data.climate) {
        case CLIMATE_CENTRAL:
            scenario_data.climate = CLIMATE_NORTHERN;
            break;
        case CLIMATE_NORTHERN:
            scenario_data.climate = CLIMATE_DESERT;
            break;
        case CLIMATE_DESERT:
        default:
            scenario_data.climate = CLIMATE_CENTRAL;
            break;
    }
    scenario_data.is_saved = 0;
}

void scenario_editor_update_subtitle(const uint8_t *new_description) {
    if (!string_equals(scenario_data.subtitle, new_description, 1)) {
        string_copy(new_description, scenario_data.subtitle, MAX_SUBTITLE);
        scenario_data.is_saved = 0;
    }
}

void scenario_editor_set_enemy(int enemy_id) {
    scenario_data.enemy_id = enemy_id;
    scenario_data.is_saved = 0;
}

void scenario_editor_change_empire(int change) {
    scenario_data.empire.id += change;
    if (scenario_data.empire.id < 0)
        scenario_data.empire.id = 39;
    else if (scenario_data.empire.id >= 40)
        scenario_data.empire.id = 0;

    scenario_data.is_saved = 0;
}

int scenario_editor_is_building_allowed(int id) {
    return scenario_data.allowed_buildings[id];
}

void scenario_editor_toggle_building_allowed(int id) {
    scenario_data.allowed_buildings[id] = scenario_data.allowed_buildings[id] ? 0 : 1;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_player_rank(int rank) {
    scenario_data.player_rank = rank;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_initial_funds(int amount) {
    scenario_data.initial_funds = amount;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_rescue_loan(int amount) {
    scenario_data.rescue_loan = amount;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_rome_supplies_wheat(void) {
    scenario_data.rome_supplies_wheat = !scenario_data.rome_supplies_wheat;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_flotsam(void) {
    scenario_data.flotsam_enabled = !scenario_data.flotsam_enabled;
    scenario_data.is_saved = 0;
}

int scenario_editor_milestone_year(int milestone_percentage) {
    switch (milestone_percentage) {
        case 25:
            return scenario_data.win_criteria.milestone25_year;
        case 50:
            return scenario_data.win_criteria.milestone50_year;
        case 75:
            return scenario_data.win_criteria.milestone75_year;
        default:
            return 0;
    }
}

void scenario_editor_set_milestone_year(int milestone_percentage, int year) {
    switch (milestone_percentage) {
        case 25:
            scenario_data.win_criteria.milestone25_year = year;
            break;
        case 50:
            scenario_data.win_criteria.milestone50_year = year;
            break;
        case 75:
            scenario_data.win_criteria.milestone75_year = year;
            break;
        default:
            return;
    }
    scenario_data.is_saved = 0;
}

void scenario_editor_set_start_year(int year) {
    scenario_data.start_year = year;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_open_play(void) {
    scenario_data.is_open_play = !scenario_data.is_open_play;
    if (scenario_data.is_open_play)
        scenario_data.open_play_scenario_id = 12; // fix it to 12: first unused entry

    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_culture(void) {
    scenario_data.win_criteria.culture.enabled = !scenario_data.win_criteria.culture.enabled;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_culture(int goal) {
    scenario_data.win_criteria.culture.goal = goal;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_prosperity(void) {
    scenario_data.win_criteria.prosperity.enabled = !scenario_data.win_criteria.prosperity.enabled;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_prosperity(int goal) {
    scenario_data.win_criteria.prosperity.goal = goal;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_peace(void) {
    scenario_data.win_criteria.monuments.enabled = !scenario_data.win_criteria.monuments.enabled;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_peace(int goal) {
    scenario_data.win_criteria.monuments.goal = goal;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_favor(void) {
    scenario_data.win_criteria.kingdom.enabled = !scenario_data.win_criteria.kingdom.enabled;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_favor(int goal) {
    scenario_data.win_criteria.kingdom.goal = goal;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_population(void) {
    scenario_data.win_criteria.population.enabled = !scenario_data.win_criteria.population.enabled;
    scenario_data.is_saved = 0;
}

void scenario_editor_set_population(int goal) {
    scenario_data.win_criteria.population.goal = goal;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_time_limit(void) {
    scenario_data.win_criteria.time_limit.enabled = !scenario_data.win_criteria.time_limit.enabled;
    if (scenario_data.win_criteria.time_limit.enabled)
        scenario_data.win_criteria.survival_time.enabled = 0;

    scenario_data.is_saved = 0;
}

void scenario_editor_set_time_limit(int years) {
    scenario_data.win_criteria.time_limit.years = years;
    scenario_data.is_saved = 0;
}

void scenario_editor_toggle_survival_time(void) {
    scenario_data.win_criteria.survival_time.enabled = !scenario_data.win_criteria.survival_time.enabled;
    if (scenario_data.win_criteria.survival_time.enabled)
        scenario_data.win_criteria.time_limit.enabled = 0;

    scenario_data.is_saved = 0;
}

void scenario_editor_set_survival_time(int years) {
    scenario_data.win_criteria.survival_time.years = years;
    scenario_data.is_saved = 0;
}
