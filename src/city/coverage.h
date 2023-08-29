#pragma once

class buffer;

void city_culture_update_coverage();
void city_health_update_coverage();

int city_culture_coverage_booth();
int city_culture_coverage_amphitheater(void);
int city_culture_coverage_colosseum(void);
int city_culture_coverage_hippodrome(void);
int city_culture_coverage_average_entertainment(void);

int city_culture_coverage_religion(int god);

int city_culture_coverage_school(void);
int city_culture_coverage_library(void);
int city_culture_coverage_academy();

int city_health_coverage_mortuary(void);
int city_health_coverage_physician(void);

int city_culture_average_education(void);
int city_culture_average_entertainment(void);
int city_culture_average_health(void);

void city_culture_calculate(void);

void city_coverage_save_state(buffer* buf);
void city_coverage_load_state(buffer* buf);
