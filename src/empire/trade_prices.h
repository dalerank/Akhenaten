#pragma once

#include "core/buffer.h"
#include "game/resource.h"

void trade_prices_reset();
int trade_price_buy(int resource);
enum { PRICE_WITH_BONUS, PRICE_ONLY_BASE, PRICE_ONLY_BONUS };
int trade_price_sell(int resource, int bonus_inclusion = PRICE_WITH_BONUS);
int trade_price_change(int resource, int amount);