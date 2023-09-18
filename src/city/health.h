#pragma once

int city_health();
void city_health_change(int amount);
void city_health_update();
void city_health_reset_mortuary_workers();
void city_health_add_mortuary_workers(int amount);
void city_health_start_disease(int total_people, bool force, int plague_people);