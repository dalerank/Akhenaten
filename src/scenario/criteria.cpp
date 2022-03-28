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
int winning_peace() {
    if (!scenario_data.win_criteria.peace.enabled)
        return 0;
    return scenario_data.win_criteria.peace.goal;
}
int winning_favor() {
    if (!scenario_data.win_criteria.favor.enabled)
        return 0;
    return scenario_data.win_criteria.favor.goal;
}
int winning_housing() {
    if (!scenario_data.win_criteria.ph_goal1.enabled)
        return 0;
    return scenario_data.win_criteria.ph_goal1.goal;
}
int winning_houselevel() {
    if (!scenario_data.win_criteria.ph_goal2.enabled)
        return 0;
    return scenario_data.win_criteria.ph_goal2.goal;
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
void scenario_max_year_save_state(buffer *buf) {
    buf->write_i32(max_game_year);
}
void scenario_max_year_load_state(buffer *buf) {
    max_game_year = buf->read_i32();
}
