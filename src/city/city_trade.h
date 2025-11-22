#pragma once

#include "game/resource.h"

struct city_trade_t {
    int16_t num_land_routes;
    int16_t num_sea_routes;
    int16_t land_trade_problem_duration;
    int16_t sea_trade_problem_duration;

    e_resource caravan_import_resource;
    e_resource caravan_backup_import_resource;

    e_resource docker_import_resource;
    e_resource docker_export_resource;
};

void city_trade_add_land_trade_route();
void city_trade_add_sea_trade_route();

int city_trade_has_land_trade_route();
int city_trade_has_sea_trade_route();

void city_trade_start_land_trade_problems(int duration);
void city_trade_start_sea_trade_problems(int duration);

int city_trade_has_land_trade_problems();
int city_trade_has_sea_trade_problems();

bool city_resource_trade_surplus(e_resource resource);

e_resource city_trade_current_caravan_import_resource();
e_resource city_trade_next_caravan_import_resource();
e_resource city_trade_next_caravan_backup_import_resource();

e_resource city_trade_next_docker_import_resource();
e_resource city_trade_next_docker_export_resource();
