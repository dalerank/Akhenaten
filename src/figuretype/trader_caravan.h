#pragma once

#include "game/resource.h"

class building;
class figure;

bool figure_trade_caravan_can_buy(figure* trader, building* warehouse, int city_id);
bool figure_trade_caravan_can_sell(figure* trader, building* warehouse, int city_id);
