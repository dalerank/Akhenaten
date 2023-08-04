#include "editor.h"

#include "core/string.h"
#include "grid/grid.h"
#include "io/gamefiles/lang.h"
#include "scenario/property.h"
#include "scenario/scenario_data.h"

#include <string.h>

static const struct {
    int width;
    int height;
} MAP_SIZES[] = {{40, 40}, {60, 60}, {80, 80}, {100, 100}, {120, 120}, {160, 160}};

// static void init_point(map_point *point) {
//     point->x = -1;
//     point->y = -1;
// }

void scenario_editor_create(int map_size) {
    memset(&g_scenario_data, 0, sizeof(g_scenario_data));

    g_scenario_data.map.width = MAP_SIZES[map_size].width;
    g_scenario_data.map.height = MAP_SIZES[map_size].height;
    g_scenario_data.map.border_size = GRID_LENGTH - g_scenario_data.map.width;
    g_scenario_data.map.start_offset
      = (GRID_LENGTH - g_scenario_data.map.height) / 2 * GRID_LENGTH + (GRID_LENGTH - g_scenario_data.map.width) / 2;

    string_copy(lang_get_string(44, 37), g_scenario_data.subtitle, MAX_SUBTITLE);
    string_copy(lang_get_string(44, 38), g_scenario_data.brief_description, MAX_BRIEF_DESCRIPTION);

    g_scenario_data.initial_funds = 1000;
    g_scenario_data.rescue_loan = 500;
    g_scenario_data.start_year = -500;

    g_scenario_data.win_criteria.milestone25_year = 10;
    g_scenario_data.win_criteria.milestone50_year = 20;
    g_scenario_data.win_criteria.milestone75_year = 30;

    for (int i = 0; i < MAX_ALLOWED_BUILDINGS; i++) {
        g_scenario_data.allowed_buildings[i] = 1;
    }
    g_scenario_data.rome_supplies_wheat = 0;

    g_scenario_data.win_criteria.culture.goal = 10;
    g_scenario_data.win_criteria.culture.enabled = 1;
    g_scenario_data.win_criteria.prosperity.goal = 10;
    g_scenario_data.win_criteria.prosperity.enabled = 1;
    g_scenario_data.win_criteria.monuments.goal = 10;
    g_scenario_data.win_criteria.monuments.enabled = 1;
    g_scenario_data.win_criteria.kingdom.goal = 10;
    g_scenario_data.win_criteria.kingdom.enabled = 1;
    g_scenario_data.win_criteria.population.goal = 0;
    g_scenario_data.win_criteria.population.enabled = 0;

    g_scenario_data.win_criteria.time_limit.years = 0;
    g_scenario_data.win_criteria.time_limit.enabled = 0;
    g_scenario_data.win_criteria.survival_time.years = 0;
    g_scenario_data.win_criteria.survival_time.enabled = 0;

    g_scenario_data.earthquake.severity = 0;
    g_scenario_data.earthquake.year = 0;

    g_scenario_data.earthquake_point.set(-1);
    g_scenario_data.entry_point.set(-1);
    g_scenario_data.exit_point.set(-1);
    g_scenario_data.river_entry_point.set(-1);
    g_scenario_data.river_exit_point.set(-1);
    for (int i = 0; i < MAX_INVASION_POINTS_LAND; i++)
        g_scenario_data.invasion_points_land[i].set(-1);
    for (int i = 0; i < MAX_INVASION_POINTS_SEA; i++)
        g_scenario_data.invasion_points_sea[i].set(-1);

    for (int i = 0; i < MAX_FISH_POINTS; i++)
        g_scenario_data.fishing_points[i].set(-1);
    for (int i = 0; i < MAX_PREDATOR_HERD_POINTS; i++)
        g_scenario_data.herd_points_predator[i].set(-1);
    for (int i = 0; i < MAX_PREY_HERD_POINTS; i++)
        g_scenario_data.herd_points_prey[i].set(-1);

    for (int i = 0; i < MAX_REQUESTS; i++) {
        g_scenario_data.requests[i].deadline_years = 5;
        g_scenario_data.requests[i].kingdom = 8;
    }
    for (int i = 0; i < MAX_INVASIONS; i++) {
        g_scenario_data.invasions[i].from = 8;
    }

    g_scenario_data.is_saved = 1;
}

void scenario_editor_set_native_images(int image_hut, int image_meeting, int image_crops) {
    g_scenario_data.native_images.hut = image_hut;
    g_scenario_data.native_images.meeting = image_meeting;
    g_scenario_data.native_images.crops = image_crops;
}

void scenario_editor_request_get(int index, editor_request* request) {
    request->year = g_scenario_data.requests[index].year;
    request->amount = g_scenario_data.requests[index].amount;
    request->resource = g_scenario_data.requests[index].resource;
    request->deadline_years = g_scenario_data.requests[index].deadline_years;
    request->kingdom = g_scenario_data.requests[index].kingdom;
}

static void sort_requests(void) {
    for (int i = 0; i < MAX_REQUESTS; i++) {
        for (int j = MAX_REQUESTS - 1; j > 0; j--) {
            request_t* current = &g_scenario_data.requests[j];
            request_t* prev = &g_scenario_data.requests[j - 1];
            if (current->resource && (!prev->resource || prev->year > current->year)) {
                request_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_request_delete(int index) {
    g_scenario_data.requests[index].year = 0;
    g_scenario_data.requests[index].amount = 0;
    g_scenario_data.requests[index].resource = RESOURCE_NONE;
    g_scenario_data.requests[index].deadline_years = 5;
    g_scenario_data.requests[index].kingdom = 8;
    sort_requests();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_request_save(int index, editor_request* request) {
    g_scenario_data.requests[index].year = request->year;
    g_scenario_data.requests[index].amount = request->amount;
    g_scenario_data.requests[index].resource = request->resource;
    g_scenario_data.requests[index].deadline_years = request->deadline_years;
    g_scenario_data.requests[index].kingdom = request->kingdom;
    sort_requests();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_invasion_get(int index, editor_invasion* invasion) {
    invasion->year = g_scenario_data.invasions[index].year;
    invasion->type = g_scenario_data.invasions[index].type;
    invasion->amount = g_scenario_data.invasions[index].amount;
    invasion->from = g_scenario_data.invasions[index].from;
    invasion->attack_type = g_scenario_data.invasions[index].attack_type;
}

static void sort_invasions(void) {
    for (int i = 0; i < MAX_INVASIONS; i++) {
        for (int j = MAX_INVASIONS - 1; j > 0; j--) {
            invasion_t* current = &g_scenario_data.invasions[j];
            invasion_t* prev = &g_scenario_data.invasions[j - 1];
            if (current->type && (!prev->type || prev->year > current->year)) {
                invasion_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_invasion_delete(int index) {
    g_scenario_data.invasions[index].year = 0;
    g_scenario_data.invasions[index].amount = 0;
    g_scenario_data.invasions[index].type = 0;
    g_scenario_data.invasions[index].from = 8;
    g_scenario_data.invasions[index].attack_type = 0;
    sort_invasions();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_invasion_save(int index, editor_invasion* invasion) {
    g_scenario_data.invasions[index].year = invasion->type ? invasion->year : 0;
    g_scenario_data.invasions[index].amount = invasion->type ? invasion->amount : 0;
    g_scenario_data.invasions[index].type = invasion->type;
    g_scenario_data.invasions[index].from = invasion->from;
    g_scenario_data.invasions[index].attack_type = invasion->attack_type;
    sort_invasions();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_price_change_get(int index, editor_price_change* price_change) {
    price_change->year = g_scenario_data.price_changes[index].year;
    price_change->resource = g_scenario_data.price_changes[index].resource;
    price_change->amount = g_scenario_data.price_changes[index].amount;
    price_change->is_rise = g_scenario_data.price_changes[index].is_rise;
}

static void sort_price_changes(void) {
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        if (!g_scenario_data.price_changes[i].resource)
            g_scenario_data.price_changes[i].year = 0;
    }
    for (int i = 0; i < MAX_PRICE_CHANGES; i++) {
        for (int j = MAX_PRICE_CHANGES - 1; j > 0; j--) {
            price_change_t* current = &g_scenario_data.price_changes[j];
            price_change_t* prev = &g_scenario_data.price_changes[j - 1];
            if (current->year && (!prev->year || prev->year > current->year)) {
                price_change_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_price_change_delete(int index) {
    g_scenario_data.price_changes[index].year = 0;
    g_scenario_data.price_changes[index].resource = 0;
    g_scenario_data.price_changes[index].amount = 0;
    g_scenario_data.price_changes[index].is_rise = 0;
    sort_price_changes();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_price_change_save(int index, editor_price_change* price_change) {
    g_scenario_data.price_changes[index].year = price_change->year;
    g_scenario_data.price_changes[index].resource = price_change->resource;
    g_scenario_data.price_changes[index].amount = price_change->amount;
    g_scenario_data.price_changes[index].is_rise = price_change->is_rise;
    sort_price_changes();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_demand_change_get(int index, editor_demand_change* demand_change) {
    demand_change->year = g_scenario_data.demand_changes[index].year;
    demand_change->resource = g_scenario_data.demand_changes[index].resource;
    demand_change->route_id = g_scenario_data.demand_changes[index].route_id;
    demand_change->is_rise = g_scenario_data.demand_changes[index].is_rise;
}

static void sort_demand_changes(void) {
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        if (!g_scenario_data.demand_changes[i].resource)
            g_scenario_data.demand_changes[i].year = 0;
    }
    for (int i = 0; i < MAX_DEMAND_CHANGES; i++) {
        for (int j = MAX_DEMAND_CHANGES - 1; j > 0; j--) {
            demand_change_t* current = &g_scenario_data.demand_changes[j];
            demand_change_t* prev = &g_scenario_data.demand_changes[j - 1];
            if (current->year && (!prev->year || prev->year > current->year)) {
                demand_change_t tmp = *current;
                *current = *prev;
                *prev = tmp;
            }
        }
    }
}

void scenario_editor_demand_change_delete(int index) {
    g_scenario_data.demand_changes[index].year = 0;
    g_scenario_data.demand_changes[index].resource = 0;
    g_scenario_data.demand_changes[index].route_id = 0;
    g_scenario_data.demand_changes[index].is_rise = 0;
    sort_demand_changes();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_demand_change_save(int index, editor_demand_change* demand_change) {
    g_scenario_data.demand_changes[index].year = demand_change->year;
    g_scenario_data.demand_changes[index].resource = demand_change->resource;
    g_scenario_data.demand_changes[index].route_id = demand_change->route_id;
    g_scenario_data.demand_changes[index].is_rise = demand_change->is_rise;
    sort_demand_changes();
    g_scenario_data.is_saved = 0;
}

void scenario_editor_cycle_image(int forward) {
    if (forward)
        g_scenario_data.image_id++;
    else {
        g_scenario_data.image_id--;
    }
    if (g_scenario_data.image_id < 0)
        g_scenario_data.image_id = 15;

    if (g_scenario_data.image_id > 15)
        g_scenario_data.image_id = 0;

    g_scenario_data.is_saved = 0;
}

void scenario_editor_cycle_climate(void) {
    switch (g_scenario_data.climate) {
    case CLIMATE_CENTRAL:
        g_scenario_data.climate = CLIMATE_NORTHERN;
        break;
    case CLIMATE_NORTHERN:
        g_scenario_data.climate = CLIMATE_DESERT;
        break;
    case CLIMATE_DESERT:
    default:
        g_scenario_data.climate = CLIMATE_CENTRAL;
        break;
    }
    g_scenario_data.is_saved = 0;
}

void scenario_editor_update_subtitle(const char* new_description) {
    if (!string_equals(g_scenario_data.subtitle, (const uint8_t*)new_description, 1)) {
        string_copy((const uint8_t*)new_description, g_scenario_data.subtitle, MAX_SUBTITLE);
        g_scenario_data.is_saved = 0;
    }
}

void scenario_editor_set_enemy(int enemy_id) {
    g_scenario_data.enemy_id = enemy_id;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_change_empire(int change) {
    g_scenario_data.empire.id += change;
    if (g_scenario_data.empire.id < 0)
        g_scenario_data.empire.id = 39;
    else if (g_scenario_data.empire.id >= 40)
        g_scenario_data.empire.id = 0;

    g_scenario_data.is_saved = 0;
}

int scenario_editor_is_building_allowed(int id) {
    return g_scenario_data.allowed_buildings[id];
}

void scenario_editor_toggle_building_allowed(int id) {
    g_scenario_data.allowed_buildings[id] = g_scenario_data.allowed_buildings[id] ? 0 : 1;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_player_rank(int rank) {
    g_scenario_data.player_rank = rank;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_initial_funds(int amount) {
    g_scenario_data.initial_funds = amount;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_rescue_loan(int amount) {
    g_scenario_data.rescue_loan = amount;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_rome_supplies_wheat(void) {
    g_scenario_data.rome_supplies_wheat = !g_scenario_data.rome_supplies_wheat;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_flotsam(void) {
    g_scenario_data.flotsam_enabled = !g_scenario_data.flotsam_enabled;
    g_scenario_data.is_saved = 0;
}

int scenario_editor_milestone_year(int milestone_percentage) {
    switch (milestone_percentage) {
    case 25:
        return g_scenario_data.win_criteria.milestone25_year;
    case 50:
        return g_scenario_data.win_criteria.milestone50_year;
    case 75:
        return g_scenario_data.win_criteria.milestone75_year;
    default:
        return 0;
    }
}

void scenario_editor_set_milestone_year(int milestone_percentage, int year) {
    switch (milestone_percentage) {
    case 25:
        g_scenario_data.win_criteria.milestone25_year = year;
        break;
    case 50:
        g_scenario_data.win_criteria.milestone50_year = year;
        break;
    case 75:
        g_scenario_data.win_criteria.milestone75_year = year;
        break;
    default:
        return;
    }
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_start_year(int year) {
    g_scenario_data.start_year = year;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_open_play(void) {
    g_scenario_data.is_open_play = !g_scenario_data.is_open_play;
    if (g_scenario_data.is_open_play)
        g_scenario_data.open_play_scenario_id = 12; // fix it to 12: first unused entry

    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_culture(void) {
    g_scenario_data.win_criteria.culture.enabled = !g_scenario_data.win_criteria.culture.enabled;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_culture(int goal) {
    g_scenario_data.win_criteria.culture.goal = goal;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_prosperity(void) {
    g_scenario_data.win_criteria.prosperity.enabled = !g_scenario_data.win_criteria.prosperity.enabled;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_prosperity(int goal) {
    g_scenario_data.win_criteria.prosperity.goal = goal;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_monument(void) {
    g_scenario_data.win_criteria.monuments.enabled = !g_scenario_data.win_criteria.monuments.enabled;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_monument(int goal) {
    g_scenario_data.win_criteria.monuments.goal = goal;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_kingdom(void) {
    g_scenario_data.win_criteria.kingdom.enabled = !g_scenario_data.win_criteria.kingdom.enabled;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_kingdom(int goal) {
    g_scenario_data.win_criteria.kingdom.goal = goal;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_population(void) {
    g_scenario_data.win_criteria.population.enabled = !g_scenario_data.win_criteria.population.enabled;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_population(int goal) {
    g_scenario_data.win_criteria.population.goal = goal;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_time_limit(void) {
    g_scenario_data.win_criteria.time_limit.enabled = !g_scenario_data.win_criteria.time_limit.enabled;
    if (g_scenario_data.win_criteria.time_limit.enabled)
        g_scenario_data.win_criteria.survival_time.enabled = 0;

    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_time_limit(int years) {
    g_scenario_data.win_criteria.time_limit.years = years;
    g_scenario_data.is_saved = 0;
}

void scenario_editor_toggle_survival_time(void) {
    g_scenario_data.win_criteria.survival_time.enabled = !g_scenario_data.win_criteria.survival_time.enabled;
    if (g_scenario_data.win_criteria.survival_time.enabled)
        g_scenario_data.win_criteria.time_limit.enabled = 0;

    g_scenario_data.is_saved = 0;
}

void scenario_editor_set_survival_time(int years) {
    g_scenario_data.win_criteria.survival_time.years = years;
    g_scenario_data.is_saved = 0;
}
