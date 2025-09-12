#pragma once

#include "core/buffer.h"
#include "game/resource.h"

struct trade_price {
    e_resource res;
    int32_t buy;
    int32_t sell;
};

enum e_price_rule { 
    PRICE_WITH_BONUS, 
    PRICE_ONLY_BASE, 
    PRICE_ONLY_BONUS 
};

void trade_prices_reset();
int trade_price_buy(e_resource resource);
int trade_price_sell(e_resource resource, int bonus_inclusion = PRICE_WITH_BONUS);
bool trade_price_change(e_resource resource, int amount);