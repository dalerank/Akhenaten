#pragma once

#include "city/gods.h"

class buffer;

void city_culture_update_coverage();
void city_health_update_coverage();

int city_culture_coverage_booth();
int city_culture_coverage_amphitheater();
int city_culture_coverage_colosseum();
int city_culture_coverage_hippodrome();
int city_culture_coverage_average_entertainment();

int city_culture_coverage_religion(e_god god);

int city_culture_coverage_school();
int city_culture_coverage_library();
int city_culture_coverage_academy();

int city_health_coverage_mortuary();
int city_health_coverage_physician();

int city_culture_average_education();
int city_culture_average_entertainment();
int city_culture_average_health();

void city_culture_calculate();

void city_coverage_save_state(buffer* buf);
void city_coverage_load_state(buffer* buf);
