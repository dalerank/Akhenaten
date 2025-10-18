#pragma once

#include "game/resource.h"

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
