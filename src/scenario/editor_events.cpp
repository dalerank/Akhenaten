#include "editor_events.h"

#include "scenario/data.h"

int scenario_editor_earthquake_severity(void) {
    return scenario_data.earthquake.severity;
}

int scenario_editor_earthquake_year(void) {
    return scenario_data.earthquake.year;
}

void scenario_editor_earthquake_cycle_severity(void) {
    scenario_data.earthquake.severity++;
    if (scenario_data.earthquake.severity > EARTHQUAKE_LARGE)
        scenario_data.earthquake.severity = EARTHQUAKE_NONE;

    scenario_data.is_saved = 0;
}

void scenario_editor_earthquake_set_year(int year) {
    scenario_data.earthquake.year = year;
    scenario_data.is_saved = 0;
}

int scenario_editor_gladiator_revolt_enabled(void) {
    return scenario_data.gladiator_revolt.enabled;
}

int scenario_editor_gladiator_revolt_year(void) {
    return scenario_data.gladiator_revolt.year;
}

void scenario_editor_gladiator_revolt_toggle_enabled(void) {
    scenario_data.gladiator_revolt.enabled = !scenario_data.gladiator_revolt.enabled;
    scenario_data.is_saved = 0;
}

void scenario_editor_gladiator_revolt_set_year(int year) {
    scenario_data.gladiator_revolt.year = year;
    scenario_data.is_saved = 0;
}

int scenario_editor_emperor_change_enabled(void) {
    return scenario_data.emperor_change.enabled;
}

int scenario_editor_emperor_change_year(void) {
    return scenario_data.emperor_change.year;
}

void scenario_editor_emperor_change_toggle_enabled(void) {
    scenario_data.emperor_change.enabled = !scenario_data.emperor_change.enabled;
    scenario_data.is_saved = 0;
}

void scenario_editor_emperor_change_set_year(int year) {
    scenario_data.emperor_change.year = year;
    scenario_data.is_saved = 0;
}

int scenario_editor_sea_trade_problem_enabled(void) {
    return scenario_data.random_events.sea_trade_problem;
}

void scenario_editor_sea_trade_problem_toggle_enabled(void) {
    scenario_data.random_events.sea_trade_problem = !scenario_data.random_events.sea_trade_problem;
    scenario_data.is_saved = 0;
}

int scenario_editor_land_trade_problem_enabled(void) {
    return scenario_data.random_events.land_trade_problem;
}

void scenario_editor_land_trade_problem_toggle_enabled(void) {
    scenario_data.random_events.land_trade_problem = !scenario_data.random_events.land_trade_problem;
    scenario_data.is_saved = 0;
}

int scenario_editor_raise_wages_enabled(void) {
    return scenario_data.random_events.raise_wages;
}

void scenario_editor_raise_wages_toggle_enabled(void) {
    scenario_data.random_events.raise_wages = !scenario_data.random_events.raise_wages;
    scenario_data.is_saved = 0;
}

int scenario_editor_lower_wages_enabled(void) {
    return scenario_data.random_events.lower_wages;
}

void scenario_editor_lower_wages_toggle_enabled(void) {
    scenario_data.random_events.lower_wages = !scenario_data.random_events.lower_wages;
    scenario_data.is_saved = 0;
}

int scenario_editor_contaminated_water_enabled(void) {
    return scenario_data.random_events.contaminated_water;
}

void scenario_editor_contaminated_water_toggle_enabled(void) {
    scenario_data.random_events.contaminated_water = !scenario_data.random_events.contaminated_water;
    scenario_data.is_saved = 0;
}

int scenario_editor_iron_mine_collapse_enabled(void) {
    return scenario_data.random_events.iron_mine_collapse;
}

void scenario_editor_iron_mine_collapse_toggle_enabled(void) {
    scenario_data.random_events.iron_mine_collapse = !scenario_data.random_events.iron_mine_collapse;
    scenario_data.is_saved = 0;
}

int scenario_editor_clay_pit_flooded_enabled(void) {
    return scenario_data.random_events.clay_pit_flooded;
}

void scenario_editor_clay_pit_flooded_toggle_enabled(void) {
    scenario_data.random_events.clay_pit_flooded = !scenario_data.random_events.clay_pit_flooded;
    scenario_data.is_saved = 0;
}
