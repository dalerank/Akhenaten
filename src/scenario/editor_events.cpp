#include "editor_events.h"

#include "scenario/scenario.h"

int scenario_editor_earthquake_severity(void) {
    return g_scenario.earthquake.severity;
}

int scenario_editor_earthquake_year(void) {
    return g_scenario.earthquake.year;
}

void scenario_editor_earthquake_cycle_severity(void) {
    g_scenario.earthquake.severity++;
    if (g_scenario.earthquake.severity > EARTHQUAKE_LARGE)
        g_scenario.earthquake.severity = EARTHQUAKE_NONE;

    g_scenario.is_saved = 0;
}

void scenario_editor_earthquake_set_year(int year) {
    g_scenario.earthquake.year = year;
    g_scenario.is_saved = 0;
}

int scenario_editor_gladiator_revolt_enabled(void) {
    return g_scenario.gladiator_revolt.enabled;
}

int scenario_editor_gladiator_revolt_year(void) {
    return g_scenario.gladiator_revolt.year;
}

void scenario_editor_gladiator_revolt_toggle_enabled(void) {
    g_scenario.gladiator_revolt.enabled = !g_scenario.gladiator_revolt.enabled;
    g_scenario.is_saved = 0;
}

void scenario_editor_gladiator_revolt_set_year(int year) {
    g_scenario.gladiator_revolt.year = year;
    g_scenario.is_saved = 0;
}

int scenario_editor_emperor_change_enabled(void) {
    return g_scenario.emperor_change.enabled;
}

int scenario_editor_emperor_change_year(void) {
    return g_scenario.emperor_change.year;
}

void scenario_editor_emperor_change_toggle_enabled(void) {
    g_scenario.emperor_change.enabled = !g_scenario.emperor_change.enabled;
    g_scenario.is_saved = 0;
}

void scenario_editor_emperor_change_set_year(int year) {
    g_scenario.emperor_change.year = year;
    g_scenario.is_saved = 0;
}

int scenario_editor_sea_trade_problem_enabled(void) {
    return g_scenario.random_events.sea_trade_problem;
}

void scenario_editor_sea_trade_problem_toggle_enabled(void) {
    g_scenario.random_events.sea_trade_problem = !g_scenario.random_events.sea_trade_problem;
    g_scenario.is_saved = 0;
}

int scenario_editor_land_trade_problem_enabled(void) {
    return g_scenario.random_events.land_trade_problem;
}

void scenario_editor_land_trade_problem_toggle_enabled(void) {
    g_scenario.random_events.land_trade_problem = !g_scenario.random_events.land_trade_problem;
    g_scenario.is_saved = 0;
}

int scenario_editor_raise_wages_enabled(void) {
    return g_scenario.random_events.raise_wages;
}

void scenario_editor_raise_wages_toggle_enabled(void) {
    g_scenario.random_events.raise_wages = !g_scenario.random_events.raise_wages;
    g_scenario.is_saved = 0;
}

int scenario_editor_lower_wages_enabled(void) {
    return g_scenario.random_events.lower_wages;
}

void scenario_editor_lower_wages_toggle_enabled(void) {
    g_scenario.random_events.lower_wages = !g_scenario.random_events.lower_wages;
    g_scenario.is_saved = 0;
}

int scenario_editor_contaminated_water_enabled(void) {
    return g_scenario.random_events.contaminated_water;
}

void scenario_editor_contaminated_water_toggle_enabled(void) {
    g_scenario.random_events.contaminated_water = !g_scenario.random_events.contaminated_water;
    g_scenario.is_saved = 0;
}

int scenario_editor_iron_mine_collapse_enabled(void) {
    return g_scenario.random_events.copper_mine_collapsed;
}

void scenario_editor_iron_mine_collapse_toggle_enabled(void) {
    g_scenario.random_events.copper_mine_collapsed = !g_scenario.random_events.copper_mine_collapsed;
    g_scenario.is_saved = 0;
}

int scenario_editor_clay_pit_flooded_enabled(void) {
    return g_scenario.random_events.clay_pit_flooded;
}

void scenario_editor_clay_pit_flooded_toggle_enabled(void) {
    g_scenario.random_events.clay_pit_flooded = !g_scenario.random_events.clay_pit_flooded;
    g_scenario.is_saved = 0;
}
