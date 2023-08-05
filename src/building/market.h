#pragma once

#include "game/resource.h"

class building;

int building_market_get_max_food_stock(building* market);
int building_market_get_max_goods_stock(building* market);
int building_market_get_storage_destination(building* market);
bool is_good_accepted(int index, building* market);
void toggle_good_accepted(int index, building* market);
void unaccept_all_goods(building* market);
