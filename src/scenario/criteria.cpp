#include "criteria.h"

#include "scenario/data.h"

static int max_game_year;

int scenario_criteria_time_limit_enabled(void) {
    return scenario_data.win_criteria.time_limit.enabled;
}
int scenario_criteria_time_limit_years(void) {
    return scenario_data.win_criteria.time_limit.years;
}
int scenario_criteria_survival_enabled(void) {
    return scenario_data.win_criteria.survival_time.enabled;
}
int scenario_criteria_survival_years(void) {
    return scenario_data.win_criteria.survival_time.years;
}

int winning_population() {
    if (!scenario_data.win_criteria.population.enabled)
        return 0;
    return scenario_data.win_criteria.population.goal;
}
int winning_culture() {
    if (!scenario_data.win_criteria.culture.enabled)
        return 0;
    return scenario_data.win_criteria.culture.goal;
}
int winning_prosperity() {
    if (!scenario_data.win_criteria.prosperity.enabled)
        return 0;
    return scenario_data.win_criteria.prosperity.goal;
}
int winning_monuments() {
    if (!scenario_data.win_criteria.monuments.enabled)
        return 0;
    return scenario_data.win_criteria.monuments.goal;
}
int winning_kingdom() {
    if (!scenario_data.win_criteria.kingdom.enabled)
        return 0;
    return scenario_data.win_criteria.kingdom.goal;
}
int winning_housing() {
    if (!scenario_data.win_criteria.housing_count.enabled)
        return 0;
    return scenario_data.win_criteria.housing_count.goal;
}
int winning_houselevel() {
    if (!scenario_data.win_criteria.housing_level.enabled)
        return 0;
    return scenario_data.win_criteria.housing_level.goal;
}

int scenario_criteria_milestone_year(int percentage) {
    switch (percentage) {
        case 25:
            return scenario_data.start_year + scenario_data.win_criteria.milestone25_year;
        case 50:
            return scenario_data.start_year + scenario_data.win_criteria.milestone50_year;
        case 75:
            return scenario_data.start_year + scenario_data.win_criteria.milestone75_year;
        default:
            return 0;
    }
}

void scenario_criteria_init_max_year(void) {
    if (scenario_data.win_criteria.time_limit.enabled)
        max_game_year = scenario_data.start_year + scenario_data.win_criteria.time_limit.years;
    else if (scenario_data.win_criteria.survival_time.enabled)
        max_game_year = scenario_data.start_year + scenario_data.win_criteria.survival_time.years;
    else
        max_game_year = 1000000 + scenario_data.start_year;
}
int scenario_criteria_max_year(void) {
    return max_game_year;
}
io_buffer *iob_max_year = new io_buffer([](io_buffer *iob) {
    iob->bind(BIND_SIGNATURE_UINT32, &max_game_year);
});
