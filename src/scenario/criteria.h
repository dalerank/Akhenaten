#pragma once

#include "core/buffer.h"

int scenario_criteria_time_limit_enabled();
int scenario_criteria_time_limit_years();

int scenario_criteria_survival_enabled();
int scenario_criteria_survival_years();

int winning_population();
int winning_culture();
int winning_prosperity();
int winning_monuments();
int winning_kingdom();
int winning_housing();
int winning_houselevel();
int winning_conditions();
int winning_reasons();

int scenario_criteria_milestone_year(int percentage);
void scenario_criteria_init_max_year();
int scenario_criteria_max_year();