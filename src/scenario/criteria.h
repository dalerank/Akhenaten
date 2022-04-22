#ifndef SCENARIO_CRITERIA_H
#define SCENARIO_CRITERIA_H

#include "core/buffer.h"

int scenario_criteria_time_limit_enabled(void);
int scenario_criteria_time_limit_years(void);

int scenario_criteria_survival_enabled(void);
int scenario_criteria_survival_years(void);

int winning_population();
int winning_culture();
int winning_prosperity();
int winning_monuments();
int winning_kingdom();
int winning_housing();
int winning_houselevel();

int scenario_criteria_milestone_year(int percentage);
void scenario_criteria_init_max_year(void);
int scenario_criteria_max_year(void);

#endif // SCENARIO_CRITERIA_H
